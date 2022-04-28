#pragma once

#include <fstream>
#include "AbstractDataContainer.h"
#include "../lib/RedBlackTree.h"
#include "../lib/FilterIterator.h"

namespace SimpleDB {

    class DataContainer final : public AbstractDataContainer {
        ID m_last_id;
        Row *m_container;
        size_t m_len;
        size_t m_cap;


    public:
        DataContainer() : m_cap(256), m_len(0), m_container(nullptr), m_last_id(0) { m_container = new Row[m_cap]; }

        ~DataContainer() = default;

        void load_data(const string &file_path);

        void save_data(const string &file_path);

        const Row &insert_row(const Row &row);

        void delete_row(ID key);

        Range get_all_apartments();

        Range get_apartments_with_n_rooms(int n);

        void export_to_text(const string &file_path);

        Range find_apartment_for_exchange(ID key);

    private:
        void reserve(size_t new_cap);

        void push_back(const Row &row);

        void erase(size_t index);

        void clear();

        bool empty();

        size_t find_by_id(ID id);

        inline Iterator<Row> create_iterator(Row *p) { return Iterator<Row>(new LinearIterator<Row>(p)); }

        inline Iterator<Row> begin() { return create_iterator(m_container); }

        inline Iterator<Row> end() { return create_iterator(m_container + m_len); }

        template<typename Predicate>
        inline Iterator<Row> create_filter_iterator(const Iterator<Row> &p, Predicate predicate) {
            return Iterator<Row>(new FilterIterator<Row, Predicate>(
                                         begin(),
                                         p,
                                         end(),
                                         predicate
                                 )
            );
        }
    };

}
