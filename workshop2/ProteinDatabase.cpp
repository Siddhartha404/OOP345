//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include "ProteinDatabase.h"

namespace seneca {
    ProteinDatabase::ProteinDatabase() {}
    ProteinDatabase::ProteinDatabase(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::string protein;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') {
                // Save the previous protein sequence
                if (!protein.empty()) {
                    proteins.push_back(protein);
                    protein.clear();
                }
            }
            else {
                protein += line;
            }
        }
        // Save the last protein sequence
        if (!protein.empty()) {
            proteins.push_back(protein);
        }
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) : proteins(other.proteins) {}

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
        if (this != &other) {
            proteins = other.proteins;
        }
        return *this;
    }

    ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) noexcept : proteins(std::move(other.proteins)) {
        other.proteins.clear();
    }

    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) noexcept {
        if (this != &other) {
            proteins = std::move(other.proteins);
            other.proteins.clear();
        }
        return *this;
    }

    ProteinDatabase::~ProteinDatabase() {}

    size_t ProteinDatabase::size() const {
        return proteins.size();
    }

    std::string ProteinDatabase::operator[](size_t index) const {
        return (index < proteins.size()) ? proteins[index] : std::string();
    }

}

