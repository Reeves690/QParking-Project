#include "location.h"
#include <iostream>

/*
 * location.cpp
 * Component 4 implementation: locating a car in the garage system.
 *
 * Performs a linear scan across all garages. In a real system this
 * could be replaced with a hash map (customerID -> garage+index)
 * for O(1) lookup; here we use O(m*n) linear search as specified.
 */

// -----------------------------------------------------------------
// locateCar
// Iterates over each garage and calls findCar on each one.
// Returns immediately when the car is found.
// -----------------------------------------------------------------
CarLocation locateCar(const std::vector<Garage>& garages, int customerID) {
    CarLocation result;
    result.found        = false;
    result.garageIndex  = -1;
    result.stackIndex   = -1;

    for (int g = 0; g < (int)garages.size(); g++) {
        int idx = garages[g].findCar(customerID);
        if (idx != -1) {
            result.found       = true;
            result.garageIndex = g;
            result.stackIndex  = idx;
            return result;
        }
    }

    return result; // not found
}

// -----------------------------------------------------------------
// printCarLocation
// Displays the result of a locateCar call in a readable form.
// -----------------------------------------------------------------
void printCarLocation(const CarLocation& loc, int customerID) {
    if (loc.found) {
        std::cout << "  Car for customer " << customerID
                  << " is in garage " << loc.garageIndex
                  << " at stack position " << loc.stackIndex
                  << " (0 = bottom).\n";
    } else {
        std::cout << "  Car for customer " << customerID
                  << " was NOT found in any garage.\n";
    }
}
