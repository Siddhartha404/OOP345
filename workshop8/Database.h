//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments.This submitted piece of work has not been shared with any other student or 3rd party content provider.

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <array>

namespace seneca {
    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template<typename T>
    class Database {
    private:
        static std::shared_ptr<Database<T>> instance;
        std::string filename;
        static const int capacity = 20;
        std::array<std::string, capacity> keys;
        std::array<T, capacity> values;
        int numEntries = 0;

        Database(const std::string& filename);
        void encryptDecrypt(T& value);

    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& filename);
        Err_Status GetValue(const std::string& key, T& value) const;
        Err_Status SetValue(const std::string& key, const T& value);
        ~Database();
    };

    //template specializations for encryption/decryption
    template<>
    void Database<std::string>::encryptDecrypt(std::string& value);

    template<>
    void Database<long long>::encryptDecrypt(long long& value);
}

#endif // SENECA_DATABASE_H