#pragma once

namespace SimpleDB {


    template<typename T>
    class RedBlackTree {
    public:

        class Node {
        public:
            Node *parent = nullptr;
            Node *left_child = nullptr;
            Node *right_child = nullptr;
            bool is_red = false;
            T value;

            Node(bool isRed, T value) : is_red(isRed), value(value) {};

            explicit Node(Node *parent) : parent(parent) {};

            Node() = default;
        };

        Node *root = nullptr;

        RedBlackTree() = default;

        void insert(T value);

        void remove(T value);

        void print(Node *node, int blackHeight);

    private:
        void balance_insertion(Node *node);

        void balance_removing(Node *node);

        Node *get_uncle(Node *node);

        Node *get_grand_father(Node *node);

        bool is_father_left_child(Node *node);

        void left_rotate(Node *node);

        void right_rotate(Node *node);

        void replace_node(Node *first_node, Node *second_node);
    };

}
