#ifndef STATUS_H
#define STATUS_H

#include <vector>
#include <string>
#include <fstream>
#include "garage.h"
#include "customer.h"
#include "interactions.h"

/*
 * status.h
 * Component 6: Parking lot status and output functionality.
 *
 * Responsible for:
 *   - Reporting whether the lot is full
 *   - Reporting how many spaces are available
 *   - Writing the garage state to the output text file after each
 *     system interaction is executed
 */

// Print current lot status (full / spaces available) to stdout.
void printLotStatus(const std::vector<Garage>& garages, int n, int m);

// Write a full interaction log entry (interaction + garage state)
// to the output file stream.
void logInteraction(std::ofstream& out,
                    int interactionNumber,
                    const Interaction& inter,
                    const std::vector<Garage>& garages,
                    int n,
                    int m);

// Write the final garage state summary to the output file.
void writeFinalSummary(std::ofstream& out,
                       const std::vector<Garage>& garages,
                       int n,
                       int m);

#endif // STATUS_H
