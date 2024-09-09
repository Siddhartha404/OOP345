// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/08/03
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{
    // Global variables for managing orders
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders; // Orders in this workstation
        Workstation* m_pNextStation = nullptr; // Pointer to the next workstation

    public:
        // Constructor initializing base Station
        Workstation(const std::string& src) : Station(src) {};

        // Fills the order at the front of the queue if there are orders
        void fill(std::ostream& os);

        // Attempts to move the order to the next station or global queues
        bool attemptToMoveOrder();

        // Sets the next workstation in the assembly line
        void setNextStation(Workstation* station);

        // Gets the next workstation in the assembly line
        Workstation* getNextStation() const;

        // Displays the workstation and the next station or "End of Line"
        void display(std::ostream& os) const;

        // Adds a new customer order to this workstation
        Workstation& operator+=(CustomerOrder&& newOrder);

        // Deleted copy and move operations
        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;
    };
}

#endif // SENECA_WORKSTATION_H
