//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <iostream>


namespace seneca {
    class Reservation {
    private:
        std::string id;
        std::string name;
        std::string email;
        int partySize;
        int day;
        int hour;

    public:
        Reservation();
        void update(int newDay, int newHour);
        Reservation(const std::string& res);
        friend std::ostream& operator<<(std::ostream& os, const Reservation& reservation);
    };
}

#endif // RESERVATION_H
