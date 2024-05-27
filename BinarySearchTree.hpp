#pragma once

#include <iostream> 
#include <iomanip> // ��������� ����������� ���������� ��� ����������� � �������

using std::cout;
using std::endl;
using std::setw;

struct BinaryNode {
    int info;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;
};

/*
����� ������ ������ ���� (� ������ �������): A, B, C - ���������� �����.
����� ������ � ������������ ������� (����� �������): B, A, C - ��������� �����.
����� ������ � �������� ������� (����� �����): B, C, A - ����������� �����.
*/

/*
void treeprint(tnode* tree) {
  if (tree != NULL) { //���� �� ���������� ������ ����
    cout << tree->field; //���������� ������ ������
    treeprint(tree->left); //����������� ������� ��� ������ ���������
    treeprint(tree->right); //����������� ������� ��� ������� ���������
  }
}

void treeprint(tnode* tree) {
  if (tree != NULL) { //���� �� ���������� ������ ����
    treeprint(tree->left); //����������� ������� ��� ������ ���������
    cout << tree->field; //���������� ������ ������
    treeprint(tree->right); //����������� ������� ��� ������� ���������
  }
}

void treeprint(tnode* tree) {
  if (tree != NULL) { //���� �� ���������� ������ ����
    treeprint(tree->left); //����������� ������� ��� ������ ���������
    treeprint(tree->right); //����������� ������� ��� ������� ���������
    cout << tree->field; //���������� ������ ������
  }
}

*/

class BinaryTree {

    BinaryNode* root = nullptr; // ��������� �� �������� ����
    bool is_finded = true;

public:

    BinaryTree()
    {

    }

    BinaryTree(int root) {
        this->root = new BinaryNode; // �������� ������ ��������� ����
        this->root->info = root; // ���������� �������� ��������� ����
    }

    ~BinaryTree() {
        dell(root);
        cout << "\n\t\t\t\t������ ������� :(" << endl;
    }

    // ����� ��� ������ ���������� ������ �������� � ������
    void add(int info) {
        if (root == nullptr) {
            root = new BinaryNode; // �������� ������ ��������� ����
            root->info = info; // ���������� �������� ��������� ����
        }
        else {
            root = add(info, root); // ���������� ����
        }
    }

    // ����� ��� ������������ ���������� �������� � ��������������� ����� � ������
    BinaryNode* add(int info, BinaryNode* tree) {
        // ����������� ���������� ���� � ������
        if (tree == nullptr) {
            tree = new BinaryNode;
            tree->info = info;
        }
        else  if (info < tree->info) tree->left = add(info, tree->left);
        else  if (info > tree->info) tree->right = add(info, tree->right);
        else cout << "\t\t\t\t�����������, " << info << " ��� ����." << endl;

        return tree;
    }

    // �����  ��� ������������ �������� ���� ����� ������, ������� � ��������� ���� tree.
    void dell(BinaryNode* tree) {
        // ����������� �������� ����� �� ������
        if (tree != nullptr) {
            dell(tree->left);
            dell(tree->right);
            delete tree; // �������� �������� ����
            tree = nullptr;
        }
    }

