//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include "Collection.h"
#include <iomanip>

namespace seneca {

    template <typename T, unsigned C>
    void Collection<T, C>::setSmallestItem(const T& item) {
        if (item < m_smallestItem) {
            m_smallestItem = item;
        }
    }

    template <typename T, unsigned C>
    void Collection<T, C>::setLargestItem(const T& item) {
        if (item > m_largestItem) {
            m_largestItem = item;
        }
    }

    template <typename T, unsigned C>
    bool Collection<T, C>::operator+=(const T& item) {
        if (m_size >= C) {
            return false;
        }
        m_items[m_size++] = item;
        setSmallestItem(item);
        setLargestItem(item);
        return true;
    }

    template <typename T, unsigned C>
    std::ostream& Collection<T, C>::print(std::ostream& os) const {
        os << "[";
        for (unsigned i = 0; i < m_size; ++i) {
            os << m_items[i];
            if (i < m_size - 1) {
                os << ",";
            }
        }
        os << "]";
        os << std::endl;
        return os;
    }

    // Specialization for Book when C = 10
    template <>
    std::ostream& Collection<seneca::Book, 10>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (unsigned i = 0; i < m_size; ++i) {
            os << "| " << std::setw(2);
            m_items[i].print(os);
            if (i < m_size - 1) {
                os << " |" << std::endl;
            }
        }
        os << " |"<< std::endl;
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }

    // Specialization for Book when C = 72
    template <>
    std::ostream& Collection<seneca::Book, 72>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (unsigned i = 0; i < m_size; ++i) {
            os << "| " << std::setw(2);
            m_items[i].print(os);
            if (i < m_size - 1) {
                os << " |" << std::endl;
            }
        }
        os << " |" << std::endl;
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }

    // Explicit instantiations for Collection<int, 10> and Collection<double, 10>
    template class Collection<int, 10>;
    template class Collection<double, 10>;

} // namespace seneca
