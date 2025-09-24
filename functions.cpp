#include "functions.h" 
#include <iostream> 

using namespace std;

void addNumbers() {
    int first, second;
    cout << "\n--- Add Numbers ---\n";
    cout << "Enter the first number: \n";
    cin >> first;
    cout << "Enter the second number: \n";
    cin >> second;
    cout << "The sum is: " << first + second << "\n";
}


void sayHello() {
    cout << "\n--- Saying Hello ---\n";
    cout << "hello! hope you are having a good day\n";
}
