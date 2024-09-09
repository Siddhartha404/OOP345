//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <iomanip>
#include "FoodOrder.h"

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;
namespace seneca {
    FoodOrder::FoodOrder():m_name{ "" }, m_description(nullptr), m_price(0.0), m_dailySpecial(false) {}

    FoodOrder::FoodOrder(const FoodOrder& other) : m_price(other.m_price), m_dailySpecial(other.m_dailySpecial) {
        std::strcpy(m_name, other.m_name);

        if (other.m_description != nullptr) {
            m_description = new char[std::strlen(other.m_description) + 1];
            std::strcpy(m_description, other.m_description);
        }
        else {
            delete[] m_description;
            m_description = nullptr;
        }
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& other)
    {
        if (this != &other) {
            delete[] m_description;

            m_price = other.m_price;
            m_dailySpecial = other.m_dailySpecial;
            std::strcpy(m_name, other.m_name);

            if (other.m_description != nullptr) {
                m_description = new char[std::strlen(other.m_description) + 1];
                std::strcpy(m_description, other.m_description);
            }
            else {
                m_description = nullptr;
            }
        }
        return *this;
    }



    void FoodOrder::read(std::istream& input) {
        if (input) {
            char dailySpecialStatus = '\0';
            input.getline(m_name, 11, ',');

            std::string tempDesc;
            std::getline(input,tempDesc, ',');

            delete[] m_description;
            m_description = new char[tempDesc.length() + 1];
            std::strcpy(m_description, tempDesc.c_str());
            input >> m_price;
            input.ignore();
            input >> dailySpecialStatus;
            input.ignore();
            m_dailySpecial = (dailySpecialStatus == 'Y');
        }
    }

    void FoodOrder::display() const {
        static int counter = 1;

        if (std::strlen(m_name) == 0) {
            std::cout << std::left << std::setw(2) << counter++ << ". " << "No Order" << std::endl;
        }
        else {
            double priceWithTax = m_price * (1 + g_taxrate);
            std::cout << std::left << std::setw(2) << counter++ << ". "
                << std::left << std::setw(10) << m_name << "|"
                << std::left << std::setw(25) << m_description << "|"
                << std::left << std::setw(12) << std::fixed << std::setprecision(2) << priceWithTax;

            if (m_dailySpecial) {
                double specialPrice = priceWithTax - g_dailydiscount;
                std::cout << "|" << std::right << std::setw(13) << std::fixed << std::setprecision(2) << specialPrice;
            }
            else {
                std::cout << "|";
            }
            std::cout << std::endl;
        }
    }
    FoodOrder::~FoodOrder() {
        delete[] m_description;
    }
}
