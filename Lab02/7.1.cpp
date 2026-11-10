#include <iostream>
using namespace std;

int main() {
    int arr[5] = {15, 25, 35, 45, 55};
    int value, foundIndex = -1;

    cout << "Enter value to search: ";
    cin >> value;

    for (int i = 0; i < 5; i++) {
        if (arr[i] == value) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        cout << "Element found at index: " << foundIndex << endl;
    } else {
        cout << "Element Not Found." << endl;
    }

    return 0;
}
