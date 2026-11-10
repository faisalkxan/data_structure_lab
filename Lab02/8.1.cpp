#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int index, newValue;

    cout << "Current array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Enter index to update (0-4): ";
    cin >> index;
    cout << "Enter new value: ";
    cin >> newValue;

    arr[index] = newValue;

    cout << "Updated array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
