QParking - CSCE 2110

Reeves Holliday

========================================================
PROJECT DESCRIPTION
========================================================
QParking simulates a valet parking system consisting of m
"stack" garages, each of capacity n. Cars are parked using
a LIFO (Last-In, First-Out) approach. At least n spaces
are kept free at all times to allow retrieval of any car.

Maximum cars parked simultaneously: n * (m - 1)

The system reads a configuration file, loads the initial
garage layout and customer list, then processes a series
of customer interactions (drop-offs and pickups). After
each interaction the garage state is printed to the screen
and logged to output.txt.

========================================================
FILES
========================================================
main.cpp              - Entry point (int main)
config.h / config.cpp - Component 1: reads config, garage,
                        and customer files, initializes system
interactions.h / interactions.cpp
                      - Component 2: reads interaction commands
parking.h / parking.cpp
                      - Component 3: parking space assignment
location.h / location.cpp
                      - Component 4: car location search
retrieval.h / retrieval.cpp
                      - Component 5: lot reconfiguration
                        and car retrieval
status.h / status.cpp - Component 6: lot status reporting
                        and output logging
garage.h / garage.cpp - Garage data structure (LIFO stack)
customer.h            - Customer struct definition

Input files:
  config.txt        - Configuration (m, n, and filenames)
  garage.csv        - Initial garage occupancy layout
  customers.csv     - Initial customer data
  interactions.txt  - 10 sample interactions (5 pickups,
                      5 drop-offs)

========================================================
HOW TO COMPILE
========================================================
On CSE CELL machines (Linux):

  g++ -Wall -std=c++17 -o qparking main.cpp config.cpp \
  garage.cpp interactions.cpp parking.cpp location.cpp \
  retrieval.cpp status.cpp

On Windows (Visual Studio terminal):

  g++ -o qparking main.cpp config.cpp garage.cpp interactions.cpp parking.cpp location.cpp retrieval.cpp status.cpp

No additional flags or libraries are required.

========================================================
HOW TO RUN
========================================================
  ./qparking       (Linux / CSE CELL machines)
  .\qparking       (Windows / Visual Studio terminal)

The program will prompt you for two filenames:
  1. Configuration file  -> type: config.txt
  2. Interactions file   -> type: interactions.txt

Do NOT include quotes around filenames.

========================================================
INPUT FILE FORMATS
========================================================

config.txt (text):
  Line 1: <m> <n>             (number of garages, capacity)
  Line 2: <garage CSV file>
  Line 3: <customer CSV file>

garage.csv:
  n rows x m columns
  Each column = one garage
  Each row    = one level (row 0 = bottom of stack)
  Values: -1 (available), R (restricted), or customerID

customers.csv:
  id, name, phone, arrivalTime, departureTime

interactions.txt:
  P: <customerID>                  (pickup request)
  D: <name>,<phone>,<arrivalTime>  (drop-off request)

========================================================
EXPECTED OUTPUT
========================================================
The program prints the garage state after each of the 10
interactions along with the current lot status (cars
parked, spaces free, open or full). A full log including
all interaction details and a final garage summary is
written to output.txt after the simulation completes.
