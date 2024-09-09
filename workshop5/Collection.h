//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace seneca {
    template <typename T>
    class Collection {
        std::string m_name;
        T* m_items;
        size_t m_size;
        void (*m_observer)(const Collection<T>&, const T&);

    public:
        // Sets the name of the collection to the string referred to by the parameter and sets all other attributes to their default value
        Collection(const std::string& name);
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        ~Collection();

        // A query that returns the name of the collection.
        const std::string& name() const;
        // A query that returns the number of items in the collection.
        size_t size() const;
        void setObserver(void (*observer)(const Collection<T>&, const T&));
        Collection<T>& operator+=(const T& item);
        // Returns the item at index idx
        T& operator[](size_t idx) const;
        // Returns the address of the item with the title title (type T has a member function called title() that returns the title of the item)
        T* operator[](const std::string& title) const;
        // Insertion operator to insert the content of a Collection object into an ostream object. 
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Collection<U>& collection);
    };

    template <typename T>
    Collection<T>::Collection(const std::string& name) : m_name{ name }, m_items{ nullptr }, m_size{ 0 }, m_observer{ nullptr } {}

    template <typename T>
    Collection<T>::~Collection() {
        delete[] m_items;
    }

    template <typename T>
    const std::string& Collection<T>::name() const {
        return m_name;
    }

    template <typename T>
    size_t Collection<T>::size() const {
        return m_size;
    }

    template <typename T>
    void Collection<T>::setObserver(void (*observer)(const Collection<T>&, const T&)) {
        m_observer = observer;
    }

    template <typename T>
    Collection<T>& Collection<T>::operator+=(const T& item) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_items[i].title() == item.title()) {
                return *this;
            }
        }

        T* temp = new T[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_items[i];
        }
        temp[m_size] = item;
        delete[] m_items;
        m_items = temp;
        ++m_size;

        if (m_observer) {
            m_observer(*this, item);
        }

        return *this;
    }

    template <typename T>
    T& Collection<T>::operator[](size_t idx) const {
        if (idx >= m_size) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
        }
        return m_items[idx];
    }

    template <typename T>
    T* Collection<T>::operator[](const std::string& title) const {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_items[i].title() == title) {
                return &m_items[i];
            }
        }
        return nullptr;
    }

    template <typename U>
    std::ostream& operator<<(std::ostream& os, const Collection<U>& collection) {
        for (size_t i = 0; i < collection.m_size; ++i) {
            os << collection.m_items[i];
        }
        return os;
    }
}
#endif 