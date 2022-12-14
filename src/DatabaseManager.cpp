#include "DatabaseManager.h"
#include "DBException.h"

namespace SimpleDB {

    exit_code DatabaseManager::run_forever() {
        print_app_info();
        string command;
        while (true) {
            print_prompt();
            try {
                Statement s = m_statement_reader.read_statement();
                switch (m_statement_executor.execute_statement(s)) {
                    case AbstractStatementExecutor::ExecutionResult::SUCCESS:
                        break;
                    case AbstractStatementExecutor::ExecutionResult::SUCCESS_EXIT:
                        return 0;
                }
            } catch (DBException &e) {
                std::cout << e.what() << std::endl;
            }
            // commented for now
//            catch (std::exception &e) {
//                std::cout << e.what() << std::endl;
//            }
            catch (const char *e) {
                std::cout << e;
            }
//            catch (...) {
//                std::cout << "Unknown Error" << std::endl;
//            }
        }
    }

    void DatabaseManager::print_app_info() {
        m_out << "Room for sale command prompt (v1.0.0)" << std::endl;
    }

    void DatabaseManager::print_prompt() {
        m_out << ">> ";
    }

}