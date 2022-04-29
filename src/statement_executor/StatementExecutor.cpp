#include "StatementExecutor.h"

#include <fstream>
#include "FileSystemError.h"

namespace SimpleDB {

    StatementExecutor::ExecutionResult StatementExecutor::execute_statement(const Statement &s) {
        switch (s.type) {
            case StatementType::EXIT:
                return ExecutionResult::SUCCESS_EXIT;
            case StatementType::LOAD:
                m_dc.load_data(s.file_path);
                return ExecutionResult::SUCCESS;
            case StatementType::SAVE:
                m_dc.save_data(s.file_path);
                return ExecutionResult::SUCCESS;
            case StatementType::ADD:
                print_row(m_out, m_dc.insert_row(s.row_to_insert));
                return ExecutionResult::SUCCESS;
            case StatementType::DEL:
                m_dc.delete_row(s.id);
                return ExecutionResult::SUCCESS;
            case StatementType::PRINT:
                if (s.rooms_amount == -1) {
                    print_range(m_out, m_dc.get_all_apartments());
                } else {
                    print_range(m_out, m_dc.get_apartments_with_n_rooms(s.rooms_amount));
                }
                return ExecutionResult::SUCCESS;
            case StatementType::EXPORT: {
                std::ofstream f(s.file_path.str(), std::ios::binary);
                if (f.fail()) {
                    throw FileSystemError("Error while opening file '" + s.file_path + "'");
                }
                print_range(f, m_dc.get_all_apartments());
                return ExecutionResult::SUCCESS;
            }
            case StatementType::FIND:
                print_range(m_out, m_dc.find_apartment_for_exchange(s.id));
                return ExecutionResult::SUCCESS;
            case StatementType::CLEAR:
                m_dc.clear();
                return ExecutionResult::SUCCESS;
        }
    }

    void StatementExecutor::print_row(std::ostream &os, const Row &row) {
        os << row.id << ", "
           << to_string(row.date) << ", "
           << row.price << ", "
           << row.rooms_amount << ", "
           << row.floor << ", "
           << row.area << ", "
           << row.address << std::endl;
    }

    void StatementExecutor::print_range(std::ostream &os, const AbstractDataContainer::Range &range) {
        for (auto curr = range.begin; curr != range.end; ++curr) {
            print_row(os, *curr);
        }
    }

}
