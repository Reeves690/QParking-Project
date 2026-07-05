#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "config.h"
#include "customer.h"
#include "garage.h"
#include "interactions.h"
#include "location.h"
#include "parking.h"
#include "retrieval.h"
#include "status.h"

/*
 * main.cpp
 * QParking 
 * CSCE 2110
 *
 * Entry point: prompts the user for the config filename,
 * initialises the system, then processes each interaction
 * in sequence, logging the garage state after each one.
 *
 * Output is written to "output.txt".
 */

int main() {
    // Step 1: Get config filename from user
    std::string configFilename;
    std::cout << "QParking System\n";
    std::cout << "Enter the name of the configuration file: ";
    std::cin >> configFilename;

    // Step 2: Read configuration (Component 1)

    SystemConfig config;
    if (!readConfig(configFilename, config)) {
        std::cerr << "FATAL: Could not read configuration. Exiting.\n";
        return 1;
    }

    // Step 3: Initialise garages and customers (Component 1)

    std::vector<Garage> garages;
    if (!loadGarages(config, garages)) {
        std::cerr << "FATAL: Could not load garage data. Exiting.\n";
        return 1;
    }

    std::vector<Customer> customers;
    if (!loadCustomers(config, customers)) {
        std::cerr << "FATAL: Could not load customer data. Exiting.\n";
        return 1;
    }

    // Track the next available customer ID for new drop-offs
    int nextCustomerID = 0;
    for (const Customer& c : customers) {
        if (c.id >= nextCustomerID) nextCustomerID = c.id + 1;
    }

    // Print the initial state
    std::cout << "\n=== Initial Garage State ===\n";
    printAllGarages(garages);
    printLotStatus(garages, config.n, config.m);

    // Step 4: Read interactions file (Component 2)

    // The interactions filename is prompted from the user as
    // per the assignment: "Read in and execute sample system interaction"
    std::string interactionsFilename;
    std::cout << "\nEnter the name of the interactions file: ";
    std::cin >> interactionsFilename;

    std::vector<Interaction> interactions;
    if (!readInteractions(interactionsFilename, interactions)) {
        std::cerr << "FATAL: Could not read interactions. Exiting.\n";
        return 1;
    }

    // Step 5: Open output file

    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cerr << "FATAL: Could not open output.txt for writing.\n";
        return 1;
    }

    outFile << "QParking Simulation Output\n";
    outFile << "Config: m=" << config.m << " garages, n=" << config.n
            << " spaces each\n";
    outFile << "Max capacity: " << config.n * (config.m - 1) << " cars\n";

    // Step 6: Execute each interaction

    int interNum = 0;
    for (Interaction& inter : interactions) {
        interNum++;
        std::cout << "\n=== Interaction #" << interNum << " ===\n";
        printInteraction(inter);

        if (inter.type == 'D') {
            // DROP-OFF: register customer, then assign parking
            // Assign the next available ID
            inter.customerID = nextCustomerID++;

            // Add to customer list
            Customer newCust;
            newCust.id            = inter.customerID;
            newCust.name          = inter.name;
            newCust.phone         = inter.phone;
            newCust.arrivalTime   = inter.time;
            newCust.departureTime = "";
            customers.push_back(newCust);

            std::cout << "  Registered as customer ID: "
                      << inter.customerID << "\n";

            // Component 3: assign a parking space
            int garageUsed = assignParking(garages, config.n, inter.customerID);
            if (garageUsed == -1) {
                std::cout << "  DROP-OFF FAILED: lot is full.\n";
            }

        } else if (inter.type == 'P') {
            // PICKUP: locate (Component 4) and retrieve (Component 5)
            CarLocation loc = locateCar(garages, inter.customerID);
            printCarLocation(loc, inter.customerID);

            if (loc.found) {
                retrieveCar(garages, config.n, inter.customerID);
            }
        }

        // Component 6: print and log status after each interaction
        printAllGarages(garages);
        printLotStatus(garages, config.n, config.m);
        logInteraction(outFile, interNum, inter, garages, config.n, config.m);
    }

    // Step 7: Write final summary to output file
    
    writeFinalSummary(outFile, garages, config.n, config.m);
    outFile.close();

    std::cout << "\nSimulation complete. Results written to output.txt\n";
    return 0;
}
