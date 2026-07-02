#ifndef RETRIEVAL_H
#define RETRIEVAL_H

#include <vector>
#include "garage.h"
#include "customer.h"
#include "location.h"

/*
 * retrieval.h
 * Component 5: Parking lot reconfiguration after a customer picks up their car.
 *
 * Algorithm:
 *   1. Locate the car using Component 4.
 *   2. If the car is on top of its garage stack, pop it directly.
 *   3. If cars are blocking it, temporarily move them (pop from the
 *      source garage and push to a temporary "free" garage) until
 *      the target car is exposed.
 *   4. Pop the target car.
 *   5. Move all temporarily displaced cars back to the first
 *      available garage.
 *
 * A "free" garage is defined as one that is NOT the source garage
 * and has available space (subject to the n-free-space rule).
 */

// Retrieve the car for a given customer from the garage system.
// Handles reconfiguration (moving blocking cars).
// Returns true on success, false if the car cannot be found or
// the system cannot safely reconfigure.
bool retrieveCar(std::vector<Garage>& garages,
                 int n,
                 int customerID);

#endif // RETRIEVAL_H
