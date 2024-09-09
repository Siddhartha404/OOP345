//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include <iostream>
#include "ConfirmationSender.h"

namespace seneca {
    ConfirmationSender::ConfirmationSender() : reservations(nullptr), count(0) {}

    ConfirmationSender::~ConfirmationSender() {
        delete[] reservations;
    }

    ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) : reservations(nullptr), count(0) {
        *this = other;
    }

    ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
        if (this != &other) {
            delete[] reservations;

            count = other.count;
            reservations = new const Reservation * [count];
            for (size_t i = 0; i < count; ++i) {
                reservations[i] = other.reservations[i];
            }
        }
        return *this;
    }

    ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept : reservations(other.reservations), count(other.count) {
        other.reservations = nullptr;
        other.count = 0;
    }

    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept {
        if (this != &other) {
            delete[] reservations;

            reservations = other.reservations;
            count = other.count;

            other.reservations = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        // Check if the reservation is already in the array
        for (size_t i = 0; i < count; ++i) {
            if (reservations[i] == &res) {
                return *this;
            }
        }

        // Resize the array
        const Reservation** temp = new const Reservation * [count + 1];
        for (size_t i = 0; i < count; ++i) {
            temp[i] = reservations[i];
        }
        temp[count] = &res;

        delete[] reservations;
        reservations = temp;
        ++count;

        return *this;
    }

    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
        // Check if the reservation is in the array
        size_t index = count;
        for (size_t i = 0; i < count; ++i) {
            if (reservations[i] == &res) {
                index = i;
                break;
            }
        }

        if (index == count) {
            return *this; // Not found
        }

        // Resize the array
        const Reservation** temp = new const Reservation * [count - 1];
        for (size_t i = 0, j = 0; i < count; ++i) {
            if (i != index) {
                temp[j++] = reservations[i];
            }
        }

        delete[] reservations;
        reservations = temp;
        --count;

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender) {
        os << "--------------------------" << std::endl;
        os << "Confirmations to Send" << std::endl;
        os << "--------------------------" << std::endl;

        if (sender.count == 0) {
            os << "There are no confirmations to send!" << std::endl;
        }
        else {
            for (size_t i = 0; i < sender.count; ++i) {
                os << *sender.reservations[i];
            }
        }
        os << "--------------------------" << std::endl;

        return os;
    }
}
