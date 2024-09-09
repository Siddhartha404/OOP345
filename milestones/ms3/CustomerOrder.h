// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/20
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Station.h"

namespace seneca {
    struct Item
    {
        std::string m_itemName = "";
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const std::string& src) : m_itemName(src) {}
    };

    class CustomerOrder {
        std::string m_name = "";
        std::string m_product = "";
        size_t m_cntItem = 0u;
        Item** m_lstItem{ nullptr };
        static size_t m_widthField;

    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string& line);
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(CustomerOrder& customer) = delete;
        CustomerOrder(CustomerOrder&& moveCustomer) noexcept;
        CustomerOrder& operator=(CustomerOrder&& moveCustomer) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };

}

#endif // SENECA_CUSTOMERORDER_H
