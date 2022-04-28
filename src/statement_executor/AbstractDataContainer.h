#pragma once

#include "../lib/string.h"
#include "../statement.h"

namespace SimpleDB {

    class AbstractDataContainer {
    public:
        struct Range {
            Iterator<Row> begin;
            Iterator<Row> end;
        };

        virtual void load_data(const string &file_path) = 0;

        virtual void save_data(const string &file_path) = 0;

        virtual const Row &insert_row(const Row &row) = 0;

        virtual void delete_row(ID key) = 0;

        virtual Range get_all_apartments() = 0;

        virtual Range get_apartments_with_n_rooms(int n) = 0;

        virtual Range find_apartment_for_exchange(ID key) = 0;

        virtual ~AbstractDataContainer() = default;

    };

}