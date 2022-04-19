#include "StatementReader.h"

#include "UnknownCommandError.h"
#include "helpers.h"

namespace SimpleDB {

    Statement StatementReader::read_statement() {
        string command;
        m_in >> command;
        Statement result;
        if (command == "exit") {
            read_exit_statement_params(result);
        } else if (command == "load") {
            read_load_statement_params(result);
        } else if (command == "save") {
            read_save_statement_params(result);
        } else if (command == "add") {
            read_add_statement_params(result);
        } else {
            throw UnknownCommandError(command);
        }
        return result;
    }

    void StatementReader::read_load_statement_params(Statement &result) {
        result.type = StatementType::LOAD;
        m_in >> result.file_name;
    }

    void StatementReader::read_save_statement_params(Statement &result) {
        result.type = StatementType::SAVE;
        m_in >> result.file_name;
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
        result.row_to_insert.address = trim(buff);

        // reading price
        m_in >> result.row_to_insert.price;
    }
}