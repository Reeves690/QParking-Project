#ifndef GARAGE_H
#define GARAGE_H

#include <vector>
#include <string>

/*
 * garage.h
 * Declares the Garage class which represents one "stack" garage
 * to store and retrieve cars.
 
 * Special cell values:
 *   -1  = available parking space
 *   -2  = restricted space (used for manipulation / retrieval)
 *    N  = occupied by customer with ID N (N >= 0)
 */

class Garage {
public:
    int capacity;               // Maximum number of spaces (n)
    std::vector<int> spaces;    // Index 0 = bottom of stack, top = last occupied

    // Constructor: initialises an empty garage of the given size
    Garage(int cap);

    // Returns true if the garage has at least one non-restricted available slot
    // while keeping n spaces free (enforced at the system level, not here)
    bool isFull() const;

    // Returns the number of cars currently parked (not counting restricted/available)
    int carCount() const;

    // Push a car (customerID) onto the top of the stack.
    bool pushCar(int customerID);

    // Pop the top car off the stack (retrieval or relocation).
    int popCar();

    // Peek at the top car without removing it.
    int peekTop() const;

    // Returns the 0-based stack index of a car belonging to customerID,
    // or -1 if not found.
    int findCar(int customerID) const;

    // Prints the current state of this garage (top to bottom).
    void printState(int garageIndex) const;
};

#endif // GARAGE_H
