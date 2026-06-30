#ifndef PARKING_H
#define PARKING_H

#include <vector>
#include "garage.h"
#include "customer.h"

/*
 * parking.h
 * Component 3: Parking space assignment functionality.
 *
 * Rules enforced:
 *   - At least n spaces must remain free across ALL garages combined
 *     so there is always room to manoeuvre cars during retrieval.
 *   - Maximum cars parked at any time = n * (m - 1).
 *   - Cars are assigned to the first garage with available space.
 *   - Assignment uses LIFO (stack push) within each garage.
 */

// Returns the total number of cars currently parked across all garages.
int totalCarsParked(const std::vector<Garage>& garages);

// Returns the total number of available spaces (value == -1) across all garages.
int totalAvailableSpaces(const std::vector<Garage>& garages);

// Returns true if the system can accept one more car (capacity not exceeded).
// Must keep >= n spaces free at all times.
bool canPark(const std::vector<Garage>& garages, int n);

// Assign parking to a new customer.
// Finds the first garage with space and pushes the customerID.
// Returns the index of the garage used, or -1 if the lot is full.
int assignParking(std::vector<Garage>& garages, int n, int customerID);

#endif // PARKING_H
