// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/20
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>

namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& line) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(line, next_pos, more);
        m_product = util.extractToken(line, next_pos, more);

        std::string itemName;
        while (more) {
            itemName = util.extractToken(line, next_pos, more);
            if (!itemName.empty()) {
                Item* newItem = new Item(itemName);
                m_cntItem++;
                Item** tempArray = new Item * [m_cntItem];
                for (size_t i = 0; i < m_cntItem - 1; ++i) {
                    tempArray[i] = m_lstItem[i];
                }
                tempArray[m_cntItem - 1] = newItem;
                delete[] m_lstItem;
                m_lstItem = tempArray;
            }
        }

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw std::runtime_error("Copy constructor is deleted.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& moveCustomer) noexcept
        : m_name(moveCustomer.m_name), m_product(moveCustomer.m_product), m_cntItem(moveCustomer.m_cntItem), m_lstItem(moveCustomer.m_lstItem) {
        moveCustomer.m_lstItem = nullptr;
        moveCustomer.m_cntItem = 0;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& moveCustomer) noexcept {
        if (this != &moveCustomer) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = moveCustomer.m_name;
            m_product = moveCustomer.m_product;
            m_cntItem = moveCustomer.m_cntItem;
            m_lstItem = moveCustomer.m_lstItem;

            moveCustomer.m_lstItem = nullptr;
            moveCustomer.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName) {
                return m_lstItem[i]->m_isFilled;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == station.getItemName()) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                else {
                    os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                return;
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
                << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

} // namespace seneca
