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
    private:
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

        void trim(std::string& str);

    public:
        // Default constructor
        Book();

        // Constructor that parses a string to initialize the attributes
        Book(const std::string& strBook);

        // Query for title
        const std::string& title() const;

        // Query for country
        const std::string& country() const;

        // Query for year
        const size_t& year() const;

        // Function to get price by reference
        double& price();

        // Templated function to fix spelling
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_description);
        }

        // Friend function to overload insertion operator
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };

} // namespace seneca

#endif // SENECA_BOOK_H
