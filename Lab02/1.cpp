#include <iostream>
using namespace std;

int main() {
    int arr[10];
    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    cout << "\nElements with their indexes:\n";
    for (int i = 0; i < 10; i++) {
        cout << "Index " << i << ": " << arr[i] << endl;
    }
    return 0;
}
