#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string value) {
        name = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

    void show(Node* node) {
        if (node == nullptr)
            return;

        cout << node->name << " -> Left: ";
        if (node->left == nullptr)
            cout << "NULL";
        else
            cout << node->left->name;

        cout << ", Right: ";
        if (node->right == nullptr)
            cout << "NULL";
        else
            cout << node->right->name;
        cout << endl;

        show(node->left);
        show(node->right);
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->name << " | ";
        inorder(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        destroy(root);
    }

    void createTree() {
        root = new Node("Dr. Ahmed");
        root->left = new Node("Prof. Sara");
        root->right = new Node("Dr. Bilal");

        root->left->left = new Node("Mr. Usman");
        root->left->right = new Node("Ms. Hina");
        root->right->left = new Node("Mr. Kamran");
        root->right->right = new Node("Ms. Ayesha");

        root->left->left->left = new Node("Mr. Zain");
    }

    void display() {
        show(root);
    }

    void displayInorder() {
        cout << "In-order of names: ";
        inorder(root);
        cout << endl;
    }
};

class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int value, bool& added) {
        if (node == nullptr) {
            added = true;
            return new BSTNode(value);
        }

        if (value < node->data)
            node->left = insert(node->left, value, added);
        else if (value > node->data)
            node->right = insert(node->right, value, added);

        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int value, bool& removed) {
        if (node == nullptr)
            return nullptr;

        if (value < node->data) {
            node->left = deleteNode(node->left, value, removed);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value, removed);
        }
        else {
            removed = true;

            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->data = temp->data;

            bool ignore = false;
            node->right = deleteNode(node->right, temp->data, ignore);
        }

        return node;
    }

    void inorder(BSTNode* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void destroy(BSTNode* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        destroy(root);
    }

    bool insertValue(int value) {
        bool added = false;
        root = insert(root, value, added);
        return added;
    }

    bool searchValue(int value, int& visits) {
        visits = 0;
        BSTNode* current = root;

        while (current != nullptr) {
            visits++;

            if (value == current->data)
                return true;
            else if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        return false;
    }

    bool deleteValue(int value) {
        bool removed = false;
        root = deleteNode(root, value, removed);
        return removed;
    }

    void display() {
        cout << "BST values: ";
        inorder(root);
        cout << endl;
    }
};

void fillOriginal(BST& tree) {
    tree.insertValue(48);
    tree.insertValue(28);
    tree.insertValue(68);
    tree.insertValue(18);
    tree.insertValue(38);
    tree.insertValue(58);
    tree.insertValue(78);
}

void testSearch(BST& tree, int value) {
    int visits = 0;
    bool found = tree.searchValue(value, visits);

    cout << "Search " << value << ": ";
    if (found)
        cout << "Found";
    else
        cout << "Not found";
    cout << " | Node visits: " << visits << endl;
}

void testDelete(BST& tree, int value) {
    cout << "Deleting " << value << ": ";
    if (tree.deleteValue(value))
        cout << "deleted" << endl;
    else
        cout << "ID not found, tree unchanged" << endl;

    tree.display();
}

int main() {
    cout << "===== General Binary Tree =====" << endl;
    BinaryTree staff;
    staff.createTree();
    staff.display();
    staff.displayInorder();

    cout << endl << "===== BST of Staff IDs =====" << endl;
    BST tree;
    fillOriginal(tree);
    cout << "Initial IDs" << endl;
    tree.display();

    cout << endl << "Enter three additional staff IDs:" << endl;
    for (int i = 1; i <= 3; i++) {
        int id;
        cout << "ID " << i << ": ";
        cin >> id;

        if (tree.insertValue(id))
            cout << id << " inserted" << endl;
        else
            cout << id << " already exists, rejected" << endl;
    }
    tree.display();

    cout << endl << "===== Search Tests =====" << endl;
    testSearch(tree, 38);
    testSearch(tree, 99);
    testSearch(tree, 5);

    int key;
    cout << "Enter an ID to search: ";
    cin >> key;
    testSearch(tree, key);

    cout << endl << "===== Deletion Tests =====" << endl;

    BST leafTree;
    fillOriginal(leafTree);
    cout << "Case 1: leaf node" << endl;
    testDelete(leafTree, 18);

    BST oneChildTree;
    fillOriginal(oneChildTree);
    oneChildTree.insertValue(15);
    cout << endl << "Case 2: node with one child (15 added under 18)" << endl;
    testDelete(oneChildTree, 18);

    BST twoChildTree;
    fillOriginal(twoChildTree);
    cout << endl << "Case 3: node with two children" << endl;
    testDelete(twoChildTree, 28);

    BST userTree;
    fillOriginal(userTree);
    int value;
    cout << endl << "Enter a staff ID to delete: ";
    cin >> value;
    testDelete(userTree, value);

    cout << endl << "===== Explanation =====" << endl;
    cout << "In a general binary tree, nodes are linked wherever the programmer" << endl;
    cout << "chooses, so no rule connects a node's value to its position. The" << endl;
    cout << "in-order result therefore follows the shape of the tree and can be" << endl;
    cout << "in any order." << endl;
    cout << "In a BST, every value in the left subtree is smaller than the node" << endl;
    cout << "and every value in the right subtree is larger. In-order traversal" << endl;
    cout << "visits left, root, then right, so smaller values are always shown" << endl;
    cout << "before larger ones and the output is in ascending order." << endl;

    return 0;
}
