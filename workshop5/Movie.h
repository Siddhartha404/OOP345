//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <iostream>
#include <string>

namespace seneca {

    class Movie {
    private:
        std::string m_title;
        int m_year;
        std::string m_description;
    public:
        // Default constructor
        Movie();

        // Constructor that parses a string to initialize the attributes
        Movie(const std::string& strMovie);

        // Query for title
        const std::string& title() const;

        // Templated function to fix spelling
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_description);
        }

        // Friend function to overload insertion operator
        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };
} // namespace seneca

#endif // SENECA_MOVIE_H
