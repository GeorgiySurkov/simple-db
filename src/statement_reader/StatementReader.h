#ifndef ROOM_FOR_SALE_STATEMENTREADER_H
#define ROOM_FOR_SALE_STATEMENTREADER_H

#include <iostream>
#include "../statement.h"
#include "../AbstractStatementReader.h"

namespace SimpleDB {
    class StatementReader : public AbstractStatementReader {
    public:
        using AbstractStatementReader::AbstractStatementReader;
        Statement read_statement() final;
    };
}

#endif //ROOM_FOR_SALE_STATEMENTREADER_H
