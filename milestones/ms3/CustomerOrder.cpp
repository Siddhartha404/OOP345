// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/20
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include <string>
#include <algorithm>

using namespace std;

namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& str) {
        size_t next_pos = 0;
        bool more = true;
        Utilities util{};
        size_t startCpy{};
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        startCpy = next_pos;

        while (more) { util.extractToken(str, next_pos, more); m_cntItem++; }

        next_pos = startCpy;
        more = true;

        m_lstItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }

        m_widthField = std::max(m_widthField, util.getFieldWidth());
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& customer) {
        throw "ERROR: Cannot make copies.";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& moveCustomer) noexcept {
        *this = std::move(moveCustomer);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& moveCustomer) noexcept {
        if (this != &moveCustomer) {
            if (m_lstItem) {
                for (size_t i = 0; i < m_cntItem; i++) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }

            m_name = moveCustomer.m_name;
            m_product = moveCustomer.m_product;
            m_cntItem = moveCustomer.m_cntItem;
            m_lstItem = moveCustomer.m_lstItem;

            moveCustomer.m_name = "";
            moveCustomer.m_product = "";
            moveCustomer.m_cntItem = 0u;
            moveCustomer.m_lstItem = nullptr;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                if (!m_lstItem[i]->m_isFilled) {
                    return false;
                }
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {
                station.updateQuantity();
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                return;
            }
            else if (m_lstItem[i]->m_itemName == station.getItemName() && station.getQuantity() == 0) {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] ";
            os << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }

}
