
#include <iostream>
using namespace std;

#define SIZE 5

struct Patient {
    int id;
    int priority;
};

Patient queue[SIZE];
int count = 0;

void enqueue(int id, int priority) {
    if (count == SIZE) {
        cout << "Queue is full! Cannot add patient.\n";
        return;
    }

    queue[count].id = id;
    queue[count].priority = priority;
    count++;

    cout << "Patient added successfully.\n";
}

void dequeue() {
    if (count == 0) {
        cout << "Queue is empty! No patient to treat.\n";
        return;
    }

    int highest = 0;

    for (int i = 1; i < count; i++) {
        if (queue[i].priority < queue[highest].priority) {
            highest = i;
        }
    }

    cout << "Patient P" << queue[highest].id
         << " is being treated.\n";

    for (int i = highest; i < count - 1; i++) {
        queue[i] = queue[i + 1];
    }

    count--;
}

void display() {
    if (count == 0) {
        cout << "No patients waiting.\n";
        return;
    }

    cout << "\nWaiting Patients:\n";

    for (int i = 0; i < count; i++) {
        cout << "Patient P" << queue[i].id
             << " | Priority: " << queue[i].priority << endl;
    }
}

int main() {
    int choice, id, priority;

    do {
        cout << "\n--- Hospital Emergency Department ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Treat Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient ID: P";
                cin >> id;
                cout << "Enter priority (1 = highest): ";
                cin >> priority;

                if (priority < 1) {
                    cout << "Invalid priority!\n";
                } else {
                    enqueue(id, priority);
                }
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
