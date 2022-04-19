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

        void read_exit_statement_params(Statement &result) { result.type = StatementType::EXIT; }

        void read_load_statement_params(Statement &result);

        void read_save_statement_params(Statement &result);

        void read_add_statement_params(Statement &result);
    };
}

#endif //ROOM_FOR_SALE_STATEMENTREADER_H
