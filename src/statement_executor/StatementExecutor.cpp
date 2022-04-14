#include "StatementExecutor.h"

namespace SimpleDB {
    StatementExecutor::ExecutionResult StatementExecutor::execute_statement(const Statement s) {
        switch (s.type) {
            case StatementType::EXIT:
                return ExecutionResult::SUCCESS_EXIT;
        }
    }
}