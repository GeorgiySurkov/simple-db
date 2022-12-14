#pragma once

#include <fstream>
#include "AbstractDataContainer.h"
#include "../lib/FilterIterator.h"

namespace SimpleDB {

    class DataContainer final : public AbstractDataContainer {
        ID m_last_id;
        Row *m_container;
        size_t m_len;
        size_t m_cap;

    public:
        DataContainer() : m_cap(256), m_len(0), m_container(nullptr), m_last_id(0) { m_container = new Row[m_cap]; }

        ~DataContainer() final { delete[] m_container; };

        void load_data(const string &file_path) final;

        void save_data(const string &file_path) final;

        const Row &insert_row(const Row &row) final;

        void delete_row(ID key) final;

        Range get_all_apartments() final;

        Range get_apartments_with_n_rooms(int n) final;

        Range find_apartment_for_exchange(ID key) final;

        void clear();

    private:
        void reserve(size_t new_cap);

        template<typename Comparator>
        void sort(const Comparator &comp);

        void push_back(const Row &row);

        void erase(size_t index);

        bool empty() const;

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
