#pragma once

#include <iostream> 
#include <iomanip> // Включение стандартной библиотеки для манипуляций с выводом

using std::cout;
using std::endl;
using std::setw;

struct BinaryNode {
    int info;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
};

/*
Обход дерева сверху вниз (в прямом порядке): A, B, C - префиксная форма.
Обход дерева в симметричном порядке (слева направо): B, A, C - инфиксная форма.
Обход дерева в обратном порядке (снизу вверх): B, C, A - постфиксная форма.
*/

/*
void treeprint(tnode* tree) {
  if (tree != NULL) { //Пока не встретится пустой узел
    cout << tree->field; //Отображаем корень дерева
    treeprint(tree->left); //Рекурсивная функция для левого поддерева
    treeprint(tree->right); //Рекурсивная функция для правого поддерева
  }
}

void treeprint(tnode* tree) {
  if (tree != NULL) { //Пока не встретится пустой узел
    treeprint(tree->left); //Рекурсивная функция для левого поддерева
    cout << tree->field; //Отображаем корень дерева
    treeprint(tree->right); //Рекурсивная функция для правого поддерева
  }
}

void treeprint(tnode* tree) {
  if (tree != NULL) { //Пока не встретится пустой узел
    treeprint(tree->left); //Рекурсивная функция для левого поддерева
    treeprint(tree->right); //Рекурсивная функция для правого поддерева
    cout << tree->field; //Отображаем корень дерева
  }
}

*/

class BinaryTree {

    BinaryNode* root = nullptr; // Указатель на корневой узел
    bool is_finded = true;

public:

    BinaryTree()
    {

    }

    BinaryTree(int root) {
        this->root = new BinaryNode; // Создание нового корневого узла
        this->root->info = root; // Присвоение значению корневого узла
    }

    ~BinaryTree() {
        dell(root);
        cout << "\n\t\t\t\tДерево удалено :(" << endl;
    }

    // Метод для начала добавления нового элемента в дерево
    void add(int info) {
        if (root == nullptr) {
            root = new BinaryNode; // Создание нового корневого узла
            root->info = info; // Присвоение значению корневого узла
        }
        else {
            root = add(info, root); // Добавление узла
        }
    }

    // Метод для рекурсивного добавления элемента в соответствующее место в дереве
    BinaryNode* add(int info, BinaryNode* tree) {
        // Рекурсивное добавление узла в дерево
        if (tree == nullptr) {
            tree = new BinaryNode;
            tree->info = info;
        }
        else  if (info < tree->info) tree->left = add(info, tree->left);
        else  if (info > tree->info) tree->right = add(info, tree->right);
        else cout << "\t\t\t\tПовторилось, " << info << " уже есть." << endl;

        return tree;
    }

    // Метод  для рекурсивного удаления всех узлов дерева, начиная с заданного узла tree.
    void dell(BinaryNode* tree) {
        // Рекурсивное удаление узлов из дерева
        if (tree != nullptr) {
            dell(tree->left);
            dell(tree->right);
            delete tree; // Удаление текущего узла
            tree = nullptr;
        }
    }

    // Метод для удаления узла с определенным значением info из дерева
    // учитывает информацию о предыдущем узле и его отношении к удаляемому узлу (слева или справа).
    void dell(int info, BinaryNode* tree, BinaryNode* tree_pred, char leftOrRight) {
        // Удаление узла по значению
        if (tree == nullptr) {
            cout << "\t\t\t\tУдаление невозможно, элемент отсутствует :(" << endl;
        }
        else {
            if (info == tree->info) {
                dell(tree->left);
                dell(tree->right);
                delete tree;

                switch (leftOrRight) {
                case 'l': tree_pred->left = nullptr; break;
                case 'r': tree_pred->right = nullptr; break;
                default: cout << "\t\t\t\tError."; break;
                }
            }
            else if (info < tree->info) dell(info, tree->left, tree, 'l');
            else if (info > tree->info) dell(info, tree->right, tree, 'r');
            else cout << "\t\t\t\tError." << endl;
        }
    }

    // Метод для удаления узла с определенным значением info из дерева
    // начинает поиск с корня дерева
    void dell(int info) {
        // Удаление узла по значению
        if (root == nullptr) {
            cout << "\t\t\t\tУдаление невозможно, 0 узлов :(" << endl;
        }
        else {
            if (info == root->info) {
                dell(root->left);
                dell(root->right);
                delete root;
                root = nullptr;
            }
            else if (info < root->info) dell(info, root->left, root, 'l');
            else if (info > root->info) dell(info, root->right, root, 'r');
            else cout << "\t\t\t\tError." << endl;
        }
    }

