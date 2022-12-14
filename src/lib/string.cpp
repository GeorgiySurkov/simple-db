#include "./string.h"
#include <iostream>

namespace SimpleDB {

    string::string(const char *source) {
        m_capacity = strlen(source) + 1;
        m_data = new char[m_capacity];
        memcpy(m_data, source, m_capacity);
    }

    string::string(size_t N) {
        m_capacity = N > 0 ? (N + 1) : 1;
        m_data = new char[m_capacity];
        m_data[0] = '\0';
    }

    string::string(const string &X) {
        m_capacity = X.m_capacity;
        m_data = new char[m_capacity];
        memcpy(m_data, X.m_data, m_capacity);
    }

    string::string(string &&X) noexcept {
        m_capacity = X.m_capacity;
        m_data = X.m_data;
        X.m_capacity = 0;
        X.m_data = nullptr;
    }

    string &string::operator=(const string &X) {
        if (this != &X) {
            delete[] m_data;
            m_capacity = X.m_capacity;
            m_data = new char[m_capacity];
            memcpy(m_data, X.m_data, m_capacity);
        }
        return *this;
    }

    string &string::operator=(string &&X) noexcept {
        if (this != &X) {
            delete[] m_data;
            m_capacity = X.m_capacity;
            m_data = X.m_data;
            X.m_capacity = 0;
            X.m_data = nullptr;
        }
        return *this;
    }

    string &string::operator+=(const string &right) {
        size_t len1 = size(), len2 = right.size();
        char *tmp = new char[len1 + len2 + 1];
        memcpy(tmp, m_data, len1);
        memcpy(tmp + len1, right.m_data, len2 + 1);
        delete[] m_data;
        m_data = tmp;
        m_capacity = len1 + len2 + 1;
        return *this;
    }

    void string::push_back(char c) {
        size_t len = size();
        if (len + 2 > m_capacity) {
            size_t new_capacity = m_capacity * 2 + 1;
            char *buff = new char[new_capacity];
            strcpy(buff, m_data);
            delete[] m_data;
            m_data = buff;
            m_capacity = new_capacity;
        }
        m_data[len] = c;
        m_data[len + 1] = '\0';
    }

    string operator+(const char *str, const string &B) {
        string A(str);
        size_t len1 = A.size(), len2 = B.size();
        char *tmp = new char[len1 + len2 + 1];
        memcpy(tmp, A.str(), len1);
        memcpy(tmp + len1, B.str(), len2 + 1);
        string result(tmp);
        delete[] tmp;
        return result;
    }

    std::ostream &operator<<(std::ostream &out, const string &s) {
        out << s.str();
        return out;
    }

    std::istream &operator>>(std::istream &in, string &s) {
        //TODO: handle if user enters more than 255 chars
        char buff[256];
        in >> buff;
        buff[sizeof(buff) - 1] = '\0';
        s = string(buff);
        return in;
    }

    std::istream& getline(std::istream& in, string& str, char delim = '\n') {
        //TODO: handle if line is more than 255 chars
        const int buff_size = 256;
        char *buff = new char[buff_size];
        in.getline(buff, buff_size, delim);
        delete[] str.m_data;
        str.m_data = buff;
        str.m_capacity = buff_size;
        return in;
    }

    void string::pop_back() {
        // TODO: remove expensive operation of getting string len
        size_t len = strlen(m_data);
        if (len > 0) {
            m_data[len - 1] = 0;
        }
    }

    string &ltrim_in_place(string &s) {
        auto curr = s.begin();
        while (std::isspace(*curr) && curr != s.end() ) {
            ++curr;
        }
        s = string(curr, s.end());
        return s;
    }

    string &rtrim_in_place(string &s) {
        auto curr = s.end();
        do {
            --curr;
        } while (std::isspace(*curr) && curr != s.begin());
        s = string(s.begin(), ++s.end());
        return s;
    }

}

