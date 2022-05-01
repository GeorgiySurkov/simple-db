#include "DataContainer.h"

#include <fstream>
#include "FileSystemError.h"

#define read_value(fs, value) \
    (fs).read((char*) &(value), sizeof(value))

#define write_value(fs, value) \
    (fs).write((char*) &(value), sizeof(value))


namespace SimpleDB {

    void DataContainer::load_data(const string &file_path) {
        clear();
        std::ifstream f(file_path.str(), std::ios::binary);
        if (f.fail()) {
            throw FileSystemError("Error while opening file '" + file_path + "'");
        }
        read_value(f, m_last_id);
        if (f.fail()) {
            throw FileSystemError("Error while reading file");
        }
        Row curr;
        while (read_value(f, curr.id)) {
            read_value(f, curr.date);
            read_value(f, curr.rooms_amount);
            read_value(f, curr.floor);
            read_value(f, curr.area);
            read_value(f, curr.address);
            read_value(f, curr.price);
            if (f.fail()) {
                clear();
                throw FileSystemError("Error while reading file");
            }
            push_back(curr);
        }
    }

    void DataContainer::save_data(const string &file_path) {
        if (empty()) {
            throw StatementExecutingError("You should load data from file before saving");
        }
        std::ofstream f(file_path.str(), std::ios::binary);
        if (f.fail()) {
            throw FileSystemError("Error while opening file '" + file_path + "'");
        }
        write_value(f, m_last_id);
        if (f.fail()) {
            throw FileSystemError("Error while writing to file");
        }
        for (size_t i = 0; i < m_len; ++i) {
            const Row &curr = m_container[i];
            write_value(f, curr.id);
            write_value(f, curr.date);
            write_value(f, curr.rooms_amount);
            write_value(f, curr.floor);
            write_value(f, curr.area);
            write_value(f, curr.address);
            write_value(f, curr.price);
            if (f.fail()) {
                throw FileSystemError("Error while writing to file");
            }
        }
    }

    const Row &DataContainer::insert_row(const Row &row) {
        Row copy = row;
        copy.id = ++m_last_id;
        push_back(copy);
        sort([](const Row &lhs, const Row &rhs) {
            return lhs.price < rhs.price;
        });
        return m_container[m_len - 1];
    }

    void DataContainer::delete_row(ID key) {
        if (empty()) {
            throw StatementExecutingError("Can't delete row without any data");
        }
        auto index = find_by_id(key);
        if (index == -1) {
            char err[256];
            snprintf(err, 256, "Row with ID %lld doesn't exist", key);
            throw StatementExecutingError(err);
        }
        erase(find_by_id(key));
    }

    AbstractDataContainer::Range DataContainer::get_all_apartments() {
        return {
                create_iterator(m_container),
                create_iterator(m_container + m_len)
        };
    }

    AbstractDataContainer::Range DataContainer::get_apartments_with_n_rooms(int n) {
        auto filter = [n](const Row &row) {
            return row.rooms_amount == n;
        };
        auto first_it = begin();
        while (first_it != end() && !filter(*first_it)) {
            ++first_it;
        }
        return {
                create_filter_iterator(first_it, filter),
                create_filter_iterator(end(), filter)
        };
    }

    AbstractDataContainer::Range DataContainer::find_apartment_for_exchange(ID key) {
        auto index = find_by_id(key);
        if (index == -1) {
            char err[256];
            snprintf(err, 256, "Row with ID %lld doesn't exist", key);
            throw StatementExecutingError(err);
        }
        const Row &row_for_exchange = m_container[index];
        auto filter = [&row_for_exchange](const Row &row) {
            return row.rooms_amount == row_for_exchange.rooms_amount &&
                   row.floor == row_for_exchange.floor &&
                   row_for_exchange.price * 8 / 10 <= row.price &&
                   row.price <= row_for_exchange.price * 12 / 10;
        };
        auto first_it = begin();
        while (first_it != end() && !filter(*first_it)) {
            ++first_it;
        }
        return {
                create_filter_iterator(first_it, filter),
                create_filter_iterator(end(), filter)
        };
    }

    void DataContainer::reserve(size_t new_cap) {
        if (new_cap <= m_cap) return;
        Row *tmp = new Row[new_cap];
        for (size_t i = 0; i < m_cap; ++i)
            tmp[i] = m_container[i];
        delete[] m_container;
        m_container = tmp;
        m_cap = new_cap;
    }

    void DataContainer::push_back(const Row &row) {
        if (m_len + 1 > m_cap) {
            reserve((m_cap + 1) * 2);
        }
        m_container[m_len] = row;
        ++m_len;
    }

    void DataContainer::erase(size_t index) {
        if (index >= m_len) {
            throw StatementExecutingError("Index out of range");
        }
        for (size_t i = index + 1; i < m_len - 1; ++i) {
            m_container[i - 1] = m_container[i];
        }
        --m_len;
    }

    size_t DataContainer::find_by_id(ID id) {
        for (size_t i = 0; i < m_len; ++i) {
            if (m_container[i].id == id) {
                return i;
            }
        }
        return -1;
    }

    void DataContainer::clear() {
        m_len = 0;
        m_last_id = 0;
    }

    bool DataContainer::empty() const {
        return m_len == 0;
    }

    template<typename Comparator>
    void _merge(
            Row *M,
            int first,
            int middle,
            int last,
            unsigned long long &count_less,
            unsigned long long &count_eq,
            Comparator &comp
    ) {
        int size = last - first + 1;
        Row *tmp = new Row[size];
        int start1 = first, end1 = middle, start2 = middle + 1, end2 = last;
        int i = 0;
        while (start1 <= end1 && start2 <= end2) {
            ++count_less;
            ++count_eq;
            if (comp(M[start1], M[start2]))
                tmp[i++] = M[start1++];
            else
                tmp[i++] = M[start2++];
        }
        while (start1 <= end1) {
            tmp[i++] = M[start1++];
            ++count_eq;
        }
        while (start2 <= end2) {
            tmp[i++] = M[start2++];
            ++count_eq;
        }
        i = 0;
        while (first <= last) {
            M[first++] = tmp[i++];
            ++count_eq;
        }
        delete[] tmp;
    }

    template<typename Comparator>
    void _split(
            Row *M,
            int first,
            int last,
            unsigned long long &count_less,
            unsigned long long &count_eq,
            Comparator &comp
    ) {
        if (first < last) {
            int middle = first + (last - first) / 2;
            _split(M, first, middle, count_less, count_eq, comp);
            _split(M, middle + 1, last, count_less, count_eq, comp);
            _merge(M, first, middle, last, count_less, count_eq, comp);
        }
    }

    template<typename Comparator>
    void DataContainer::sort(const Comparator &comp) {
        // Merge sort
        unsigned long long count_less = 0, count_eq = 0;
        _split(m_container, 0, m_len - 1, count_less, count_eq, comp);
    }

}
