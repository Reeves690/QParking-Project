#include "status.h"
#include "parking.h"
#include <iostream>

/*
 * status.cpp
 * Component 6 implementation: lot status reporting and output file writing.
 *
 * Every interaction is followed by a snapshot of the garage states
 * written to output.txt
 */

// printLotStatus
// Displays the current occupancy and whether the lot is full.

void printLotStatus(const std::vector<Garage>& garages, int n, int m) {
    int cars      = totalCarsParked(garages);
    int available = totalAvailableSpaces(garages);
    int maxCars   = n * (m - 1);

    std::cout << "  --- Lot Status ---\n";
    std::cout << "  Cars parked   : " << cars << " / " << maxCars << "\n";
    std::cout << "  Spaces free   : " << available << "\n";

    if (!canPark(garages, n)) {
        std::cout << "  Status        : FULL (cannot accept new arrivals)\n";
    } else {
        std::cout << "  Status        : Open (" << (maxCars - cars)
                  << " slot(s) remaining)\n";
    }
    std::cout << "  ------------------\n";
}

// logInteraction
// Writes a numbered entry for one interaction to the output file,
// including the full garage state after execution.

void logInteraction(std::ofstream& out,
                    int interactionNumber,
                    const Interaction& inter,
                    const std::vector<Garage>& garages,
                    int n,
                    int m) {
    out << "\n--- Interaction #" << interactionNumber << " ---\n";

    if (inter.type == 'P') {
        out << "Type   : PICKUP\n";
        out << "Customer ID: " << inter.customerID << "\n";
    } else if (inter.type == 'D') {
        out << "Type   : DROP-OFF\n";
        out << "Name   : " << inter.name << "\n";
        out << "Phone  : " << inter.phone << "\n";
        out << "Time   : " << inter.time << "\n";
    }

    // Lot status
    int cars      = totalCarsParked(garages);
    int available = totalAvailableSpaces(garages);
    int maxCars   = n * (m - 1);
    out << "Cars parked: " << cars << " / " << maxCars << "\n";
    out << "Spaces free: " << available << "\n";
    out << (canPark(garages, n) ? "Status: OPEN\n" : "Status: FULL\n");

    // Garage snapshot
    out << "Garage state after interaction:\n";
    for (int g = 0; g < (int)garages.size(); g++) {
        out << "  Garage " << g << " [top->bottom]: ";
        const Garage& garage = garages[g];
        bool anyPrinted = false;
        for (int i = garage.capacity - 1; i >= 0; i--) {
            if (garage.spaces[i] >= 0) {
                out << "[Car " << garage.spaces[i] << "] ";
                anyPrinted = true;
            } else if (garage.spaces[i] == -1) {
                out << "[---] ";
            } else {
                out << "[R] ";
            }
        }
        if (!anyPrinted) out << "(empty)";
        out << "\n";
    }
}

// writeFinalSummary
// Writes the complete post-simulation summary to the output file.

void writeFinalSummary(std::ofstream& out,
                       const std::vector<Garage>& garages,
                       int n,
                       int m) {
    out << "\n========== FINAL GARAGE STATE ==========\n";
    int cars      = totalCarsParked(garages);
    int available = totalAvailableSpaces(garages);
    int maxCars   = n * (m - 1);
    out << "Total cars parked : " << cars << " / " << maxCars << "\n";
    out << "Total spaces free : " << available << "\n";
    out << (canPark(garages, n) ? "Lot status        : OPEN\n"
                                 : "Lot status        : FULL\n");
    out << "\n";

    for (int g = 0; g < (int)garages.size(); g++) {
        out << "Garage " << g << " (top -> bottom):\n";
        const Garage& garage = garages[g];
        for (int i = garage.capacity - 1; i >= 0; i--) {
            out << "  Slot " << i << ": ";
            if (garage.spaces[i] >= 0)
                out << "Car (Customer " << garage.spaces[i] << ")\n";
            else if (garage.spaces[i] == -1)
                out << "Available\n";
            else
                out << "Restricted\n";
        }
    }
    out << "=========================================\n";
}
