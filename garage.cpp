#include "garage.h"
#include <iostream>

/*
 * garage.cpp
 * Implementation of the Garage class.
 * Each garage is modelled as a vector acting as a stack (LIFO).
 * Index 0 is the bottom; cars are pushed/popped from the back.
 */

// -----------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------
Garage::Garage(int cap) : capacity(cap) {
    // Initialise all spaces as available (-1)
    spaces.assign(cap, -1);
}

// -----------------------------------------------------------------
// isFull
// A garage is considered full when every space holds a car (>= 0).
// -----------------------------------------------------------------
bool Garage::isFull() const {
    return carCount() >= capacity;
}

// -----------------------------------------------------------------
// carCount
// Count cells that hold a real car (value >= 0).
// -----------------------------------------------------------------
int Garage::carCount() const {
    int count = 0;
    for (int s : spaces) {
        if (s >= 0) count++;
    }
    return count;
}

// -----------------------------------------------------------------
// pushCar
// Places a car on the next available (–1) slot from the top down
// (i.e. the lowest index free slot that represents the top of the
// stack after previously parked cars).
// We fill from index 0 upward so the "top" is the highest-index
// occupied cell, matching the typical stack-garage model.
// -----------------------------------------------------------------
bool Garage::pushCar(int customerID) {
    for (int i = 0; i < capacity; i++) {
        if (spaces[i] == -1) {
            spaces[i] = customerID;
            return true;
        }
    }
    return false; // garage is full
}

// -----------------------------------------------------------------
// popCar
// Removes and returns the customerID at the top of the stack
// (highest occupied index). Returns -1 if no car is present.
// -----------------------------------------------------------------
int Garage::popCar() {
    for (int i = capacity - 1; i >= 0; i--) {
        if (spaces[i] >= 0) {
            int id = spaces[i];
            spaces[i] = -1;
            return id;
        }
    }
    return -1; // empty
}

// -----------------------------------------------------------------
// peekTop
// Returns the customerID at the top without removing it.
// -----------------------------------------------------------------
int Garage::peekTop() const {
    for (int i = capacity - 1; i >= 0; i--) {
        if (spaces[i] >= 0) {
            return spaces[i];
        }
    }
    return -1;
}

// -----------------------------------------------------------------
// findCar
// Linear search through the stack for a given customerID.
// Returns the index if found, -1 otherwise.
// -----------------------------------------------------------------
int Garage::findCar(int customerID) const {
    for (int i = 0; i < (int)spaces.size(); i++) {
        if (spaces[i] == customerID) return i;
    }
    return -1;
}

// -----------------------------------------------------------------
// printState
// Displays the garage from top (most recently parked) to bottom.
// -----------------------------------------------------------------
void Garage::printState(int garageIndex) const {
    std::cout << "  Garage " << garageIndex << " (top -> bottom): ";
    bool anyPrinted = false;
    for (int i = capacity - 1; i >= 0; i--) {
        if (spaces[i] >= 0) {
            std::cout << "[Car " << spaces[i] << "] ";
            anyPrinted = true;
        } else if (spaces[i] == -1) {
            std::cout << "[---] ";
        } else {
            std::cout << "[R] "; // restricted
        }
    }
    if (!anyPrinted) std::cout << "(empty)";
    std::cout << "\n";
}
