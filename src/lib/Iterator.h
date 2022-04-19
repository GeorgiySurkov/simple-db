#pragma once

namespace SimpleDB {

    template<typename T>
    class Iterator {
    public:

        using value_type = T;
        using pointer = T *;
        using reference = T &;

    public:

        explicit Iterator(T *ptr = nullptr) { m_ptr = ptr; }

        Iterator(const Iterator<T> &it) = default;

        ~Iterator() = default;

        virtual Iterator<T> &operator=(const Iterator<T> &it) = default;

        virtual Iterator<T> &operator=(T *ptr) {
            m_ptr = ptr;
            return (*this);
        }

        explicit operator bool() const {
            if (m_ptr)
                return true;
            else
                return false;
        }

        bool operator==(const Iterator<T> &it) const { return (m_ptr == it.getConstPtr()); }

        bool operator!=(const Iterator<T> &it) const { return (m_ptr != it.getConstPtr()); }

        virtual Iterator<T> &operator++() {
            ++m_ptr;
            return (*this);
        }

        virtual Iterator<T> &operator--() {
            --m_ptr;
            return (*this);
        }

        virtual Iterator<T> operator++(int) {
            auto temp(*this);
            ++m_ptr;
            return temp;
        }

        virtual Iterator<T> operator--(int) {
            auto temp(*this);
            --m_ptr;
            return temp;
        }

        T &operator*() { return *m_ptr; }

        const T &operator*() const { return *m_ptr; }

        T *operator->() { return m_ptr; }

        const T *getConstPtr() const { return m_ptr; }

    protected:

        T *m_ptr;
    };
}
