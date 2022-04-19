#pragma once

#include "lib/string.h"

namespace SimpleDB {
    class DBException {
        string str;

    public:
        explicit DBException(string s) : str(std::move(s)) {}

        [[nodiscard]] virtual const string &what() const { return str; }
    };
}
