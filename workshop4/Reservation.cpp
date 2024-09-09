//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include <iomanip>
#include <iostream>
#include <string>
#include "Reservation.h"

namespace seneca {
    Reservation::Reservation() : partySize(0), day(0), hour(0) {}

    void Reservation::update(int newDay, int newHour) {
        day = newDay;
        hour = newHour;
    }

    Reservation::Reservation(const std::string& res) {
        size_t start = 0;
        size_t end = res.find(':');
        id = res.substr(start, end - start);
        id.erase(0, id.find_first_not_of(' '));  // Remove leading spaces
        id.erase(id.find_last_not_of(' ') + 1);  // Remove trailing spaces

        start = end + 1;
        end = res.find(',', start);
        name = res.substr(start, end - start);
        name.erase(0, name.find_first_not_of(' '));  // Remove leading spaces
        name.erase(name.find_last_not_of(' ') + 1);  // Remove trailing spaces

        start = end + 1;
        end = res.find(',', start);
        email = res.substr(start, end - start);
        email.erase(0, email.find_first_not_of(' '));  // Remove leading spaces
        email.erase(email.find_last_not_of(' ') + 1);  // Remove trailing spaces

        start = end + 1;
        end = res.find(',', start);
        partySize = std::stoi(res.substr(start, end - start));

        start = end + 1;
        end = res.find(',', start);
        day = std::stoi(res.substr(start, end - start));

        start = end + 1;
        hour = std::stoi(res.substr(start));
    }

    std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {
        std::string temp;

        os << "Reservation ";
        os << std::setw(10) << std::right << reservation.id << ": ";
        os << std::setw(20) << std::right << reservation.name << "  ";
        std::string email_field = "<" + reservation.email + ">";
        os << std::left << std::setw(20) << std::setfill(' ') << email_field;
        os << "    ";

        if (reservation.hour >= 6 && reservation.hour <= 9) {
            temp = "Breakfast";
        }
        else if (reservation.hour >= 11 && reservation.hour <= 15) {
            temp = "Lunch";
        }
        else if (reservation.hour >= 17 && reservation.hour <= 21) {
            temp = "Dinner";
        }
        else {
            temp = "Drinks";
        }

        os << temp << " on day " << reservation.day << " @ " << reservation.hour << ":00 for " << reservation.partySize << (reservation.partySize == 1 ? " person." : " people.") << std::endl;
        return os;
    }
}
