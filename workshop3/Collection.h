//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <array>
#include "Book.h"

namespace seneca {

    template <typename T, unsigned C>
    class Collection {
        static T m_smallestItem;
        static T m_largestItem;

        std::array<T, C> m_items{};
        unsigned m_size{ 0 };

    protected:
        T& operator[](unsigned index) { return m_items[index]; }
        const T& operator[](unsigned index) const { return m_items[index]; }
        void incrSize() { if (m_size < C) ++m_size; }

        void setSmallestItem(const T& item);
        void setLargestItem(const T& item);

    public:
        static T getSmallestItem() { return m_smallestItem; }
        static T getLargestItem() { return m_largestItem; }

        unsigned size() const { return m_size; }
        unsigned capacity() const { return C; }

        bool operator+=(const T& item);

        std::ostream& print(std::ostream& os) const;
    };

    // Static member initialization
    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = 9999;

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = -9999;

    // Specialization for Book when C = 10
    template <>
    seneca::Book Collection<seneca::Book, 10>::m_smallestItem = seneca::Book("", 1, 10000);

    template <>
    seneca::Book Collection<seneca::Book, 10>::m_largestItem = seneca::Book("", 10000, 1);

    // Specialization for Book when C = 72
    template <>
    seneca::Book Collection<seneca::Book, 72>::m_smallestItem = seneca::Book("", 1, 10000);

    template <>
    seneca::Book Collection<seneca::Book, 72>::m_largestItem = seneca::Book("", 10000, 1);

} // namespace seneca

#include "Collection.cpp"

#endif // SENECA_COLLECTION_H
