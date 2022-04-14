#include "DatabaseManager.h"

namespace SimpleDB {

    exit_code DatabaseManager::run_forever() {
        print_app_info();
        string command;
        while (true) {
            print_prompt();
            Statement s = m_statement_reader.read_statement();
            switch (m_statement_executor.execute_statement(s)) {
                case AbstractStatementExecutor::ExecutionResult::SUCCESS:
                    break;
                case AbstractStatementExecutor::ExecutionResult::SUCCESS_EXIT:
                    return 0;
            }
        }
    }

    void DatabaseManager::print_app_info() {
        m_out << "Room for sale command prompt (v1.0.0)" << std::endl;
    }

    void DatabaseManager::print_prompt() {
        m_out << ">> ";
    }

}