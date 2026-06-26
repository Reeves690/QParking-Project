#include <iostream>
#include <vector>
#include <string>

#include "config.h"
#include "customer.h"
#include "garage.h"

/*
 * main.cpp
 * QParking – Valet Parking Simulation
 * CSCE 2110, Section 400
 *
 * Milestone 1: Reads the configuration file, loads the garage
 * occupancy layout, loads the customer list, and prints the
 * initial parking lot state to the screen.
 */

int main() {
    // -------------------------------------------------------
    // Step 1: Get config filename from user
    // -------------------------------------------------------
    std::string configFilename;
    std::cout << "QParking System - Milestone 1\n";
    std::cout << "Enter the name of the configuration file: ";
    std::cin >> configFilename;

    // -------------------------------------------------------
    // Step 2: Read configuration (Component 1)
    // -------------------------------------------------------
    SystemConfig config;
    if (!readConfig(configFilename, config)) {
        std::cerr << "FATAL: Could not read configuration. Exiting.\n";
        return 1;
    }

    // -------------------------------------------------------
    // Step 3: Load garages (Component 1)
    // -------------------------------------------------------
    std::vector<Garage> garages;
    if (!loadGarages(config, garages)) {
        std::cerr << "FATAL: Could not load garage data. Exiting.\n";
        return 1;
    }

    // -------------------------------------------------------
    // Step 4: Load customers (Component 1)
    // -------------------------------------------------------
    std::vector<Customer> customers;
    if (!loadCustomers(config, customers)) {
        std::cerr << "FATAL: Could not load customer data. Exiting.\n";
        return 1;
    }

    // -------------------------------------------------------
    // Step 5: Print initial garage state
    // -------------------------------------------------------
    std::cout << "\n=== Initial Garage State ===\n";
    printAllGarages(garages);

    std::cout << "\nSystem initialized successfully.\n";
    std::cout << "Garages: " << config.m << "\n";
    std::cout << "Capacity per garage: " << config.n << "\n";
    std::cout << "Max cars: " << config.n * (config.m - 1) << "\n";
    std::cout << "Customers loaded: " << customers.size() << "\n";

    return 0;
}
