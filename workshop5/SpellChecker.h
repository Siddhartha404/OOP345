//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>

namespace seneca {

    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        size_t m_replacements[6] = { 0 };

    public:
        // Constructor
        SpellChecker(const char* filename);

        // Functor to replace misspelled words
        void operator()(std::string& text);

        // Function to show statistics
        void showStatistics(std::ostream& out) const;
    };

} // namespace seneca

#endif // SENECA_SPELLCHECKER_H
