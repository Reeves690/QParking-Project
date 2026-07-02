#include "retrieval.h"
#include "parking.h"
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

/*
 * retrieval.cpp
 * Component 5 implementation: car retrieval with lot reconfiguration.
 *
 * Key constraint: at least n spaces must remain free at all times,
 * which is what makes retrieval possible without exiting the lot.
 * The displaced cars are temporarily held in a queue and re-parked
 * after the target vehicle is removed.
 */


// Helper: find the index of a garage that has room for one more car
// and is NOT the excluded garage.
// Returns -1 if none found.
static int findFreeGarage(const std::vector<Garage>& garages, int excludeIdx) {
    for (int i = 0; i < (int)garages.size(); i++) {
        if (i == excludeIdx) continue;
        if (!garages[i].isFull()) return i;
    }
    return -1;
}

// retrieveCar
bool retrieveCar(std::vector<Garage>& garages, int n, int customerID) {
    // Step 1: locate the car
    CarLocation loc = locateCar(garages, customerID);
    if (!loc.found) {
        std::cout << "  RETRIEVAL FAILED: Customer " << customerID
                  << "'s car not found.\n";
        return false;
    }

    int srcGarage = loc.garageIndex;
    std::cout << "  Retrieving car for customer " << customerID
              << " from garage " << srcGarage << ".\n";

    // Step 2: pop cars above the target into a list tracking (carID, tempGarageIdx).
    // Anything on top of the target car must be moved to a free garage first.
    // Record exactly where each car was placed so we can remove it cleanly.
    std::vector<std::pair<int,int>> displaced; // {carID, tempGarageIdx}

    while (garages[srcGarage].peekTop() != customerID) {
        int topID = garages[srcGarage].popCar();
        if (topID == -1) {
            std::cerr << "ERROR: Stack inconsistency during retrieval.\n";
            return false;
        }

        // Find a free garage to temporarily hold this car
        int freeIdx = findFreeGarage(garages, srcGarage);
        if (freeIdx == -1) {
            std::cerr << "ERROR: No free garage available for displaced car "
                      << topID << " during retrieval.\n";
            garages[srcGarage].pushCar(topID); // best-effort rollback
            return false;
        }

        garages[freeIdx].pushCar(topID);
        displaced.push_back({topID, freeIdx});
        std::cout << "    Moved car " << topID
                  << " to garage " << freeIdx << " temporarily.\n";
    }

    // Step 3: pop the target car
    int retrieved = garages[srcGarage].popCar();
    std::cout << "  Car for customer " << retrieved
              << " retrieved from garage " << srcGarage << ". Goodbye!\n";

    // Step 4: re-park displaced cars. Iterate in reverse order so
    // we pop each from its temporary garage (where it sits on top) and
    // re-assign it to any available spot.
    for (int i = (int)displaced.size() - 1; i >= 0; i--) {
        int carID      = displaced[i].first;
        int tempGarage = displaced[i].second;

        // Remove from the top of the temp garage
        int popped = garages[tempGarage].popCar();
        if (popped != carID) {
            // Fallback: locate and remove directly
            std::cerr << "WARNING: Displaced car " << carID
                      << " was not on top of garage " << tempGarage
                      << " — using locate fallback.\n";
            // Put the wrongly-popped car back
            if (popped != -1) garages[tempGarage].pushCar(popped);
            // Linear removal: find and blank the slot
            for (int& slot : garages[tempGarage].spaces) {
                if (slot == carID) { slot = -1; break; }
            }
        }

        // Re-park in the first available garage
        int reParkIdx = assignParking(garages, n, carID);
        if (reParkIdx == -1) {
            std::cerr << "WARNING: Could not re-park displaced car " << carID
                      << " — lot may be full.\n";
        } else {
            std::cout << "    Re-parked displaced car " << carID
                      << " in garage " << reParkIdx << ".\n";
        }
    }

    return true;
}
