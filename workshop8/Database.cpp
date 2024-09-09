//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include "Database.h"
#include <iomanip>
#include <algorithm>

namespace seneca {
    // Initialize static member
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::instance = nullptr;

    // Constructor: Load data from file
    template<typename T>
    Database<T>::Database(const std::string& filename) : filename(filename), numEntries(0) {
        std::ifstream file(filename);
        if (!file) {
            std::cout << "[" << this << "] ";
            std::cout << "Database(const std::string&) - File could not be opened" << std::endl;
            return;
        }

        std::cout << "[" << this << "] ";
        std::cout << "Database(const std::string&)" << std::endl;

        std::string key;
        T value;
        while (file >> key >> value) {
            if (numEntries >= capacity) {
                break;
            }
            std::replace(key.begin(), key.end(), '_', ' ');
            encryptDecrypt(value);
            keys[numEntries] = key;
            values[numEntries] = value;
            numEntries++;
        }
    }

    // Get singleton instance
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename) {
        if (!instance) {
            instance = std::shared_ptr<Database<T>>(new Database<T>(filename));
        }
        return instance;
    }

    // Get value by key
    template<typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value) const {
        for (int i = 0; i < numEntries; ++i) {
            if (keys[i] == key) {
                value = values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    // Set value by key
    template<typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
        if (numEntries >= capacity) {
            return Err_Status::Err_OutOfMemory;
        }
        keys[numEntries] = key;
        values[numEntries] = value;
        numEntries++;
        return Err_Status::Err_Success;
    }

    // Destructor: Backup data
    template<typename T>
    Database<T>::~Database() {
        std::cout << "[" << this << "] ";
        std::cout << "~Database()" << std::endl;

        std::ofstream backupFile(filename + ".bkp.txt", std::ios::out | std::ios::binary);
        if (!backupFile) {
            std::cerr << "Error opening backup file for writing." << std::endl;
            return;
        }

        for (int i = 0; i < numEntries; ++i) {
            T encryptedValue = values[i];
            encryptDecrypt(encryptedValue);
            backupFile << std::left << std::setw(25) << keys[i] << " -> " << encryptedValue << std::endl;
        }

        backupFile.close();
    }

    // Specialized encryptDecrypt for std::string
    template<>
    void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[] = "secret encryption key";
        size_t secret_len = sizeof(secret) - 1;

        for (char& c : value) {
            for (size_t j = 0; j < secret_len; ++j) {
                c ^= secret[j];
            }
        }
    }

    // Specialized encryptDecrypt for long long
    template<>
    void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[] = "super secret encryption key";
        size_t secret_len = sizeof(secret) - 1;

        char* data = reinterpret_cast<char*>(&value);

        for (size_t i = 0; i < sizeof(long long); ++i) {
            for (size_t j = 0; j < secret_len; ++j) {
                data[i] ^= secret[j];
            }
        }
    }

    // Explicit template instantiation
    template class Database<std::string>;
    template class Database<long long>;
}
