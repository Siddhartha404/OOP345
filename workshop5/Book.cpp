//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include "Book.h"
#include <sstream>
#include <iomanip>

namespace seneca {

    // Private helper function to trim spaces
    void Book::trim(std::string& str) {
        size_t start = str.find_first_not_of(" ");
        size_t end = str.find_last_not_of(" ");
        if (start == std::string::npos || end == std::string::npos) {
            str = "";
        }
        else {
            str = str.substr(start, end - start + 1);
        }
    }

    // Default constructor
    Book::Book() : m_year(0), m_price(0.0) {}

    // Constructor that parses a string to initialize the attributes
    Book::Book(const std::string& strBook) {
        std::istringstream stream(strBook);
        std::string token;

        std::getline(stream, m_author, ',');
        std::getline(stream, m_title, ',');
        std::getline(stream, m_country, ',');
        std::getline(stream, token, ',');
        m_price = std::stod(token);
        std::getline(stream, token, ',');
        m_year = std::stoi(token);
        std::getline(stream, m_description);

        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\n\r"));
            s.erase(s.find_last_not_of(" \t\n\r") + 1);
            };

        trim(m_author);
        trim(m_title);
        trim(m_country);
        trim(m_description);
    }

    // Query for title
    const std::string& Book::title() const {
        return m_title;
    }

    // Query for country
    const std::string& Book::country() const {
        return m_country;
    }

    // Query for year
    const size_t& Book::year() const {
        return m_year;
    }

    // Function to get price by reference
    double& Book::price() {
        return m_price;
    }

    // Friend function to overload insertion operator
    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << std::right << book.m_author << " | "
            << std::setw(22) << std::right << book.m_title << " | "
            << std::setw(5) << std::right << book.m_country << " | "
            << std::setw(4) << std::right << book.m_year << " | "
            << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
            << book.m_description << "\n";
        return os;
    }

} // namespace seneca
