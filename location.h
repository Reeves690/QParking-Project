#ifndef LOCATION_H
#define LOCATION_H

#include <vector>
#include "garage.h"

/*
 * location.h
 * Component 4: Car location functionality.
 *
 * Searches all garages to determine which garage and position
 * holds the car belonging to a given customer ID.
 */

// Result struct returned by locateCar
struct CarLocation {
    bool found;
    int garageIndex;   // Which garage (0-based)
    int stackIndex;    // Position within that garage's spaces vector
};

// Search all garages for a car belonging to customerID.
// Returns a CarLocation with found=true on success.
CarLocation locateCar(const std::vector<Garage>& garages, int customerID);

// Prints the located car's position in a human-readable format.
void printCarLocation(const CarLocation& loc, int customerID);

#endif // LOCATION_H
