#ifndef ROOM_FOR_SALE_STRING_H
#define ROOM_FOR_SALE_STRING_H

#include <iostream>

namespace SimpleDB {
    class string {
        char* m_data;
        size_t m_capacity;
    public:
        string(const char* source = "");
        explicit string(size_t);
        string(const string&);
        string(string&&) noexcept;

        ~string() {
            delete[] m_data;
            m_capacity = 0;
            m_data = nullptr;
        }

        string& operator=(const string&);
        string& operator=(string&&) noexcept;

        [[nodiscard]] const char* str() const { return m_data; }

        string operator+(const string&) const;
        string& operator+=(const string&);

        [[nodiscard]] size_t length() const { return strlen(m_data); };

        void push_back(char c);

        char operator[](int i) {
            if (i < 0 || i > m_capacity) {
                throw "Out of string limits";
            };
            return m_data[i];
        }

        bool operator== (const string& X) const {
            return strcmp(m_data, X.m_data) == 0;
        }
        bool operator!= (const string& X) const {
            return strcmp(m_data, X.m_data) != 0;
        }
        bool operator< (const string& X) const {
            return strcmp(m_data, X.m_data) < 0;
        }

        friend std::ostream &operator<<(std::ostream &out, const string &s);

        friend std::istream &operator>>(std::istream &in, string &s);

        friend std::istream& getline(std::istream& in, string& str, char delim);
    };
}

#endif //ROOM_FOR_SALE_STRING_H
