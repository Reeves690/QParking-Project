#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include <string>
#include <vector>

/*
 * interactions.h
 * Component 2: Reading sample system interactions from a text file.
 *
 * Each line is either:
 *   P: <customerID>          – customer picking up their car
 *   D: <name>,<phone>,<time> – customer requesting valet drop-off
 */

// Represents a single interaction parsed from the interactions file
struct Interaction {
    char type;           // 'P' = pickup, 'D' = drop-off
    int  customerID;     // For P: type only
    std::string name;    // For D: type only
    std::string phone;   // For D: type only
    std::string time;    // For D: type only (arrival time)
};

// Read and parse all interactions from the given file.
// Returns true on success; populates the interactions vector.
bool readInteractions(const std::string& filename,
                      std::vector<Interaction>& interactions);

// Print a single interaction to stdout (for logging/debugging).
void printInteraction(const Interaction& inter);

#endif // INTERACTIONS_H
