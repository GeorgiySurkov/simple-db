#include <iostream>

#include "src/DatabaseManager.h"
#include "src/statement_reader/StatementReader.h"
#include "src/statement_executor/StatementExecutor.h"
#include "src/statement_executor/DataContainer.h"

using SimpleDB::StatementReader;
using SimpleDB::DataContainer;
using SimpleDB::StatementExecutor;
using SimpleDB::DatabaseManager;

int main() {
    StatementReader reader(std::cin);
    DataContainer data_container;
    StatementExecutor executor(std::cout, data_container);
    DatabaseManager db_manager(std::cin, std::cout, reader, executor);
    return db_manager.run_forever();
}
