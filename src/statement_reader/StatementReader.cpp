#include "StatementReader.h"

#include "StatementReadingError.h"

namespace SimpleDB {
    Statement StatementReader::read_statement() {
        string command;
        m_in >> command;
        Statement result;
        if (command == "exit") {
            result.type = StatementType::EXIT;
            return result;
        } else if (command == "load") {
            result.type = StatementType::LOAD;
            m_in >> result.file_name;
            return result;
        } else if (command == "save") {
            result.type = StatementType::SAVE;
            m_in >> result.file_name;
            return result;
        } else {
            throw StatementReadingError("Unknown command: " + command);
        }
    }
}