    // Метод для начала поиска в дереве
    void search(int info) {
        if (root == nullptr) {
            is_finded = false;
        }
        else if (info == root->info) {
            is_finded = true;
        }
        // Реркурсивный поиск в соответствующем поддереве
        else if (info < root->info) return search(info, root->left);
        else if (info > root->info) return search(info, root->right);
        else {
            cout << "\t\t\t\tError." << endl;
            is_finded = false;
        }

        if (is_finded) {
            cout << "Узел найден.\n";
        }
        else {
            cout << "Пусто. Ничего не найдено.\n";
        }
    }

    // Метод для рекурсивного поиска в поддереве, начиная с заданного узла
    // Выполняет рекурсивный поиск в поддереве, начиная с этого узла
    void search(int info, BinaryNode* tree) {
        if (tree == nullptr) {
            is_finded = false;
        }
        else if (info == tree->info) {
            is_finded = true;
        }
        // Рекурсивно вызывает сам себя для поиска в левом или правом поддереве
        else if (info < tree->info) return search(info, tree->left);
        else if (info > tree->info) return search(info, tree->right);
        else {
            cout << "\t\t\t\tError." << endl;
            is_finded = false;
        }

        if (is_finded) {
            cout << "Узел найден.\n";
        }
        else {
            cout << "Пусто. Ничего не найдено.\n";
        }
    }

    // Прямой обход
    void showDirectOrder(BinaryNode* tree, int indent) {

        if (tree != nullptr) {
            cout << "\t\t\t\t" << setw(indent) << tree->info << /*" " << tree << " " << tree->left << " " << tree->right <<*/ endl;
            // Рекурсивно вызывает себя для левого и правого поддеревьев текущего узла
            showDirectOrder(tree->left, indent + 6);
            showDirectOrder(tree->right, indent + 6);
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    // Прямой обход с корня
    void showDirectOrder(int indent = 5) {

        if (root != nullptr) {
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
            showDirectOrder(root->left, indent + 12);
            showDirectOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
    }

    // Симметричный обход
    void showSymmetricalOrder(BinaryNode* tree, int indent) {

        if (tree != nullptr) {
            showSymmetricalOrder(tree->left, indent + 6);
            cout << "\t\t\t\t" << setw(indent) << tree->info << /*" " << tree << " " << tree->left << " " << tree->right <<*/ endl;
            showSymmetricalOrder(tree->right, indent + 6);
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    // Симметричный обход с корня
    void showSymmetricalOrder(int indent = 5) {

        if (root != nullptr) {
            showSymmetricalOrder(root->left, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
            showSymmetricalOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
    }

    // Обратный обход
    void showReverseOrder(BinaryNode* tree, int indent) {

        if (tree != nullptr) {
            showReverseOrder(tree->left, indent + 6);
            showReverseOrder(tree->right, indent + 6);
            cout << "\t\t\t\t" << setw(indent) << tree->info << /*" " << tree << " " << tree->left << " " << tree->right <<*/ endl;
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    // Обратный обход с корня
    void showReverseOrder(int indent = 5) {

        if (root != nullptr) {
            showReverseOrder(root->left, indent + 12);
            showReverseOrder(root->right, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
        }
        else {
            cout << "\t\t\t\tДерево пустое :(" << endl;
        }
    }

    void erase(int key) {
        BinaryNode* curr = root;
        BinaryNode* parent = nullptr;

        // Поиск узла для удаления
        while (curr && curr->info != key) {
            parent = curr;
            if (key < curr->info)
                curr = curr->left;
            else
                curr = curr->right;
        }

        // Если узел не найден, возвращаемся
        if (!curr)
            return;

        // Удаление узла с одним или без потомков
        if (curr->left == nullptr || curr->right == nullptr) {
            BinaryNode* child = (curr->left != nullptr) ? curr->left : curr->right;

            if (parent == nullptr) {
                root = child; // Обновляем корень, если удаляемый узел был корнем
            }
            else {
                if (parent->left == curr)
                    parent->left = child;
                else
                    parent->right = child;
            }
            delete curr;
            return;
        }

        // Удаление узла с двумя потомками
        BinaryNode* replace = curr->right;
        while (replace->left)
            replace = replace->left;
        int replace_value = replace->info;
        erase(replace_value); // Рекурсивно удаляем наименьший элемент из правого поддерева
        curr->info = replace_value;
    }

};