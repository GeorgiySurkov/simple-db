#ifndef ROOM_FOR_SALE_ABSTRACTSTATEMENTEXECUTOR_H
#define ROOM_FOR_SALE_ABSTRACTSTATEMENTEXECUTOR_H

#include "iostream"
#include "statement.h"

namespace SimpleDB {
    class AbstractStatementExecutor {
    protected:
        std::ostream &m_out;
    public:
        explicit AbstractStatementExecutor(std::ostream &out) : m_out(out) {}

        enum class ExecutionResult {
            SUCCESS,
            SUCCESS_EXIT,
        };

        virtual ExecutionResult execute_statement(const Statement s) = 0;
    };
}

#endif //ROOM_FOR_SALE_ABSTRACTSTATEMENTEXECUTOR_H
