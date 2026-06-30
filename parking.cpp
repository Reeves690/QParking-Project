#include "parking.h"
#include <iostream>

/*
 * parking.cpp
 * Component 3 implementation: parking space assignment.
 *
 * The system must always keep at least n spaces free so that
 * cars can be shuffled to retrieve a specific vehicle.
 * Therefore, the effective maximum capacity is n*(m-1).
 */

// -----------------------------------------------------------------
// totalCarsParked
// Counts cells with value >= 0 (a real car ID).
// -----------------------------------------------------------------
int totalCarsParked(const std::vector<Garage>& garages) {
    int total = 0;
    for (const Garage& g : garages) {
        total += g.carCount();
    }
    return total;
}

// -----------------------------------------------------------------
// totalAvailableSpaces
// Counts cells with value == -1 (empty and unrestricted).
// -----------------------------------------------------------------
int totalAvailableSpaces(const std::vector<Garage>& garages) {
    int total = 0;
    for (const Garage& g : garages) {
        for (int s : g.spaces) {
            if (s == -1) total++;
        }
    }
    return total;
}

// -----------------------------------------------------------------
// canPark
// The lot can accept a new car only if there will still be at
// least n free spaces after the car is parked.
// -----------------------------------------------------------------
bool canPark(const std::vector<Garage>& garages, int n) {
    // After parking one more car, available spaces would drop by 1.
    return totalAvailableSpaces(garages) - 1 >= n;
}

// -----------------------------------------------------------------
// assignParking
// Scans garages in order and parks the car in the first one that
// has room (is not fully packed). Returns garage index or -1.
// -----------------------------------------------------------------
int assignParking(std::vector<Garage>& garages, int n, int customerID) {
    if (!canPark(garages, n)) {
        std::cout << "  LOT FULL: Cannot park customer " << customerID
                  << " — insufficient free spaces.\n";
        return -1;
    }

    for (int i = 0; i < (int)garages.size(); i++) {
        if (!garages[i].isFull()) {
            garages[i].pushCar(customerID);
            std::cout << "  Customer " << customerID
                      << " parked in garage " << i << ".\n";
            return i;
        }
    }

    // Should not reach here if canPark() returned true, but guard anyway
    std::cout << "  LOT FULL: No suitable garage found for customer "
              << customerID << ".\n";
    return -1;
}
