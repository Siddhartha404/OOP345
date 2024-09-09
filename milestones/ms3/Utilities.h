// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/20
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {

    class Utilities {
        size_t m_widthField = 1;
        static char m_delimiter;

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    };

} 

#endif // UTILITIES_H
