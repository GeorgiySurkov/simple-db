#pragma once

#include "StatementReadingError.h"

namespace SimpleDB {

    class WrongDateFormatError : public StatementReadingError {
    public:
        using StatementReadingError::StatementReadingError;
    };

}
