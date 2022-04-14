#include "StatementReader.h"

namespace SimpleDB {
    Statement StatementReader::read_statement() {
        string command;
        m_in >> command;
        Statement result;
        if (command == "exit") {
            result.type = StatementType::EXIT;
            return result;
        }

    }
}