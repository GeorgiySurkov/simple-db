#pragma once

namespace SimpleDB {

    template<typename T>
    class AbstractIterator {
    public:
        AbstractIterator() {}

        virtual ~AbstractIterator() {}

        virtual void operator++() = 0;

        virtual void operator--() = 0;

        virtual const T &operator*() const = 0;

        virtual AbstractIterator *clone() const = 0;

        bool operator==(const AbstractIterator &o) const {
//            std::cout << typeid(*this).name() << " " << typeid(o).name() << std::endl;
            return this->type() == o.type() && equal(o);
        }

        inline bool operator!=(const AbstractIterator &o) const {
            return !(*this == 0);
        }

    protected:
        virtual bool equal(const AbstractIterator &o) const = 0;

        // TODO: remove dirty hack with IteratorType
        enum class IteratorType {
            ABSTRACT,
            LINEAR,
            FILTER,
        };

        virtual IteratorType type() const { return IteratorType::ABSTRACT; }
    };

    template<typename T>
    class Iterator {
    public:
        explicit Iterator(AbstractIterator<T> *it = nullptr) : m_itr(it) {}

        ~Iterator() { delete m_itr; }

        Iterator(const Iterator &o) : m_itr(o.m_itr->clone()) {}

        Iterator(Iterator &&o) noexcept {
            m_itr = o.m_itr;
            o.m_itr = nullptr;
        }

        Iterator &operator=(const Iterator &o) {
            if (this == &o) return *this;
            delete m_itr;
            m_itr = o.m_itr->clone();
            return *this;
        }

        Iterator &operator=(Iterator &&o) noexcept {
            if (this == &o) return *this;
            m_itr = o.m_itr;
            o.m_itr = nullptr;
            return *this;
        }

        Iterator &operator++() {
            ++(*m_itr);
            return *this;
        }

        Iterator &operator--() {
            --(*m_itr);
            return *this;
        }

        const T &operator*() const { return *(*m_itr); }

        const T *operator->() const { return &(*(*m_itr)); }

        bool operator==(const Iterator &o) const {
            return (m_itr == o.m_itr) || (*m_itr == *o.m_itr);
        }

        inline bool operator!=(const Iterator &o) const { return !(*this == o); }

    protected:
        AbstractIterator<T> *m_itr;
    };

    template<typename T>
    class LinearIterator final : public AbstractIterator<T> {
        T *m_ptr;

    public:
        explicit LinearIterator(T *ptr = nullptr) : AbstractIterator<T>(), m_ptr(ptr) {}

        ~LinearIterator() = default;

        void operator++() {
            ++m_ptr;
        }

        void operator--() {
            --m_ptr;
        }

        const T &operator*() const {
            return *m_ptr;
        }

        AbstractIterator<T> *clone() const {
            return new LinearIterator<T>(*this);
        }

    protected:
        bool equal(const AbstractIterator<T> &o) const {
            const auto &other = static_cast<const LinearIterator &>(o);
            return m_ptr == other.m_ptr;
        }

        typename AbstractIterator<T>::IteratorType type() const { return AbstractIterator<T>::IteratorType::LINEAR; }
    };
}