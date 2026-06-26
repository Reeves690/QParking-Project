#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include "garage.h"
#include "customer.h"

/*
 * config.h
 * Component 1: Reading the configuration file and initialising the system.
 *
 * Responsible for:
 *   - Parsing the top-level config text file (m, n, and filenames)
 *   - Loading the initial garage occupancy from a CSV
 *   - Loading the initial customer list from a CSV
 */

// Holds the top-level configuration parsed from config.txt
struct SystemConfig {
    int m;                       // Number of garages
    int n;                       // Capacity of each garage
    std::string garageFile;      // Path to garage occupancy CSV
    std::string customerFile;    // Path to customer info CSV
};

// Parse the top-level configuration text file.
// Returns true on success, false on failure.
bool readConfig(const std::string& filename, SystemConfig& config);

// Build the garage array from the occupancy CSV.
// garages is populated with m Garage objects each of size n.
// Returns true on success.
bool loadGarages(const SystemConfig& config, std::vector<Garage>& garages);

// Load customers from the customer CSV into the customers vector.
// Returns true on success.
bool loadCustomers(const SystemConfig& config, std::vector<Customer>& customers);

// Print the full current state of all garages to stdout.
void printAllGarages(const std::vector<Garage>& garages);

// Write the full garage state to a file (used for output.txt).
void writeGarageState(const std::vector<Garage>& garages, std::ofstream& out);

#endif // CONFIG_H
