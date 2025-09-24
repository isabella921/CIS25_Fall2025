#include <iostream>
#include "functions.h" 

using namespace std;

void showMenu() {
    cout << "\n--- Welcome to Menu! ---\n";
    cout << "1. Add Two Numbers\n";
    cout << "2. Say hello\n";
    cout << "3. Exit\n"; 
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu(); 
        cin >> choice; 

        switch (choice) {
            case 1:
                addNumbers(); 
                break;
            case 2:
                sayHello(); 
                break;
            case 3:
                cout << "Exiting program. byebye! \n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 3); 

    return 0;
}
