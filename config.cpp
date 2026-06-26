#include "config.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
 * config.cpp
 * Component 1 implementation: reads the config file, garage CSV,
 * and customer CSV to initialise the entire QParking system.
 */

// -----------------------------------------------------------------
// Helper: split a CSV line into tokens
// -----------------------------------------------------------------
static std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        // Trim leading/trailing whitespace
        size_t start = token.find_first_not_of(" \t\r\n");
        size_t end   = token.find_last_not_of(" \t\r\n");
        if (start != std::string::npos)
            tokens.push_back(token.substr(start, end - start + 1));
        else
            tokens.push_back("");
    }
    return tokens;
}

// -----------------------------------------------------------------
// readConfig
// File format (text):
//   Line 1: <m> <n>
//   Line 2: <garage CSV filename>
//   Line 3: <customer CSV filename>
// -----------------------------------------------------------------
bool readConfig(const std::string& filename, SystemConfig& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open config file: " << filename << "\n";
        return false;
    }

    std::string line;

    // Line 1: m and n
    if (!std::getline(file, line)) {
        std::cerr << "ERROR: Config file is empty.\n";
        return false;
    }
    std::istringstream ss1(line);
    if (!(ss1 >> config.m >> config.n)) {
        std::cerr << "ERROR: First line of config must be '<m> <n>'.\n";
        return false;
    }

    // Line 2: garage CSV filename
    if (!std::getline(file, config.garageFile)) {
        std::cerr << "ERROR: Missing garage filename in config.\n";
        return false;
    }
    // Trim whitespace/newline
    config.garageFile.erase(config.garageFile.find_last_not_of(" \t\r\n") + 1);

    // Line 3: customer CSV filename
    if (!std::getline(file, config.customerFile)) {
        std::cerr << "ERROR: Missing customer filename in config.\n";
        return false;
    }
    config.customerFile.erase(config.customerFile.find_last_not_of(" \t\r\n") + 1);

    std::cout << "Config loaded: m=" << config.m << " garages, n=" << config.n
              << " spaces each.\n";
    std::cout << "  Garage file  : " << config.garageFile << "\n";
    std::cout << "  Customer file: " << config.customerFile << "\n";

    file.close();
    return true;
}

// -----------------------------------------------------------------
// loadGarages
// Garage CSV format:
//   Each column = one garage (m columns)
//   Each row    = one level (n rows, row 0 = bottom of stack)
//   Cell values: -1 (available), -2/R (restricted), or customerID
// -----------------------------------------------------------------
bool loadGarages(const SystemConfig& config, std::vector<Garage>& garages) {
    std::ifstream file(config.garageFile);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open garage file: " << config.garageFile << "\n";
        return false;
    }

    // Initialise m empty garages of capacity n
    garages.clear();
    for (int i = 0; i < config.m; i++) {
        garages.emplace_back(config.n);
    }

    // Read n rows; each row has m comma-separated values
    // We store row 0 as the bottom of each garage stack (index 0)
    std::vector<std::vector<int>> grid; // grid[row][col]

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = splitCSV(line);
        std::vector<int> row;
        for (const std::string& tok : tokens) {
            if (tok == "R" || tok == "r") {
                row.push_back(-2); // restricted
            } else {
                try {
                    row.push_back(std::stoi(tok));
                } catch (...) {
                    row.push_back(-1); // treat unknown as available
                }
            }
        }
        grid.push_back(row);
    }
    file.close();

    // Assign grid values to garages
    // grid[row][col] → garages[col].spaces[row]
    for (int row = 0; row < (int)grid.size() && row < config.n; row++) {
        for (int col = 0; col < config.m && col < (int)grid[row].size(); col++) {
            garages[col].spaces[row] = grid[row][col];
        }
    }

    std::cout << "Garages initialised from " << config.garageFile << ".\n";
    return true;
}

// -----------------------------------------------------------------
// loadCustomers
// Customer CSV format (one customer per row):
//   customerID, name, phone, arrivalTime, departureTime
// -----------------------------------------------------------------
bool loadCustomers(const SystemConfig& config, std::vector<Customer>& customers) {
    std::ifstream file(config.customerFile);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open customer file: " << config.customerFile << "\n";
        return false;
    }

    customers.clear();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = splitCSV(line);
        if (tokens.size() < 5) {
            std::cerr << "WARNING: Skipping malformed customer line: " << line << "\n";
            continue;
        }
        Customer c;
        try { c.id = std::stoi(tokens[0]); } catch (...) { continue; }
        c.name          = tokens[1];
        c.phone         = tokens[2];
        c.arrivalTime   = tokens[3];
        c.departureTime = tokens[4];
        customers.push_back(c);
    }

    file.close();
    std::cout << "Loaded " << customers.size() << " customers.\n";
    return true;
}

// -----------------------------------------------------------------
// printAllGarages
// Prints each garage's state to stdout.
// -----------------------------------------------------------------
void printAllGarages(const std::vector<Garage>& garages) {
    std::cout << "=== Garage States ===\n";
    for (int i = 0; i < (int)garages.size(); i++) {
        garages[i].printState(i);
    }
    std::cout << "=====================\n";
}

// -----------------------------------------------------------------
// writeGarageState
// Writes each garage's current state to an output file stream.
// -----------------------------------------------------------------
void writeGarageState(const std::vector<Garage>& garages, std::ofstream& out) {
    out << "=== Garage States ===\n";
    for (int g = 0; g < (int)garages.size(); g++) {
        out << "  Garage " << g << " (top -> bottom): ";
        const Garage& garage = garages[g];
        for (int i = garage.capacity - 1; i >= 0; i--) {
            if (garage.spaces[i] >= 0)
                out << "[Car " << garage.spaces[i] << "] ";
            else if (garage.spaces[i] == -1)
                out << "[---] ";
            else
                out << "[R] ";
        }
        out << "\n";
    }
    out << "=====================\n";
}
