#include "StatementReader.h"

#include "UnknownCommandError.h"
#include "WrongStatementFormatError.h"
#include "helpers.h"

namespace SimpleDB {

    Statement StatementReader::read_statement() {
        Statement result;
        try {
            string command;
            m_in >> command;
            if (command == "exit") {
                read_exit_statement_params(result);
            } else if (command == "load") {
                read_load_statement_params(result);
            } else if (command == "save") {
                read_save_statement_params(result);
            } else if (command == "add") {
                read_add_statement_params(result);
            } else if (command == "del") {
                read_del_statement_params(result);
            } else if (command == "print") {
                read_print_statement_params(result);
            } else if (command == "export") {
                read_export_statement_params(result);
            } else if (command == "find") {
                read_find_statement_params(result);
            } else if (command == "clear") {
                read_clear_statement_params(result);
            } else {
                throw UnknownCommandError("Unknown command: " + command);
            }
        } catch (const std::ios_base::failure &e) {
            skip_bad_input();
            throw WrongStatementFormatError("Wrong Statement format error"); // TODO: add more meaningful information
        } catch (const StatementReadingError &e) {
            skip_bad_input();
            throw;
        }
        return result;
    }

    void StatementReader::read_load_statement_params(Statement &result) {
        result.type = StatementType::LOAD;
        m_in >> result.file_path;
    }

    void StatementReader::read_save_statement_params(Statement &result) {
        result.type = StatementType::SAVE;
        m_in >> result.file_path;
    }

    void StatementReader::read_add_statement_params(Statement &result) {
        // statement in format "add <date>, <rooms_amount>, <floor>, <area>, <address>, <price>"
        result.type = StatementType::ADD;
        string buff;

        // reading date
        getline(m_in, buff, ',');
        result.row_to_insert.date = parse_date(trim(buff));

        // reading rooms amount
        m_in >> result.row_to_insert.rooms_amount;
        getline(m_in, buff, ','); // get rid of trailing comma

        // reading floor
        m_in >> result.row_to_insert.floor;
        getline(m_in, buff, ',');

        // reading area
        m_in >> result.row_to_insert.area;
        getline(m_in, buff, ',');

        // reading address
        getline(m_in, buff, ',');
        trim_in_place(buff);
        if (buff.size() > 64) {
            throw WrongStatementFormatError("Address can't be longer than 64 chars: " + buff);
        }
        strncpy(result.row_to_insert.address, buff.str(), 65);

        // reading price
        m_in >> result.row_to_insert.price;
    }

    void StatementReader::read_del_statement_params(Statement &result) {
        result.type = StatementType::DEL;
        m_in >> result.id;
    }

    void StatementReader::read_print_statement_params(Statement &result) {
        result.type = StatementType::PRINT;

        // Dirty hack to read possible argument of print command
        // Possible solution: require user to enter terminating char at the end of each statement (for e.g. semicolon)
        // TODO: remove hack

        string buff;
        getline(m_in, buff, '\n');
        buff = trim(buff);
        try {
            result.rooms_amount = std::stoi(buff.str());
        } catch (...) {
            result.rooms_amount = -1;
        }
    }

    void StatementReader::read_export_statement_params(Statement &result) {
        result.type = StatementType::EXPORT;
        m_in >> result.file_path;
    }

    void StatementReader::read_find_statement_params(Statement &result) {
        result.type = StatementType::FIND;
        m_in >> result.id;
    }

    void StatementReader::skip_bad_input() {
        m_in.clear();
        m_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void StatementReader::read_clear_statement_params(Statement &result) {
        result.type = StatementType::CLEAR;
    }
}