#pragma once

#include "iostream"
#include "statement.h"

namespace SimpleDB {
    class AbstractStatementExecutor {
    protected:
        std::ostream &m_out;
    public:
        explicit AbstractStatementExecutor(std::ostream &out) : m_out(out) {}

        virtual ~AbstractStatementExecutor() = default;

        enum class ExecutionResult {
            SUCCESS,
            SUCCESS_EXIT,
        };

        virtual ExecutionResult execute_statement(const Statement &s) = 0;
    };
}
