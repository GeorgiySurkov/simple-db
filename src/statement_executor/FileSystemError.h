#pragma once

#include "StatementExecutingError.h"

namespace SimpleDB {

    class FileSystemError : public StatementExecutingError {
    public:
        using StatementExecutingError::StatementExecutingError;
    };

}
