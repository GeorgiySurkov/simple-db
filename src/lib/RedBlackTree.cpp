#include "RedBlackTree.h"

#include <iostream>

namespace SimpleDB {

    template<typename T>
    void RedBlackTree<T>::insert(T value) {
        if (!root) {
            root = new Node(false, value);
            root->left_child = new Node(root);
            root->right_child = new Node(root);
            return;
        }
        Node *node = root;
        auto *newNode = new Node(true, value);
        newNode->left_child = new Node(newNode);
        newNode->right_child = new Node(newNode);
        while (node->left_child != nullptr && node->right_child != nullptr) {
            if (node->value > value)
                node = node->left_child;
            else
                node = node->right_child;
        }
        newNode->parent = node->parent;
        if (node == node->parent->right_child)
            node->parent->right_child = newNode;
        else
            node->parent->left_child = newNode;
        balance_insertion(newNode);
    }

    template<typename T>
    void RedBlackTree<T>::balance_insertion(Node *node) {
        if (node == this->root) {
            node->is_red = false;
            return;
        }

        while (node->parent && node->parent->is_red) {
            Node *uncle = get_uncle(node);
            Node *grandFather = get_grand_father(node);
            if (is_father_left_child(node)) {
                if (uncle->is_red) {
                    node->parent->is_red = false;
                    uncle->is_red = false;
                    grandFather->is_red = true;
                    node = grandFather;
                } else {
                    if (node == node->parent->right_child) {
                        node = node->parent;
                        left_rotate(node->parent);
                    }
                    node->parent->is_red = false;
                    grandFather->is_red = true;
                    right_rotate(grandFather);
                }
            } else {
                if (uncle->is_red == true) {
                    node->parent->is_red = false;
                    uncle->is_red = false;
                    grandFather->is_red = true;
                    node = grandFather;
                } else {
                    if (node == node->parent->left_child) {
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->is_red = false;
                    grandFather->is_red = true;
                    left_rotate(grandFather);
                }
            }
        }
        root->is_red = false;
    }

    template<typename T>
    typename RedBlackTree<T>::Node *RedBlackTree<T>::get_uncle(Node *node) {
        if (is_father_left_child(node))
            return node->parent->parent->right_child;
        return node->parent->parent->left_child;
    }

    template<typename T>
    bool RedBlackTree<T>::is_father_left_child(Node *node) {
        return node->parent == node->parent->parent->left_child;
    }

    template<typename T>
    typename RedBlackTree<T>::Node *RedBlackTree<T>::get_grand_father(Node *node) {
        return node->parent->parent;
    }

    template<typename T>
    void RedBlackTree<T>::left_rotate(Node *node) {
        Node *pivot = node->right_child;

        pivot->parent = node->parent;

        if (node->parent) {
            if (node == node->parent->left_child)
                node->parent->left_child = pivot;
            else
                node->parent->right_child = pivot;
        } else {
            root = pivot;
        }

        if (pivot->left_child)
            pivot->left_child->parent = node;

        node->parent = pivot;
        node->right_child = pivot->left_child;
        pivot->left_child = node;
    }

    template<typename T>
    void RedBlackTree<T>::right_rotate(Node *node) {
        Node *pivot = node->left_child;

        pivot->parent = node->parent;

        if (node->parent) {
            if (node == node->parent->left_child)
                node->parent->left_child = pivot;
            else
                node->parent->right_child = pivot;
        } else {
            root = pivot;
        }

        if (pivot->right_child)
            pivot->right_child->parent = node;

        node->parent = pivot;
        node->left_child = pivot->right_child;
        pivot->right_child = node;
    }

    template<typename T>
    void RedBlackTree<T>::remove(T value) {
        Node *node = root;
        Node *balanceNode;
        while (node->value != value) {
            if (node->value < value)
                node = node->right_child;
            else
                node = node->left_child;
        }

        bool nodeOriginalIsRed = node->is_red;

        if (!node->right_child->right_child && !node->left_child->left_child) {
            if (node == root) {
                root = nullptr;
                return;
            } else {
                if (node == node->parent->left_child)
                    node->parent->left_child = new Node(node->parent);
                else
                    node->parent->right_child = new Node(node->parent);
                return;
            }
        }

        if (node->right_child->right_child && !node->left_child->left_child) {
            balanceNode = node->right_child;
            replace_node(node, node->right_child);
        } else if (!node->right_child->right_child && node->left_child->left_child) {
            balanceNode = node->left_child;
            replace_node(node, node->left_child);
        } else {
            Node *nextNode = node->right_child;
            while (nextNode->left_child->left_child)
                nextNode = nextNode->left_child;
            balanceNode = nextNode->right_child;
            nodeOriginalIsRed = nextNode->is_red;
            if (nextNode->parent == node) {
                balanceNode->parent = nextNode;
            } else {
                replace_node(nextNode, nextNode->right_child);
                nextNode->right_child = node->right_child;
                nextNode->right_child->parent = nextNode;
            }
            replace_node(node, nextNode);
            nextNode->left_child = node->left_child;
            nextNode->left_child->parent = nextNode;
            nextNode->is_red = node->is_red;
        }
        if (!nodeOriginalIsRed) {
            balance_removing(balanceNode);
        }
    }

    template<typename T>
    void RedBlackTree<T>::balance_removing(Node *node) {
        while (node->is_red == false && node != root) {
            if (node == node->parent->left_child) {
                Node *brother = node->parent->right_child;
                if (brother->is_red) {
                    brother->is_red = false;
                    node->parent->is_red = true;
                    left_rotate(node->parent);
                    brother = node->parent->right_child;
                }
                if (brother->left_child->is_red == false && brother->right_child->is_red == false) {
                    brother->is_red = true;
                    node = node->parent;
                } else {
                    if (brother->right_child->is_red == false) {
                        brother->left_child->is_red = false;
                        brother->is_red = true;
                        right_rotate(brother);
                        brother = node->parent->right_child;
                    }
                    brother->is_red = node->parent->is_red;
                    node->parent->is_red = false;
                    brother->right_child->is_red = false;
                    left_rotate(node->parent);
                    node = root;
                }
            } else {
                Node *brother = node->parent->left_child;
                if (brother->is_red) {
                    brother->is_red = false;
                    node->parent->is_red = true;
                    right_rotate(node->parent);
                    brother = node->parent->left_child;
                }
                if (brother->left_child->is_red == false && brother->right_child->is_red == false) {
                    brother->is_red = true;
                    node = node->parent;
                } else {
                    if (brother->left_child->is_red == false) {
                        brother->right_child->is_red = false;
                        brother->is_red = true;
                        left_rotate(brother);
                        brother = node->parent->left_child;
                    }
                    brother->is_red = node->parent->is_red;
                    node->parent->is_red = false;
                    brother->left_child->is_red = false;
                    right_rotate(node->parent);
                    node = root;
                }
            }
        }
        root->is_red = false;
    }

    template<typename T>
    void RedBlackTree<T>::replace_node(Node *first_node, Node *second_node) {
        if (first_node->parent == nullptr) {
            root = second_node;
        } else if (first_node == first_node->parent->left_child) {
            first_node->parent->left_child = second_node;
        } else {
            first_node->parent->right_child = second_node;
        }
        second_node->parent = first_node->parent;
    }

    template<typename T>
    void RedBlackTree<T>::print(Node *node, int blackHeight) {
        if (!node->left_child && !node->right_child)
            return;
        int blackHeightAddition = 0;
        if (node->is_red == false)
            blackHeightAddition = 1;
        print(node->left_child, blackHeight + blackHeightAddition);
        std::cout << node->value << " (" << blackHeight + blackHeightAddition << ')' << std::endl;
        print(node->right_child, blackHeight + blackHeightAddition);
    }
}