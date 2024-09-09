// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/07/12
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace seneca {

    // Initialize static member
    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.size()) {
            more = false;
            return "";
        }

        size_t end_pos = str.find(m_delimiter, next_pos);

        if (end_pos == std::string::npos) {
            more = false;
            end_pos = str.size();
        }
        else {
            more = true;
        }

        if (end_pos == next_pos) {
            more = false;
            throw std::runtime_error("Delimiter found at next_pos");
        }

        std::string token = str.substr(next_pos, end_pos - next_pos);
        next_pos = end_pos + 1;

        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));

        token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), token.end());

        if (m_widthField < token.size()) {
            m_widthField = token.size();
        }

        return token;
    }

} 
