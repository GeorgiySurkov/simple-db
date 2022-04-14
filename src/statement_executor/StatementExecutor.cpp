#include "StatementExecutor.h"

namespace SimpleDB {
    StatementExecutor::ExecutionResult StatementExecutor::execute_statement(const Statement &s) {
        switch (s.type) {
            case StatementType::EXIT:
                return ExecutionResult::SUCCESS_EXIT;
            case StatementType::LOAD:
                m_out << "loaded file " << s.file_name << std::endl;
                return ExecutionResult::SUCCESS;
            case StatementType::SAVE:
                m_out << "saved file " << s.file_name << std::endl;
        }
    }
}