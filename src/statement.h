#pragma once

#include "lib/string.h"
#include "lib/Date.h"

namespace SimpleDB {
    enum class StatementType {
        LOAD,
        SAVE,
        ADD,
        DEL,
        PRINT,
        EXPORT,
        FIND,
        EXIT,
    };

    typedef long long ID;

    struct Row {
        ID id;
        Date date;
        int rooms_amount;
        int floor;
        int area;
        string address;
        int price;
    };

    struct Statement {
        StatementType type;

        // used by StatementType::LOAD, StatementType::SAVE, StatementType::EXPORT
        string file_name;

        // used by StatementType::ADD
        Row row_to_insert;

        // used by StatementType::DEL, StatementType::FIND
        ID id;

        // used by StatementType::PRINT
        int rooms_amount;
    };
}
