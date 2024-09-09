//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include <iostream>
#include "Restaurant.h"

namespace seneca {
    Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : reservations(nullptr), count(0) {
        if (reservations != nullptr && cnt > 0) {
            count = cnt;
            this->reservations = new Reservation * [count];
            for (size_t i = 0; i < count; ++i) {
                this->reservations[i] = new Reservation(*reservations[i]);
            }
        }
    }

    Restaurant::~Restaurant() {
        for (size_t i = 0; i < count; ++i) {
            delete reservations[i];
        }
        delete[] reservations;
    }

    Restaurant::Restaurant(const Restaurant& other) : reservations(nullptr), count(0) {
        *this = other;
    }

    Restaurant& Restaurant::operator=(const Restaurant& other) {
        if (this != &other) {
            for (size_t i = 0; i < count; ++i) {
                delete reservations[i];
            }
            delete[] reservations;

            count = other.count;
            if (count > 0) {
                reservations = new Reservation * [count];
                for (size_t i = 0; i < count; ++i) {
                    reservations[i] = new Reservation(*other.reservations[i]);
                }
            }
            else {
                reservations = nullptr;
            }
        }
        return *this;
    }

    Restaurant::Restaurant(Restaurant&& other) noexcept : reservations(other.reservations), count(other.count) {
        other.reservations = nullptr;
        other.count = 0;
    }

    Restaurant& Restaurant::operator=(Restaurant&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < count; ++i) {
                delete reservations[i];
            }
            delete[] reservations;

            reservations = other.reservations;
            count = other.count;

            other.reservations = nullptr;
            other.count = 0;
        }
        return *this;
    }

    size_t Restaurant::size() const {
        return count;
    }

    std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant) {
        static int call_count = 0;
        ++call_count;

        os << "--------------------------" << std::endl;
        os << "Fancy Restaurant (" << call_count << ")" << std::endl;
        os << "--------------------------" << std::endl;

        if (restaurant.count == 0) {
            os << "This restaurant is empty!" << std::endl;
        }
        else {
            for (size_t i = 0; i < restaurant.count; ++i) {
                os << *restaurant.reservations[i];
            }
        }
        os << "--------------------------" << std::endl;

        return os;
    }
}
