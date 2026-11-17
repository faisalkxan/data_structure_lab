#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    int flightNumber;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int number, string place, string time) {
        flightNumber = number;
        destination = place;
        departureTime = time;
        left = 0;
        right = 0;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int number, string place, string time) {
        if (node == 0)
            return new Node(number, place, time);

        if (number < node->flightNumber)
            node->left = insert(node->left, number, place, time);
        else if (number > node->flightNumber)
            node->right = insert(node->right, number, place, time);

        return node;
    }

    Node* search(Node* node, int number) {
        if (node == 0 || node->flightNumber == number)
            return node;

        if (number < node->flightNumber)
            return search(node->left, number);

        return search(node->right, number);
    }

    Node* findMin(Node* node) {
        while (node != 0 && node->left != 0)
            node = node->left;

        return node;
    }

    Node* findMax(Node* node) {
        while (node != 0 && node->right != 0)
            node = node->right;

        return node;
    }

    Node* deleteNode(Node* node, int number) {
        if (node == 0)
            return 0;

        if (number < node->flightNumber)
            node->left = deleteNode(node->left, number);
        else if (number > node->flightNumber)
            node->right = deleteNode(node->right, number);
        else {
            if (node->left == 0) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == 0) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->flightNumber = temp->flightNumber;
            node->destination = temp->destination;
            node->departureTime = temp->departureTime;
            node->right = deleteNode(node->right, temp->flightNumber);
        }

        return node;
    }

    void inOrder(Node* node) {
        if (node == 0)
            return;

        inOrder(node->left);
        display(node);
        inOrder(node->right);
    }

    void preOrder(Node* node) {
        if (node == 0)
            return;

        display(node);
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == 0)
            return;

        postOrder(node->left);
        postOrder(node->right);
        display(node);
    }

    int countNodes(Node* node) {
        if (node == 0)
            return 0;

        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int height(Node* node) {
        if (node == 0)
            return -1;

        return 1 + max(height(node->left), height(node->right));
    }

    void display(Node* node) {
        cout << "Flight Number: " << node->flightNumber
             << " | Destination: " << node->destination
             << " | Departure: " << node->departureTime << endl;
    }

    void showTree(Node* node, int space) {
        if (node == 0)
            return;

        space += 6;
        showTree(node->right, space);

        cout << endl;
        for (int i = 6; i < space; i++)
            cout << " ";
        cout << node->flightNumber << endl;

        showTree(node->left, space);
    }

    void destroy(Node* node) {
        if (node == 0)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() {
        root = 0;
    }

    ~BST() {
        destroy(root);
    }

    void insert(int number, string place, string time) {
        root = insert(root, number, place, time);
    }

    void searchFlight(int number) {
        Node* result = search(root, number);

        if (result == 0)
            cout << "Flight not found." << endl;
        else {
            cout << "Flight Found:" << endl;
            display(result);
        }
    }

    void deleteFlight(int number) {
        if (search(root, number) == 0) {
            cout << "Flight does not exist." << endl;
            return;
        }

        root = deleteNode(root, number);
        cout << "Flight " << number << " deleted successfully." << endl;
    }

    void showInOrder() {
        cout << "\nIN-ORDER TRAVERSAL\n";
        inOrder(root);
    }

    void showPreOrder() {
        cout << "\nPRE-ORDER TRAVERSAL\n";
        preOrder(root);
    }

    void showPostOrder() {
        cout << "\nPOST-ORDER TRAVERSAL\n";
        postOrder(root);
    }

    void showMinMax() {
        if (root == 0) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "\nMinimum Flight: " << findMin(root)->flightNumber << endl;
        cout << "Maximum Flight: " << findMax(root)->flightNumber << endl;
    }

    void showCountHeight() {
        cout << "\nTotal Flights: " << countNodes(root) << endl;
        cout << "Tree Height: " << height(root) << endl;
    }

    void displayTree() {
        cout << "\nBST STRUCTURE\n";
        showTree(root, 0);
    }
};

int main() {
    BST airport;

    airport.insert(500, "London", "08:00");
    airport.insert(300, "Dubai", "08:30");
    airport.insert(700, "Istanbul", "09:00");
    airport.insert(200, "Doha", "09:30");
    airport.insert(400, "Paris", "10:00");
    airport.insert(600, "Riyadh", "10:30");
    airport.insert(800, "Toronto", "11:00");
    airport.insert(100, "Muscat", "11:30");
    airport.insert(250, "Baku", "12:00");
    airport.insert(350, "Rome", "12:30");
    airport.insert(450, "Tokyo", "13:00");
    airport.insert(650, "Jeddah", "13:30");

    cout << "AIRPORT FLIGHT SCHEDULING SYSTEM\n";
    cout << "12 Flights Inserted Successfully\n";

    airport.searchFlight(400);
    airport.searchFlight(999);

    airport.showInOrder();
    airport.showPreOrder();
    airport.showPostOrder();
    airport.showMinMax();
    airport.showCountHeight();
    airport.displayTree();

    cout << "\nDELETION OPERATIONS\n";
    airport.deleteFlight(100);
    airport.deleteFlight(600);
    airport.deleteFlight(300);

    airport.showInOrder();
    airport.showCountHeight();
    airport.displayTree();

    return 0;
}
