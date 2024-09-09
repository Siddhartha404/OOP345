//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "Bakery.h"

using namespace std;

namespace seneca {

    Bakery::Bakery(const string& filename) {
        ifstream file(filename);

        if (!file) {
            throw runtime_error("Unable to open file: " + filename);
        }

        string line;
        BakedGood good;

        while (getline(file, line)) {
            if (line.empty()) continue; // Skip empty lines

            try {
                // Extracting BakedType
                string typeStr = line.substr(0, 8);
                if (typeStr.find("Bread") != string::npos) {
                    good.m_type = BakedType::BREAD;
                }
                else if (typeStr.find("Pastry") != string::npos) {
                    good.m_type = BakedType::PASTERY;
                }
                else {
                    continue; // Skip invalid types without error message
                }

                // Extracting description
                good.m_desc = line.substr(8, 20);
                good.m_desc.erase(0, good.m_desc.find_first_not_of(' ')); // Trim leading
                good.m_desc.erase(good.m_desc.find_last_not_of(' ') + 1); // Trim trailing

                // Extracting shelf life
                good.m_life = stoi(line.substr(28, 14));

                // Extracting stock
                good.m_stock = stoi(line.substr(42, 8));

                // Extracting price
                good.m_price = stod(line.substr(50, 6));

                m_goods.push_back(good);
            }
            catch (const exception&) {
                // Skip lines with invalid data without printing error messages
                continue;
            }
        }
    }

    void Bakery::showGoods(std::ostream& os) const {
        size_t totalStock = 0;
        double totalPrice = 0;

        for_each(m_goods.begin(), m_goods.end(), [&os, &totalStock, &totalPrice](const BakedGood& good)
            {
                os << good << std::endl;
                totalStock += good.m_stock;
                totalPrice += good.m_price;
            });

        os << "Total Stock: " << totalStock << std::endl;
        os << "Total Price: " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
    }


    ostream& operator<<(ostream& out, const BakedGood& b) {
        out << "* " << left;
        out << setw(10) << (b.m_type == BakedType::BREAD ? "Bread" : "Pastry");
        out << " * " << setw(20) << b.m_desc;
        out << " * " << setw(5) << b.m_life;
        out << " * " << setw(5) << b.m_stock;
        out << " * " << setw(8) << fixed << setprecision(2) << right << b.m_price << " * ";
        return out;
    }

    void Bakery::sortBakery(const string& sortBy) {
        sort(m_goods.begin(), m_goods.end(), [sortBy](const BakedGood& g1, const BakedGood& g2) {
            if (sortBy == "Description") return g1.m_desc < g2.m_desc;
            else if (sortBy == "Shelf") return g1.m_life < g2.m_life;
            else if (sortBy == "Stock") return g1.m_stock < g2.m_stock;
            else if (sortBy == "Price") return g1.m_price < g2.m_price;
            return false;
            });
    }

    vector<BakedGood> Bakery::combine(const Bakery& other) {
        vector<BakedGood> combined(m_goods);
        combined.insert(combined.end(), other.m_goods.begin(), other.m_goods.end());
        sort(combined.begin(), combined.end(), [](const BakedGood& g1, const BakedGood& g2) {
            return g1.m_price < g2.m_price;
            });
        return combined;
    }

    bool Bakery::inStock(const string& desc, const BakedType& type) const {
        return any_of(m_goods.begin(), m_goods.end(), [&desc, type](const BakedGood& good) {
            return good.m_desc == desc && good.m_type == type && good.m_stock > 0;
            });
    }

    list<BakedGood> Bakery::outOfStock(const BakedType& type) const {
        list<BakedGood> outOfStockGoods;
        copy_if(m_goods.begin(), m_goods.end(), back_inserter(outOfStockGoods), [type](const BakedGood& good) {
            return good.m_type == type && good.m_stock == 0;
            });
        return outOfStockGoods;
    }
}
