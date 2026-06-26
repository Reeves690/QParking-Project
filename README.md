# QParking-Project
QParking 
CSCE 2110
Milestone 1 Submission

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
main.cpp        – Entry point (int main)
config.h/.cpp   – Component 1: reads config, garage, and
                  customer files and initializes the system
garage.h/.cpp   – Garage data structure (LIFO stack)
customer.h      – Customer struct definition

Input files:
  config.txt      – Configuration (m garages, n spaces,
                    and names of other input files)
  garage.csv      – Initial garage occupancy layout
  customers.csv   – Initial customer data

------------------------------
HOW TO COMPILE
------------------------------
CSE CELL machines:

  g++ -Wall -std=c++17 -o qparking main.cpp config.cpp garage.cpp

Visual Studio terminal:

  g++ -o qparking main.cpp config.cpp garage.cpp

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
  Line 1: <m> <n>  (number of garages, capacity)
  Line 2: <garage CSV file>
  Line 3: <customer CSV file>

garage.csv:
  n rows x m columns
  Each column = one garage
  Each row    = one level (row 0 = bottom of stack)
  Values: -1 (available), R (restricted), or customerID

customers.csv:
  id, name, phone, arrivalTime, departureTime

----------------------------------------
EXPECTED OUTPUT
----------------------------------------
The program will print the initial state of all garages
showing which spaces are occupied, available, or empty,
along with a summary of the number of garages, capacity,
max cars, and customers loaded.
