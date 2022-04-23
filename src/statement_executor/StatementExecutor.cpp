#include "StatementExecutor.h"

namespace SimpleDB {

    StatementExecutor::ExecutionResult StatementExecutor::execute_statement(const Statement &s) {
        switch (s.type) {
            case StatementType::EXIT:
                return ExecutionResult::SUCCESS_EXIT;
            case StatementType::LOAD:
//                m_out << "loaded file " << s.file_name << std::endl; // TODO: add loading file functionality
                m_dc.load_data(s.file_name);
                return ExecutionResult::SUCCESS;
            case StatementType::SAVE:
//                m_out << "saved file " << s.file_name << std::endl; // TODO: add saving file functionality
                m_dc.save_data(s.file_name);
                return ExecutionResult::SUCCESS;
            case StatementType::ADD:
//                m_out << "added row" << std::endl; // TODO: add adding row functionality
//                m_out << "Date: " << s.row_to_insert.date.day() << "." << s.row_to_insert.date.month() << "."
//                      << s.row_to_insert.date.year() << std::endl;
//                m_out << "Rooms amount: " << s.row_to_insert.rooms_amount << std::endl;
//                m_out << "Floor: " << s.row_to_insert.floor << std::endl;
//                m_out << "Area: " << s.row_to_insert.area << std::endl;
//                m_out << "Address: '" << s.row_to_insert.address << "'" << std::endl;
//                m_out << "Price: '" << s.row_to_insert.price << std::endl;
                print_row(m_dc.insert_row(s.row_to_insert));
                return ExecutionResult::SUCCESS;
            case StatementType::DEL:
//                m_out << "removed row with id " << s.id << std::endl;
                m_dc.delete_row(s.id);
                return ExecutionResult::SUCCESS;
            case StatementType::PRINT:
//                m_out << "printed rows with rooms_amount " << s.rooms_amount << std::endl;
                if (s.rooms_amount == -1) {
                    print_range(m_dc.get_all_apartments());
                } else {
                    print_range(m_dc.get_apartments_with_n_rooms(s.rooms_amount));
                }
                return ExecutionResult::SUCCESS;
            case StatementType::EXPORT:
//                m_out << "exported to file '" << s.file_name << "'" << std::endl;
                m_dc.export_to_text(s.file_name);
                return ExecutionResult::SUCCESS;
            case StatementType::FIND:
//                m_out << "found room for swap for room with id " << s.id << std::endl;
                print_range(m_dc.find_apartment_for_exchange(s.id));
                return ExecutionResult::SUCCESS;
        }
    }

    void StatementExecutor::print_row(const Row &row) {
        m_out << row.id << ", "
              << to_string(row.date) << ", "
              << row.price << ", "
              << row.rooms_amount << ", "
              << row.floor << ", "
              << row.area << ", "
              << row.address << std::endl;
    }

    void StatementExecutor::print_range(const AbstractDataContainer::Range &range) {
        for (auto curr = range.begin; curr != range.end; ++curr) {
            print_row(*curr);
        }
    }

}
