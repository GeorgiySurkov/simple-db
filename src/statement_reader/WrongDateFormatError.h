#pragma once

#include "../DBException.h"

namespace SimpleDB {
    class WrongDateFormatError : public DBException {
        using DBException::DBException;
    };
}
