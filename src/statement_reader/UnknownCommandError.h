#pragma once

#include "StatementReadingError.h"

namespace SimpleDB {

    class UnknownCommandError : public StatementReadingError {
    public:
        using StatementReadingError::StatementReadingError;
    };

}
