#include "interactions.h"
#include <fstream>
#include <sstream>
#include <iostream>

// interactions.cpp 

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// readInteractions
// Reads each non-empty line, identifies the type (P or D),
// and parses the remainder accordingly.
 
bool readInteractions(const std::string& filename,
                      std::vector<Interaction>& interactions) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open interactions file: " << filename << "\n";
        return false;
    }

    interactions.clear();
    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;
        line = trim(line);
        if (line.empty()) continue;

        // Expect format: "X: ..."
        if (line.size() < 3 || line[1] != ':') {
            std::cerr << "WARNING: Skipping malformed interaction line "
                      << lineNum << ": " << line << "\n";
            continue;
        }

        char type = std::toupper(line[0]);
        std::string rest = trim(line.substr(2)); // everything after "X: "

        Interaction inter;
        inter.type = type;

        if (type == 'P') {
            // P: <customerID>
            try {
                inter.customerID = std::stoi(rest);
            } catch (...) {
                std::cerr << "WARNING: Invalid customer ID on line "
                          << lineNum << ": " << rest << "\n";
                continue;
            }
        } else if (type == 'D') {
            // D: name,phone,time
            std::stringstream ss(rest);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, ',')) {
                parts.push_back(trim(token));
            }
            if (parts.size() < 3) {
                std::cerr << "WARNING: Malformed drop-off on line "
                          << lineNum << ": " << rest << "\n";
                continue;
            }
            inter.name  = parts[0];
            inter.phone = parts[1];
            inter.time  = parts[2];
            inter.customerID = -1; // not assigned yet; set during parking
        } else {
            std::cerr << "WARNING: Unknown interaction type '"
                      << type << "' on line " << lineNum << "\n";
            continue;
        }

        interactions.push_back(inter);
    }

    file.close();
    std::cout << "Loaded " << interactions.size() << " interactions.\n";
    return true;
}


// printInteraction
// Displays a single interaction in human-readable form.

void printInteraction(const Interaction& inter) {
    if (inter.type == 'P') {
        std::cout << "  [PICKUP] Customer ID: " << inter.customerID << "\n";
    } else if (inter.type == 'D') {
        std::cout << "  [DROP-OFF] " << inter.name
                  << " | " << inter.phone
                  << " | " << inter.time << "\n";
    }
}
