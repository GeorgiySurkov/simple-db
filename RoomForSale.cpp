#include <iostream>

#include "src/DatabaseManager.h"
#include "src/statement_reader/StatementReader.h"
#include "src/statement_executor/StatementExecutor.h"

int main(){
    SimpleDB::StatementReader reader(std::cin);
    SimpleDB::StatementExecutor executor(std::cout);
    SimpleDB::DatabaseManager db_manager(std::cin, std::cout, reader, executor);
    return db_manager.run_forever();
}
