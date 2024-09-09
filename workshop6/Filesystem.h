//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.#ifndef SENECA_FILESYSTEM_H
#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"

namespace seneca
{
    class Filesystem
    {
        Directory* m_root;
        Directory* m_current;

    public:
        Filesystem(std::string fileName, std::string root = "");
        Filesystem(Filesystem&) = delete;
        Filesystem& operator=(Filesystem&) = delete;
        Filesystem(Filesystem&&) noexcept;
        Filesystem& operator=(Filesystem&&) noexcept;
        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string& newCurrentDir = "");
        Directory* get_current_directory() const;
        ~Filesystem();

        // Static member function for trimming strings
        static std::string trim(const std::string& str);
    };
}

#endif // !SENECA_FILESYSTEM_H
