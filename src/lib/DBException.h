#ifndef ROOM_FOR_SALE_DBEXCEPTION_H
#define ROOM_FOR_SALE_DBEXCEPTION_H

#include "./string.h"

namespace SimpleDB {
    class DBException {
        string str;

    public:
        explicit DBException(string s) : str(std::move(s)) {}

        [[nodiscard]] const string &get_error_text() const { return str; }
    };
}


#endif //ROOM_FOR_SALE_DBEXCEPTION_H