    // ����� ��� �������� ���� � ������������ ��������� info �� ������
    // ��������� ���������� � ���������� ���� � ��� ��������� � ���������� ���� (����� ��� ������).
    void dell(int info, BinaryNode* tree, BinaryNode* tree_pred, char leftOrRight) {
        // �������� ���� �� ��������
        if (tree == nullptr) {
            cout << "\t\t\t\t�������� ����������, ������� ����������� :(" << endl;
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

    // ����� ��� �������� ���� � ������������ ��������� info �� ������
    // �������� ����� � ����� ������
    void dell(int info) {
        // �������� ���� �� ��������
        if (root == nullptr) {
            cout << "\t\t\t\t�������� ����������, 0 ����� :(" << endl;
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

    // ����� ��� ������ ������ � ������
    void search(int info) {
        if (root == nullptr) {
            is_finded = false;
        }
        else if (info == root->info) {
            is_finded = true;
        }
        // ������������ ����� � ��������������� ���������
        else if (info < root->info) return search(info, root->left);
        else if (info > root->info) return search(info, root->right);
        else {
            cout << "\t\t\t\tError." << endl;
            is_finded = false;
        }

        if (is_finded) {
            cout << "���� ������.\n";
        }
        else {
            cout << "�����. ������ �� �������.\n";
        }
    }

    // ����� ��� ������������ ������ � ���������, ������� � ��������� ����
    // ��������� ����������� ����� � ���������, ������� � ����� ����
    void search(int info, BinaryNode* tree) {
        if (tree == nullptr) {
            is_finded = false;
        }
        else if (info == tree->info) {
            is_finded = true;
        }
        // ���������� �������� ��� ���� ��� ������ � ����� ��� ������ ���������
        else if (info < tree->info) return search(info, tree->left);
        else if (info > tree->info) return search(info, tree->right);
        else {
            cout << "\t\t\t\tError." << endl;
            is_finded = false;
        }

        if (is_finded) {
            cout << "���� ������.\n";
        }
        else {
            cout << "�����. ������ �� �������.\n";
        }
    }

    // ������ �����
    void showDirectOrder(BinaryNode* tree, int indent) {

        if (tree != nullptr) {
            cout << "\t\t\t\t" << setw(indent) << tree->info << /*" " << tree << " " << tree->left << " " << tree->right <<*/ endl;
            // ���������� �������� ���� ��� ������ � ������� ����������� �������� ����
            showDirectOrder(tree->left, indent + 6);
            showDirectOrder(tree->right, indent + 6);
        }
        else {
            cout << "\t\t\t\t" << setw(indent + 7) << "- nullptr" << endl;
        }
    }

    // ������ ����� � �����
    void showDirectOrder(int indent = 5) {

        if (root != nullptr) {
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
            showDirectOrder(root->left, indent + 12);
            showDirectOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\t������ ������ :(" << endl;
        }
    }

    // ������������ �����
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

    // ������������ ����� � �����
    void showSymmetricalOrder(int indent = 5) {

        if (root != nullptr) {
            showSymmetricalOrder(root->left, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
            showSymmetricalOrder(root->right, indent + 12);
        }
        else {
            cout << "\t\t\t\t������ ������ :(" << endl;
        }
    }

    // �������� �����
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

    // �������� ����� � �����
    void showReverseOrder(int indent = 5) {

        if (root != nullptr) {
            showReverseOrder(root->left, indent + 12);
            showReverseOrder(root->right, indent + 12);
            cout << "\t\t\t\t" << setw(indent + 5) << root->info << /*" " << root << " " << root->left << " " << root->right <<*/ endl;
        }
        else {
            cout << "\t\t\t\t������ ������ :(" << endl;
        }
    }

    void erase(int key) {
        BinaryNode* curr = root;
        BinaryNode* parent = nullptr;

        // ����� ���� ��� ��������
        while (curr && curr->info != key) {
            parent = curr;
            if (key < curr->info)
                curr = curr->left;
            else
                curr = curr->right;
        }

        // ���� ���� �� ������, ������������
        if (!curr)
            return;

        // �������� ���� � ����� ��� ��� ��������
        if (curr->left == nullptr || curr->right == nullptr) {
            BinaryNode* child = (curr->left != nullptr) ? curr->left : curr->right;

            if (parent == nullptr) {
                root = child; // ��������� ������, ���� ��������� ���� ��� ������
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

        // �������� ���� � ����� ���������
        BinaryNode* replace = curr->right;
        while (replace->left)
            replace = replace->left;
        int replace_value = replace->info;
        erase(replace_value); // ���������� ������� ���������� ������� �� ������� ���������
        curr->info = replace_value;
    }

};