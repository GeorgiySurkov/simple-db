#pragma once

#include "../DBException.h"

namespace SimpleDB {

    class StatementReadingError : public DBException {
    public:
        using DBException::DBException;
    };

}
