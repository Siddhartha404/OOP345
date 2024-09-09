//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222

#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder {
    private:
        char m_name[11];
        char *m_description;
        double m_price;
        bool m_dailySpecial;

    public:
        FoodOrder();
        FoodOrder(const FoodOrder& other);
        FoodOrder& operator=(const FoodOrder& other);
        void read(std::istream& input);
        void display() const;
        ~FoodOrder();
    };
}
#endif // SENECA_FOODORDER_H
