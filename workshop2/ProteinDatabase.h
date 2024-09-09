//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace seneca {

    class ProteinDatabase {
    public:
        ProteinDatabase();
        explicit ProteinDatabase(const std::string& filename);
        ProteinDatabase(const ProteinDatabase& other);
        ProteinDatabase& operator=(const ProteinDatabase& other);
        ProteinDatabase(ProteinDatabase&& other) noexcept;
        ProteinDatabase& operator=(ProteinDatabase&& other) noexcept;
        ~ProteinDatabase();
        size_t size() const;
        std::string operator[](size_t index) const;

    private:
        std::vector<std::string> proteins;
    };
}

#endif
