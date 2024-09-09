//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace seneca {

    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        bool operator+=(const T& item) {
            if (this->size() >= this->capacity()) {
                return false;
            }

            unsigned index = 0;
            while (index < this->size() && this->operator[](index) < item) {
                ++index;
            }

            for (unsigned i = this->size(); i > index; --i) {
                this->operator[](i) = this->operator[](i - 1);
            }

            this->operator[](index) = item;
            this->incrSize();
            this->setSmallestItem(item);
            this->setLargestItem(item);

            return true;
        }
    };

} // namespace seneca

#endif // SENECA_ORDEREDCOLLECTION_H
