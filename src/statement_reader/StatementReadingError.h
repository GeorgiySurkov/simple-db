#ifndef ROOM_FOR_SALE_STATEMENTREADINGERROR_H
#define ROOM_FOR_SALE_STATEMENTREADINGERROR_H

#include <utility>

#include "../DBException.h"

namespace SimpleDB {
    class StatementReadingError : public DBException {
    public:
        using DBException::DBException;
    };
}


#endif //ROOM_FOR_SALE_STATEMENTREADINGERROR_H
