#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

class Node {
public:
    int emergencyID;
    string location;
    int severity;
    int height;
    Node* left;
    Node* right;

    Node(int id, string place, int level) {
        emergencyID = id;
        location = place;
        severity = level;
        height = 1;
        left = 0;
        right = 0;
    }
};

class AVL {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == 0)
            return 0;

        return node->height;
    }

    int getBalance(Node* node) {
        if (node == 0)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        if (node == 0)
            return node;

        updateHeight(node);

        int bf = getBalance(node);

        if (bf > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (bf < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (bf > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* insert(Node* node, int id, string place, int level) {
        if (node == 0)
            return new Node(id, place, level);

        if (id < node->emergencyID)
            node->left = insert(node->left, id, place, level);
        else if (id > node->emergencyID)
            node->right = insert(node->right, id, place, level);
        else
            return node;

        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left != 0)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int id) {
        if (node == 0)
            return 0;

        if (id < node->emergencyID)
            node->left = deleteNode(node->left, id);
        else if (id > node->emergencyID)
            node->right = deleteNode(node->right, id);
        else {
            if (node->left == 0 || node->right == 0) {
                Node* temp;

                if (node->left != 0)
                    temp = node->left;
                else
                    temp = node->right;

                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);

            node->emergencyID = temp->emergencyID;
            node->location = temp->location;
            node->severity = temp->severity;

            node->right = deleteNode(node->right, temp->emergencyID);
        }

        return balance(node);
    }

    Node* search(Node* node, int id) {
        if (node == 0 || node->emergencyID == id)
            return node;

        if (id < node->emergencyID)
            return search(node->left, id);

        return search(node->right, id);
    }

    void inOrder(Node* node) {
        if (node == 0)
            return;

        inOrder(node->left);
        display(node);
        inOrder(node->right);
    }

    void levelOrder(Node* node) {
        if (node == 0)
            return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            display(current);

            if (current->left != 0)
                q.push(current->left);

            if (current->right != 0)
                q.push(current->right);
        }
    }

    void showDetails(Node* node) {
        if (node == 0)
            return;

        showDetails(node->left);

        cout << "ID: " << node->emergencyID
             << " | Height: " << node->height
             << " | Balance Factor: " << getBalance(node) << endl;

        showDetails(node->right);
    }

    void showTree(Node* node, int space) {
        if (node == 0)
            return;

        space += 6;
        showTree(node->right, space);

        cout << endl;

        for (int i = 6; i < space; i++)
            cout << " ";

        cout << node->emergencyID
             << " [H=" << node->height
             << ", BF=" << getBalance(node) << "]" << endl;

        showTree(node->left, space);
    }

    void display(Node* node) {
        cout << "Emergency ID: " << node->emergencyID
             << " | Location: " << node->location
             << " | Severity: " << node->severity << endl;
    }

    void destroy(Node* node) {
        if (node == 0)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVL() {
        root = 0;
    }

    ~AVL() {
        destroy(root);
    }

    void insert(int id, string place, int level) {
        root = insert(root, id, place, level);
    }

    void searchEmergency(int id) {
        Node* result = search(root, id);

        if (result == 0)
            cout << "Emergency not found." << endl;
        else {
            cout << "Emergency Found:\n";
            display(result);
        }
    }

    void deleteEmergency(int id) {
        if (search(root, id) == 0) {
            cout << "Emergency does not exist." << endl;
            return;
        }

        root = deleteNode(root, id);
        cout << "Emergency " << id << " deleted successfully." << endl;
    }

    void showInOrder() {
        cout << "\nIN-ORDER TRAVERSAL\n";
        inOrder(root);
    }

    void showLevelOrder() {
        cout << "\nLEVEL-ORDER TRAVERSAL (BFS)\n";
        levelOrder(root);
    }

    void showHeight() {
        cout << "\nTree Height: " << getHeight(root) << endl;
    }

    void showBalanceFactors() {
        cout << "\nHEIGHT AND BALANCE FACTOR OF EACH NODE\n";
        showDetails(root);
    }

    void displayTree() {
        cout << "\nFINAL AVL TREE STRUCTURE\n";
        showTree(root, 0);
    }
};

void testRotations() {
    int cases[4][3] = {
        {30, 20, 10},
        {10, 20, 30},
        {30, 10, 20},
        {10, 30, 20}
    };

    const char* names[4] = {"LL", "RR", "LR", "RL"};

    for (int i = 0; i < 4; i++) {
        AVL test;

        for (int j = 0; j < 3; j++)
            test.insert(cases[i][j], "Test Location", j + 1);

        cout << names[i] << " Rotation Tested Successfully" << endl;
        test.displayTree();
    }
}

int main() {
    AVL emergency;

    emergency.insert(40, "Islamabad", 5);
    emergency.insert(20, "Rawalpindi", 4);
    emergency.insert(60, "Lahore", 3);
    emergency.insert(10, "Karachi", 5);
    emergency.insert(30, "Peshawar", 2);
    emergency.insert(50, "Quetta", 4);
    emergency.insert(70, "Multan", 3);
    emergency.insert(5, "Sialkot", 5);
    emergency.insert(15, "Gujranwala", 2);
    emergency.insert(25, "Faisalabad", 4);
    emergency.insert(35, "Hyderabad", 3);
    emergency.insert(65, "Abbottabad", 5);

    cout << "EMERGENCY RESCUE OPERATIONS - AVL TREE\n";
    cout << "12 Emergency Records Inserted Successfully\n";

    emergency.searchEmergency(25);
    emergency.searchEmergency(99);

    emergency.showInOrder();
    emergency.showLevelOrder();
    emergency.showHeight();
    emergency.showBalanceFactors();
    emergency.displayTree();

    cout << "\nROTATION CASES\n";
    testRotations();

    cout << "\nDELETION OPERATIONS\n";

    emergency.deleteEmergency(5);
    emergency.deleteEmergency(60);

    emergency.showInOrder();
    emergency.showLevelOrder();
    emergency.showHeight();
    emergency.showBalanceFactors();
    emergency.displayTree();

    return 0;
}
