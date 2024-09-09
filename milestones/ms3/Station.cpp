// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/20
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"
#include <iomanip>

namespace seneca {

    // Initialize static members
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& record)
        : m_id(++id_generator) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
        m_quantity = std::stoul(util.extractToken(record, next_pos, more));
        m_description = util.extractToken(record, next_pos, more);

        // Update width field if necessary
        if (m_widthField < m_itemName.length()) {
            m_widthField = m_itemName.length();
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

     void Station::display(std::ostream &os, bool full) const
    {
        os << std::setfill('0') << std::setw(3) << std::right << m_id;
        os << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName;
        os << " | " << std::setfill('0') << std::setw(6) << std::right << m_serialNumber << " | ";

        if (full)
        {
            os << std::setfill(' ') << std::setw(4) << std::right << m_quantity
               << " | " << std::left << m_description << std::endl;
        }
        else
        {
            os << std::endl;
        }
    }


} // namespace seneca
