#pragma once

#include "./StatementReadingError.h"

namespace SimpleDB {

    class WrongStatementFormatError : public StatementReadingError {
    public:
        using StatementReadingError::StatementReadingError;
    };

}
