#include "StatementExecutor.h"

namespace SimpleDB {

    StatementExecutor::ExecutionResult StatementExecutor::execute_statement(const Statement &s) {
        switch (s.type) {
            case StatementType::EXIT:
                return ExecutionResult::SUCCESS_EXIT;
            case StatementType::LOAD:
                m_out << "loaded file " << s.file_name << std::endl; // TODO: add loading file functionality
                return ExecutionResult::SUCCESS;
            case StatementType::SAVE:
                m_out << "saved file " << s.file_name << std::endl; // TODO: add saving file functionality
                return ExecutionResult::SUCCESS;
            case StatementType::ADD:
                m_out << "added row" << std::endl; // TODO: add adding row functionality
                m_out << "Date: " << s.row_to_insert.date.day() << "." << s.row_to_insert.date.month() << "." << s.row_to_insert.date.year() << std::endl;
                m_out << "Rooms amount: " << s.row_to_insert.rooms_amount << std::endl;
                m_out << "Floor: " << s.row_to_insert.floor << std::endl;
                m_out << "Area: " << s.row_to_insert.area << std::endl;
                m_out << "Address: '" << s.row_to_insert.address << "'" << std::endl;
                m_out << "Price: '" << s.row_to_insert.price << std::endl;
                return ExecutionResult::SUCCESS;
        }
    }

}
