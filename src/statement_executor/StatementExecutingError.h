#pragma once

#include "../DBException.h"

namespace SimpleDB {

    class StatementExecutingError : public DBException {
    public:
        using DBException::DBException;
    };

}
