#pragma once

#include "../lib/Date.h"

namespace SimpleDB {

    Date parse_date(const string &s, char delim = '.');

    string trim(const string &s);

}
