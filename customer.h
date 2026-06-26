#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

/*
 * customer.h
 * Defines the Customer struct used throughout the QParking system.
 * Each customer has a unique ID, name, cell phone number,
 * arrival time, and departure time.
 */

struct Customer {
    int id;              // Unique customer ID (assigned on registration)
    std::string name;
    std::string phone;
    std::string arrivalTime;
    std::string departureTime;
};

#endif // CUSTOMER_H
