#pragma once
/*
#include "Iterator.h"

namespace SimpleDB {

    template<typename T> // TODO: add comparator as a template parameter
    class RedBlackTree {

        class Node {
        public:
            Node *parent = nullptr;
            Node *left = nullptr;
            Node *right = nullptr;
            bool is_red = false;
            T value;

            Node(bool isRed, T value) : is_red(isRed), value(value) {};

            explicit Node(Node *parent) : parent(parent) {};

            Node() = default;

            Node *min() {
                Node *curr = this;
                while (curr->left) {
                    curr = curr->left;
                }
                return curr;
            }

            Node *max() {
                Node *curr = this;
                while (curr->right) {
                    curr = curr->right;
                }
                return curr;
            }

            Node *next() {
                if (right) {
                    return right->min();
                }
                Node *p = parent, *now = this;
                while (p) {
                    if (now == p->left) break;
                    now = p;
                    p = p->parent;
                }
                return p;
            }

            Node *prev() {
                if (left) {
                    return left->max();
                }
                Node *p = parent, *now = this;
                while (p) {
                    if (now == p->right) break;
                    now = p;
                    p = p->parent;
                }
                return p;
            }

            bool is_father_left_child() { return parent == parent->parent->left; }
        };

        class iterator final : public AbstractIterator<T> {
            Node *m_curr_node;

        public:
            iterator(Node *node) : m_curr_node(node) {}

            ~iterator() = default;

            void operator++() {
                m_curr_node = m_curr_node->next();
            }

            void operator--() {
                m_curr_node = m_curr_node->prev();
            }

            const T &operator*() const {
                return m_curr_node->value;
            }

            AbstractIterator<T> *clone() const {
                return new iterator(*this);
            }

        protected:
            bool equal(const AbstractIterator<T> &o) const {
                const auto &other = static_cast<const iterator &>(o);
                return m_curr_node == other.m_curr_node;
            }
        };

        Node *root = nullptr;

    public:
        RedBlackTree() = default;

        Iterator<T> insert(const T &value);

        size_t erase(const T &value);

        Iterator<T> erase(Iterator<T> pos);

        size_t size() const;

        Iterator<T> find(const T &value);

        Iterator<T> begin() const { return Iterator<T>(new iterator(root->min())); }

        Iterator<T> end() const { return Iterator<T>(new iterator(nullptr)); }

//        void print(Node *node, int blackHeight);

    private:
        void balance_insertion(Node *node);

        void balance_removal(Node *node);

        Node *get_uncle(Node *node);

        Node *get_grand_father(Node *node);

        void left_rotate(Node *node);

        void right_rotate(Node *node);

        void replace_node(Node *first_node, Node *second_node);
    };

}
*/