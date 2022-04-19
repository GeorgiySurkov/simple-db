#pragma once

#include "iostream"
#include "statement.h"

namespace SimpleDB {
    class AbstractStatementReader {
    protected:
        std::istream &m_in;
    public:
        explicit AbstractStatementReader(std::istream &in) : m_in(in) {}

        virtual Statement read_statement() = 0;
    };
}
