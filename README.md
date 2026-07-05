# QParking-Project
QParking 
CSCE 2110

Reeves Holliday

-----------------------------------
PROJECT DESCRIPTION
-----------------------------------
QParking simulates a valet parking system consisting of m
"stack" garages, each of capacity n. Cars are parked using
a LIFO approach. At least n spaces are kept free
at all times to allow retrieval of any car.

Maximum cars parked simultaneously: n * (m - 1)

This milestone implements Component 1: reading the
configuration file and initializing the system. It reads
the garage occupancy layout and customer list from input
files and prints the initial garage state to the screen.

--------------------
FILES:
--------------------
main.cpp          – Entry point (int main)
config.h/.cpp     – Component 1: reads config/garage/customer files
interactions.h/.cpp – Component 2: reads interaction commands
parking.h/.cpp    – Component 3: parking space assignment
location.h/.cpp   – Component 4: car location search
retrieval.h/.cpp  – Component 5: lot reconfiguration & retrieval
status.h/.cpp     – Component 6: lot status and output logging
garage.h/.cpp     – Garage data structure (LIFO stack)
customer.h        – Customer struct definition


------------------------------
HOW TO COMPILE
------------------------------
CSE CELL machines:

  g++ -Wall -std=c++17 -o qparking main.cpp config.cpp garage.cpp interactions.cpp 
      parking.cpp location.cpp retrieval.cpp status.cpp

Visual Studio terminal:

  g++ -o qparking main.cpp config.cpp garage.cpp interactions.cpp 
      parking.cpp location.cpp retrieval.cpp status.cpp

-----------------------------
HOW TO RUN:

  ./qparking          (Linux / CSE CELL)
  .\qparking          (VSC)

The program will prompt you for the configuration filename.
Type: config.txt

--------------------------

INPUT FILE FORMATS

--------------------------

config.txt (text):
  Line 1: <m> <n>           (number of garages and capacity)
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
  P: <customerID>                     (pickup request)
  D: <name>,<phone>,<arrivalTime>     (drop-off request)
----------------------------------------
EXPECTED OUTPUT
----------------------------------------
The program will print the initial state of all garages
showing which spaces are occupied, available, or empty,
along with a summary of the number of garages, capacity,
max cars, and customers loaded.
