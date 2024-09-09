//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <string>

namespace seneca {
    class Book {
        std::string m_title{};
        unsigned m_numChapters{};
        unsigned m_numPages{};
    public:
        Book();
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        const std::string& title() const;
        unsigned numChapters() const;
        unsigned numPages() const;
        bool isValid() const;

        bool operator==(const Book& other) const;
        bool operator!=(const Book& other) const;
        bool operator<(const Book& other) const;
        bool operator>(const Book& other) const;

        std::ostream& print(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif // !SENECA_BOOK_H
