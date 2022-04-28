#pragma once

#include "Iterator.h"

namespace SimpleDB {

    template<typename T, typename Predicate>
    class FilterIterator : public AbstractIterator<T> {
        Iterator<T> m_left_border;
        Iterator<T> m_curr;
        Iterator<T> m_right_border;
        Predicate m_predicate;

    public:
        FilterIterator(
                const Iterator<T> &left_border,
                const Iterator<T> &begin,
                const Iterator<T> &right_border,
                const Predicate &predicate
        ) :
                m_left_border(left_border),
                m_curr(begin),
                m_right_border(right_border),
                m_predicate(predicate) {}

        ~FilterIterator() = default;

        void operator++() {
            do {
                ++m_curr;
            } while (m_curr != m_right_border && !m_predicate(*m_curr));
        }

        void operator--() {
            do {
                --m_curr;
            } while (m_curr != m_left_border && !m_predicate(*m_curr));
        }

        const T &operator*() const {
            return *m_curr;
        }

        AbstractIterator<T> *clone() const {
            return new FilterIterator(*this);
        }

    protected:
        bool equal(const AbstractIterator<T> &o) const {
            const auto &other = static_cast<const FilterIterator &>(o);
            return m_curr == other.m_curr;
        }

        typename AbstractIterator<T>::IteratorType type() const { return AbstractIterator<T>::IteratorType::FILTER; }
    };

}
