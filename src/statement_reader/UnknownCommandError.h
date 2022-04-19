#pragma once

#include <utility>

#include "../DBException.h"

namespace SimpleDB {
    class UnknownCommandError : public DBException {
    public:
        using DBException::DBException;
    };
}
