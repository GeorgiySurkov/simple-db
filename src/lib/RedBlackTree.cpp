/*
#include "RedBlackTree.h"

namespace SimpleDB {

    template<typename T>
    Iterator<T> RedBlackTree<T>::insert(const T &value) {
        if (!root) {
            root = new Node(false, value);
            root->left = new Node(root);
            root->right = new Node(root);
            return Iterator<T>(new iterator(root));
        }
        Node *node = root;
        auto *new_node = new Node(true, value);
        new_node->left = new Node(new_node);
        new_node->right = new Node(new_node);
        while (node->left != nullptr && node->right != nullptr) {
            if (value < node->value)
                node = node->left;
            else
                node = node->right;
        }
        new_node->parent = node->parent;
        if (node == node->parent->right)
            node->parent->right = new_node;
        else
            node->parent->left = new_node;
        balance_insertion(new_node);
        return Iterator<T>(new iterator(new_node));
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
            if (node->is_father_left_child()) {
                if (uncle->is_red) {
                    node->parent->is_red = false;
                    uncle->is_red = false;
                    grandFather->is_red = true;
                    node = grandFather;
                } else {
                    if (node == node->parent->right) {
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
                    if (node == node->parent->left) {
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
        if (node->is_father_left_child())
            return node->parent->parent->right;
        return node->parent->parent->left;
    }

    template<typename T>
    typename RedBlackTree<T>::Node *RedBlackTree<T>::get_grand_father(Node *node) {
        return node->parent->parent;
    }

    template<typename T>
    void RedBlackTree<T>::left_rotate(Node *node) {
        Node *pivot = node->right;

        pivot->parent = node->parent;

        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = pivot;
            else
                node->parent->right = pivot;
        } else {
            root = pivot;
        }

        if (pivot->left)
            pivot->left->parent = node;

        node->parent = pivot;
        node->right = pivot->left;
        pivot->left = node;
    }

    template<typename T>
    void RedBlackTree<T>::right_rotate(Node *node) {
        Node *pivot = node->left;

        pivot->parent = node->parent;

        if (node->parent) {
            if (node == node->parent->left)
                node->parent->left = pivot;
            else
                node->parent->right = pivot;
        } else {
            root = pivot;
        }

        if (pivot->right)
            pivot->right->parent = node;

        node->parent = pivot;
        node->left = pivot->right;
        pivot->right = node;
    }

    template<typename T>
    size_t RedBlackTree<T>::erase(const T &value) {
        Node *node = root;
        Node *balanceNode;
        while (node->value != value) {
            if (node->value < value)
                node = node->right;
            else
                node = node->left;
        }

        bool nodeOriginalIsRed = node->is_red;

        if (!node->right->right && !node->left->left) {
            if (node == root) {
                root = nullptr;
                return;
            } else {
                if (node == node->parent->left)
                    node->parent->left = new Node(node->parent);
                else
                    node->parent->right = new Node(node->parent);
                return;
            }
        }

        if (node->right->right && !node->left->left) {
            balanceNode = node->right;
            replace_node(node, node->right);
        } else if (!node->right->right && node->left->left) {
            balanceNode = node->left;
            replace_node(node, node->left);
        } else {
            Node *nextNode = node->right;
            while (nextNode->left->left)
                nextNode = nextNode->left;
            balanceNode = nextNode->right;
            nodeOriginalIsRed = nextNode->is_red;
            if (nextNode->parent == node) {
                balanceNode->parent = nextNode;
            } else {
                replace_node(nextNode, nextNode->right);
                nextNode->right = node->right;
                nextNode->right->parent = nextNode;
            }
            replace_node(node, nextNode);
            nextNode->left = node->left;
            nextNode->left->parent = nextNode;
            nextNode->is_red = node->is_red;
        }
        if (!nodeOriginalIsRed) {
            balance_removal(balanceNode);
        }
    }

    template<typename T>
    void RedBlackTree<T>::balance_removal(Node *node) {
        while (node->is_red == false && node != root) {
            if (node == node->parent->left) {
                Node *brother = node->parent->right;
                if (brother->is_red) {
                    brother->is_red = false;
                    node->parent->is_red = true;
                    left_rotate(node->parent);
                    brother = node->parent->right;
                }
                if (brother->left->is_red == false && brother->right->is_red == false) {
                    brother->is_red = true;
                    node = node->parent;
                } else {
                    if (brother->right->is_red == false) {
                        brother->left->is_red = false;
                        brother->is_red = true;
                        right_rotate(brother);
                        brother = node->parent->right;
                    }
                    brother->is_red = node->parent->is_red;
                    node->parent->is_red = false;
                    brother->right->is_red = false;
                    left_rotate(node->parent);
                    node = root;
                }
            } else {
                Node *brother = node->parent->left;
                if (brother->is_red) {
                    brother->is_red = false;
                    node->parent->is_red = true;
                    right_rotate(node->parent);
                    brother = node->parent->left;
                }
                if (brother->left->is_red == false && brother->right->is_red == false) {
                    brother->is_red = true;
                    node = node->parent;
                } else {
                    if (brother->left->is_red == false) {
                        brother->right->is_red = false;
                        brother->is_red = true;
                        left_rotate(brother);
                        brother = node->parent->left;
                    }
                    brother->is_red = node->parent->is_red;
                    node->parent->is_red = false;
                    brother->left->is_red = false;
                    right_rotate(node->parent);
                    node = root;
                }
            }
        }
        root->is_red = false;
    }

    template<typename T>
    Iterator<T> RedBlackTree<T>::find(const T &value) {
        // TODO: implement find
        return Iterator<T>();
    }

    template<typename T>
    void RedBlackTree<T>::replace_node(Node *first_node, Node *second_node) {
        if (first_node->parent == nullptr) {
            root = second_node;
        } else if (first_node == first_node->parent->left) {
            first_node->parent->left = second_node;
        } else {
            first_node->parent->right = second_node;
        }
        second_node->parent = first_node->parent;
    }

//    template<typename T>
//    void RedBlackTree<T>::print(Node *node, int blackHeight) {
//        if (!node->left && !node->right)
//            return;
//        int blackHeightAddition = 0;
//        if (node->is_red == false)
//            blackHeightAddition = 1;
//        print(node->left, blackHeight + blackHeightAddition);
//        std::cout << node->value << " (" << blackHeight + blackHeightAddition << ')' << std::endl;
//        print(node->right, blackHeight + blackHeightAddition);
//    }
}
 */