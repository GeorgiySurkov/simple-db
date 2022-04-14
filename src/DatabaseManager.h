#ifndef ROOM_FOR_SALE_DATABASEMANAGER_H
#define ROOM_FOR_SALE_DATABASEMANAGER_H

#include <iostream>
#include "lib/string.h"
#include "AbstractStatementReader.h"
#include "AbstractStatementExecutor.h"

namespace SimpleDB {

    using exit_code = int;

    class DatabaseManager {
        std::istream &m_in;
        std::ostream &m_out;
        AbstractStatementReader &m_statement_reader;
        AbstractStatementExecutor &m_statement_executor;

    public:
        DatabaseManager(
                std::istream &in,
                std::ostream &out,
                AbstractStatementReader &statement_reader,
                AbstractStatementExecutor &statement_executor
        ) :
                m_in(in),
                m_out(out),
                m_statement_reader(statement_reader),
                m_statement_executor(statement_executor) {}

        exit_code run_forever();

    private:
        void print_app_info();

        void print_prompt();
    };

}

#endif //ROOM_FOR_SALE_DATABASEMANAGER_H
