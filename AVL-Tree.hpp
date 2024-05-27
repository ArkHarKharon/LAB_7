#pragma once

#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;
using std::setw;


struct Node {
    int info;
    int height;
    Node* left;
    Node* right;
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return false;
        return node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int info) {
        Node* node = new Node;
        node->info = info;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    Node* rightRotate(Node* pivot_node) {
        Node* new_root = pivot_node->left;          // Новый корень поддерева после поворота
        Node* subtree_to_move = new_root->right;    // Поддерево, которое перемещается в результате поворота

        // Поворот
        new_root->right = pivot_node;
        pivot_node->left = subtree_to_move;

        // Обновляем высоты узлов
        pivot_node->height = max(height(pivot_node->left), height(pivot_node->right)) + 1;
        new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

        return new_root;
    }

    Node* leftRotate(Node* new_root) {
        Node* pivot_node = new_root->right;         // Узел, вокруг которого происходит поворот
        Node* subtree_to_move = pivot_node->left;   // Поддерево, которое перемещается в результате поворота

        // Поворот
        pivot_node->left = new_root;
        new_root->right = subtree_to_move;

        // Обновляем высоты узлов
        new_root->height = max(height(new_root->left), height(new_root->right)) + 1;
        pivot_node->height = max(height(pivot_node->left), height(pivot_node->right)) + 1;

        return pivot_node;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* insert(Node* node, int info) {
        if (node == nullptr)
            return newNode(info);

        if (info < node->info)
            node->left = insert(node->left, info);
        else if (info > node->info)
            node->right = insert(node->right, info);
        else
            return node;

        // Обновляем высоту текущего узла
        node->height = 1 + max(height(node->left), height(node->right));

        // Получаем коэффициент балансировки текущего узла
        int balance = getBalance(node);

        // Перебалансировка дерева, если необходимо
        // RR - правый
        if (balance > 1 && info < node->left->info)
            return rightRotate(node);

        // LL - левый
        if (balance < -1 && info > node->right->info)
            return leftRotate(node);

        // LR - лево-правый
        if (balance > 1 && info > node->left->info) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL - право-левый
        if (balance < -1 && info < node->right->info) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }


public:
    AVLTree() : root(nullptr) {}

    void insert(int info) {
        root = insert(root, info);
    }

    void insert() {
        // Вариант #9 - Данные: 6 3 0 2 1 5 4 

        insert(6);
        showSymmetricalOrder();

        insert(3);
        showSymmetricalOrder();

        insert(0);
        showSymmetricalOrder();

        insert(2);
        showSymmetricalOrder();

        insert(1);
        showSymmetricalOrder();

        insert(5);
        showSymmetricalOrder();

        insert(4);
        cout << "\n\t\tCбалансированное дерево: \n\n" << endl;
        showSymmetricalOrder();
    }

    void showDirectOrder(Node* node, int indent) {
        if (node != nullptr) {
            cout << "\t\t\t\t" << setw(indent) << node->info << " (" << getBalance(node) << ")" << endl;
            showDirectOrder(node->left, indent + 6);
            showDirectOrder(node->right, indent + 6);
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    void showDirectOrder(int indent = 5) {
        if (root != nullptr) {
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << " (" << getBalance(root) << ")" << endl;
            showDirectOrder(root->left, indent + 12);
            showDirectOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
    }

    void showSymmetricalOrder(Node* node, int indent) {
        if (node != nullptr) {
            showSymmetricalOrder(node->left, indent + 6);
            cout << "\t\t\t\t" << setw(indent) << node->info << " (" << getBalance(node) << ")" << endl;
            showSymmetricalOrder(node->right, indent + 6);
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    void showSymmetricalOrder(int indent = 5) {
        if (root != nullptr) {
            showSymmetricalOrder(root->left, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << " (" << getBalance(root) << ")" << endl;
            showSymmetricalOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
        cout << "\n--------------------------------------------------------------------------------------------------------------\n\n";
    }

    void showReverseOrder(Node* node, int indent) {
        if (node != nullptr) {
            showReverseOrder(node->left, indent + 6);
            showReverseOrder(node->right, indent + 6);
            cout << "\t\t\t\t" << setw(indent) << node->info << " (" << getBalance(node) << ")" << endl;
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    void showReverseOrder(int indent = 5) {
        if (root != nullptr) {
            showReverseOrder(root->left, indent + 12);
            showReverseOrder(root->right, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << " (" << getBalance(root) << ")" << endl;
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
    }
};