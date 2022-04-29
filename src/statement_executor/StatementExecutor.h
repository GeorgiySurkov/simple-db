#pragma once

#include "../AbstractStatementExecutor.h"
#include "AbstractDataContainer.h"

namespace SimpleDB {
    class StatementExecutor : public AbstractStatementExecutor {
        AbstractDataContainer &m_dc;

    public:
        explicit StatementExecutor(std::ostream &out, AbstractDataContainer &data_container) :
                AbstractStatementExecutor(out),
                m_dc(data_container) {}

        ExecutionResult execute_statement(const Statement &s) final;

    private:
        void print_row(std::ostream &os, const Row &row);

        void print_range(std::ostream &os, const AbstractDataContainer::Range &range);
    };
}
