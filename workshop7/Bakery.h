#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>

namespace seneca {

    enum class BakedType {
        BREAD,
        PASTERY
    };

    struct BakedGood {
        BakedType m_type;
        std::string m_desc;
        int m_life;
        int m_stock;
        double m_price;
    };

    class Bakery {
    private:
        std::vector<BakedGood> m_goods;

    public:
        Bakery(const std::string& filename);
        void showGoods(std::ostream& os) const;
        void sortBakery(const std::string& sortBy);
        std::vector<BakedGood> combine(const Bakery& other);
        bool inStock(const std::string& desc, const BakedType& type) const;
        std::list<BakedGood> outOfStock(const BakedType& type) const;
    };

    std::ostream& operator<<(std::ostream& out, const BakedGood& b);

} // namespace seneca

#endif // BAKERY_H
