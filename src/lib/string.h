#pragma once

#include <iostream>
#include "Iterator.h"

namespace SimpleDB {

    class string {
        char *m_data;
        size_t m_capacity;

    public:

        //typedefs
        using iterator = Iterator<char>;
        using const_iterator = Iterator<const char>;

        string(const char *source = "");

        explicit string(size_t);

        template<typename It>
        string(It begin, It end) : string() {
            while (begin != end) {
                push_back(*begin);
                ++begin;
            }
        };

        string(const string &);

        string(string &&) noexcept;

        ~string() {
            delete[] m_data;
            m_capacity = 0;
            m_data = nullptr;
        }

        string &operator=(const string &);

        string &operator=(string &&) noexcept;

        [[nodiscard]] const char *str() const { return m_data; }

        string &operator+=(const string &);

        friend string operator+(string a, const string &b) {
            a += b;
            return a;
        }

        [[nodiscard]] size_t length() const { return strlen(m_data); };

        void push_back(char c);

        void pop_back();

        char operator[](size_t i) const {
            if (i < 0 || i > m_capacity) {
                throw "Out of string limits";
            };
            return m_data[i];
        }

        char &operator[](size_t i) {
            if (i < 0 || i > m_capacity) {
                throw "Out of string limits";
            };
            return m_data[i];
        }

        bool operator==(const string &X) const {
            return strcmp(m_data, X.m_data) == 0;
        }

        bool operator!=(const string &X) const {
            return strcmp(m_data, X.m_data) != 0;
        }

        bool operator<(const string &X) const {
            return strcmp(m_data, X.m_data) < 0;
        }

        friend std::ostream &operator<<(std::ostream &out, const string &s);

        friend std::istream &operator>>(std::istream &in, string &s);

        friend std::istream &getline(std::istream &in, string &str, char delim);

        iterator begin() { return iterator(m_data); }

        iterator end() { return iterator(m_data + strlen(m_data)); } // TODO: store string length to remove useless computations

        [[nodiscard]] const_iterator cbegin() const { return const_iterator(m_data); }

        [[nodiscard]] const_iterator cend() const { return const_iterator(m_data + strlen(m_data)); } // TODO: store string length to remove useless computations

        friend string &ltrim_in_place(string &s);

        friend string &rtrim_in_place(string &s);

        friend string &trim_in_place(string &s) { return ltrim_in_place(rtrim_in_place(s)); }

        friend string ltrim(string s) { return ltrim_in_place(s); }

        friend string rtrim(string s) { return rtrim_in_place(s); }

        friend string trim(string s) { return trim_in_place(s); }
    };
}
