#include <iostream>
using namespace std;

int main() {
    int matrix[3][3];
    int sum = 0;

    cout << "Enter elements for a 3x3 matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> matrix[i][j];
            sum += matrix[i][j];
        }
    }

    cout << "Sum of all elements: " << sum << endl;
    return 0;
}
