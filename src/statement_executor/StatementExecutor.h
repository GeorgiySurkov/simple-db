#ifndef ROOM_FOR_SALE_STATEMENTEXECUTOR_H
#define ROOM_FOR_SALE_STATEMENTEXECUTOR_H

#include "../AbstractStatementExecutor.h"

namespace SimpleDB {
    class StatementExecutor : public AbstractStatementExecutor {
    public:
        using AbstractStatementExecutor::AbstractStatementExecutor;
        ExecutionResult execute_statement(Statement s) final;
    };
}


#endif //ROOM_FOR_SALE_STATEMENTEXECUTOR_H
