#include <iostream>
#include <limits>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int value, bool& added) {
        if (node == nullptr) {
            added = true;
            return new Node(value);
        }

        if (value < node->data)
            node->left = insert(node->left, value, added);
        else if (value > node->data)
            node->right = insert(node->right, value, added);

        return node;
    }

    bool search(Node* node, int value) {
        if (node == nullptr)
            return false;

        if (value == node->data)
            return true;
        else if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int value, bool& removed) {
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
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;

            bool ignore = false;
            node->right = deleteNode(node->right, temp->data, ignore);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int countNodes(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        if (leftHeight > rightHeight)
            return 1 + leftHeight;
        else
            return 1 + rightHeight;
    }

    void destroy(Node* node) {
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

    void insertValue(int value) {
        bool added = false;
        root = insert(root, value, added);

        if (added)
            cout << value << " inserted successfully." << endl;
        else
            cout << value << " already exists. Duplicate rejected." << endl;
    }

    void searchValue(int value) {
        if (root == nullptr) {
            cout << "Tree is empty. Nothing to search." << endl;
            return;
        }

        if (search(root, value))
            cout << value << " found in the tree." << endl;
        else
            cout << value << " not found in the tree." << endl;
    }

    void deleteValue(int value) {
        if (root == nullptr) {
            cout << "Tree is empty. Nothing to delete." << endl;
            return;
        }

        bool removed = false;
        root = deleteNode(root, value, removed);

        if (removed) {
            cout << value << " deleted successfully." << endl;
            cout << "Updated IDs: ";
            inorder(root);
            cout << endl;
        }
        else {
            cout << value << " does not exist. Nothing deleted." << endl;
        }
    }

    void displayInorder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "In-order: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "Pre-order: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "Post-order: ";
        postorder(root);
        cout << endl;
    }

    int totalNodes() {
        return countNodes(root);
    }

    int height() {
        return getHeight(root);
    }
};

void fillInitial(BST& tree) {
    int ids[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};

    for (int i = 0; i < 9; i++)
        tree.insertValue(ids[i]);
}

int readNumber(string message) {
    int number;
    cout << message;

    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number: ";
    }

    return number;
}

void predictionTest() {
    cout << "===== Prediction Test =====" << endl;
    cout << "Sequence: insert 60, insert 30, delete 25, delete 55, delete 75" << endl;
    cout << "Predicted in-order: 30 35 40 45 50 60 65 85" << endl;
    cout << "Predicted height: 4" << endl << endl;

    BST test;
    fillInitial(test);
    cout << endl;

    test.insertValue(60);
    test.insertValue(30);
    test.deleteValue(25);
    test.deleteValue(55);
    test.deleteValue(75);

    cout << endl << "Actual results" << endl;
    test.displayInorder();
    cout << "Height: " << test.height() << endl;

    cout << endl << "Repeated deletion of the same ID (60):" << endl;
    test.deleteValue(60);
    test.deleteValue(60);
    cout << "The first call removes the node. The second call finds no node" << endl;
    cout << "with that ID, so it prints a message and the tree stays unchanged." << endl;

    cout << endl << "Deleting a node with two children:" << endl;
    cout << "The node's value is replaced by its in-order successor, which is" << endl;
    cout << "the smallest value in its right subtree. This value is larger than" << endl;
    cout << "everything in the left subtree and smaller than everything else in" << endl;
    cout << "the right subtree, so the BST property still holds. The original" << endl;
    cout << "successor node is then deleted, and it has at most one child." << endl;
    cout << endl;
}

int main() {
    predictionTest();

    cout << "===== Hospital Inventory System =====" << endl;
    BST tree;
    fillInitial(tree);

    int choice;

    do {
        cout << endl << "1. Insert an ID" << endl;
        cout << "2. Search for an ID" << endl;
        cout << "3. Delete an ID" << endl;
        cout << "4. Display in-order traversal" << endl;
        cout << "5. Display pre-order traversal" << endl;
        cout << "6. Display post-order traversal" << endl;
        cout << "7. Count total nodes" << endl;
        cout << "8. Calculate height" << endl;
        cout << "9. Exit" << endl;

        choice = readNumber("Enter your choice: ");

        switch (choice) {
            case 1:
                tree.insertValue(readNumber("Enter ID to insert: "));
                break;
            case 2:
                tree.searchValue(readNumber("Enter ID to search: "));
                break;
            case 3:
                tree.deleteValue(readNumber("Enter ID to delete: "));
                break;
            case 4:
                tree.displayInorder();
                break;
            case 5:
                tree.displayPreorder();
                break;
            case 6:
                tree.displayPostorder();
                break;
            case 7:
                cout << "Total nodes: " << tree.totalNodes() << endl;
                break;
            case 8:
                cout << "Height of BST: " << tree.height() << endl;
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Enter a number from 1 to 9." << endl;
        }
    } while (choice != 9);

    return 0;
}
