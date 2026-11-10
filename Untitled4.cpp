#include <iostream>
#include <string>
using namespace std;

string conversion(int num) {
    if (num == 0)
        return "0";

    string binary = "";

    while (num > 0) {
        char bit = (num % 2) + '0';
        binary = bit + binary;
        num = num / 2;
    }

    return binary;
}

int main() {
    int num[10];

    cout << "Enter 10 decimal numbers: " << endl;

    for (int i = 0; i < 10; i++) {
        cin >> num[i];
    }

    for (int i = 0; i < 10; i++) {
        cout << "Binary: " << conversion(num[i]) << endl;
    }

    return 0;
}
