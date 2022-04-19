#pragma once

#include <iostream>
#include "../statement.h"
#include "../AbstractStatementReader.h"

namespace SimpleDB {

    class StatementReader : public AbstractStatementReader {
        std::ios_base::iostate m_previous_exceptions_state;

    public:
        explicit StatementReader(std::istream &in) :
                AbstractStatementReader(in),
                m_previous_exceptions_state(m_in.exceptions()) {
            m_in.exceptions(std::istream::failbit);
        }

        ~StatementReader() {
            m_in.exceptions(m_previous_exceptions_state);
        }

        using AbstractStatementReader::AbstractStatementReader;

        Statement read_statement() final;

    private:
        void skip_bad_input();

        void read_exit_statement_params(Statement &result) { result.type = StatementType::EXIT; }

        void read_load_statement_params(Statement &result);

        void read_save_statement_params(Statement &result);

        void read_add_statement_params(Statement &result);

        void read_del_statement_params(Statement &result);

        void read_print_statement_params(Statement &result);

        void read_export_statement_params(Statement &result);

        void read_find_statement_params(Statement &result);
    };

}
