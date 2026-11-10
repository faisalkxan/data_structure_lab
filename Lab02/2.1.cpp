#include <iostream>
using namespace std;

int main() {
    int arr[10];
    int evenCount = 0, oddCount = 0;
    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
        if (arr[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }
    cout << "Even count: " << evenCount << endl;
    cout << "Odd count: " << oddCount << endl;
    return 0;
}
