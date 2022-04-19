#pragma once

#include "../AbstractStatementExecutor.h"

namespace SimpleDB {
    class StatementExecutor : public AbstractStatementExecutor {
    public:
        using AbstractStatementExecutor::AbstractStatementExecutor;
        ExecutionResult execute_statement(const Statement &s) final;
    };
}
