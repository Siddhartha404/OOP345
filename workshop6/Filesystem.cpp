//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.
#include <fstream>
#include <sstream>
#include <iostream>
#include "Filesystem.h"
#include "File.h"

namespace seneca
{
    Filesystem::Filesystem(std::string fileName, std::string root)
    {
        // Create root directory
        m_root = new Directory(root);
        m_current = m_root;

        // Open the file
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            delete m_root;
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        while (std::getline(file, line))
        {
            line = trim(line);

            // Check if the line contains file content
            size_t separator_pos = line.find('|');
            if (separator_pos != std::string::npos)
            {
                // This is a file
                std::string filePath = trim(line.substr(0, separator_pos));
                std::string fileContent = trim(line.substr(separator_pos + 1));

                std::istringstream pathStream(filePath);
                std::string segment;
                Directory* currentDir = m_root;

                // Split the path and create directories
                while (std::getline(pathStream, segment, '/'))
                {
                    segment = trim(segment);

                    if (pathStream.eof())
                    {
                        // Last segment, this is the file name
                        File* newFile = new File(segment, fileContent);
                        *currentDir += newFile;
                    }
                    else
                    {
                        // This is a directory
                        segment += "/";
                        Resource* foundDir = currentDir->find(segment);
                        if (!foundDir)
                        {
                            Directory* newDir = new Directory(segment);
                            *currentDir += newDir;
                            currentDir = newDir;
                        }
                        else
                        {
                            currentDir = dynamic_cast<Directory*>(foundDir);
                        }
                    }
                }
            }
            else
            {
                // This is a directory
                std::string dirPath = trim(line);

                std::istringstream pathStream(dirPath);
                std::string segment;
                Directory* currentDir = m_root;

                // Split the path and create directories
                while (std::getline(pathStream, segment, '/'))
                {
                    segment = trim(segment) + "/";

                    Resource* foundDir = currentDir->find(segment);
                    if (!foundDir)
                    {
                        Directory* newDir = new Directory(segment);
                        *currentDir += newDir;
                        currentDir = newDir;
                    }
                    else
                    {
                        currentDir = dynamic_cast<Directory*>(foundDir);
                    }
                }
            }
        }

        file.close();
    }

    Filesystem::Filesystem(Filesystem&& other) noexcept : m_root(other.m_root), m_current(other.m_current)
    {
        other.m_root = nullptr;
        other.m_current = nullptr;
    }

    Filesystem& Filesystem::operator=(Filesystem&& other) noexcept
    {
        if (this != &other)
        {
            delete m_root;
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_root = nullptr;
            other.m_current = nullptr;
        }
        return *this;
    }

    Filesystem& Filesystem::operator+=(Resource* res)
    {
        *m_current += res;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& newCurrentDir)
    {
        if (newCurrentDir.empty())
        {
            m_current = m_root;
            return m_current;
        }

        Directory* newDir = dynamic_cast<Directory*>(m_current->find(newCurrentDir));
        if (!newDir)
        {
            throw std::invalid_argument("Cannot change directory! " + newCurrentDir + " not found!");
        }

        m_current = newDir;
        return m_current;
    }

    Directory* Filesystem::get_current_directory() const
    {
        return m_current;
    }

    Filesystem::~Filesystem()
    {
        delete m_root;
    }

    // Implementation of the trim function
    std::string Filesystem::trim(const std::string& str)
    {
        size_t first_non_space = str.find_first_not_of(' ');
        size_t last_non_space = str.find_last_not_of(' ');

        if (first_non_space == std::string::npos || last_non_space == std::string::npos)
            return "";

        return str.substr(first_non_space, last_non_space - first_non_space + 1);
    }
}
