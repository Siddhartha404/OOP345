//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include "Movie.h"
#include "Movie.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace seneca {

    // Default constructor
    Movie::Movie() : m_title(""), m_year(0), m_description("") {}

    // Constructor that parses a string to initialize the attributes
    Movie::Movie(const std::string& strMovie) {
        std::istringstream stream(strMovie);
        std::string token;

        std::getline(stream, m_title, ',');
        std::getline(stream, token, ',');
        m_year = std::stoi(token);
        std::getline(stream, m_description);

        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\n\r"));
            s.erase(s.find_last_not_of(" \t\n\r") + 1);
            };

        trim(m_title);
        trim(m_description);
    }

    // Query for title
    const std::string& Movie::title() const {
        return m_title;
    }

    // Friend function to overload insertion operator
    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::setw(40) << std::right << movie.m_title << " | "
            << std::setw(4) << std::right << movie.m_year << " | "
            << movie.m_description << "\n";
        return os;
    }

} // namespace seneca
