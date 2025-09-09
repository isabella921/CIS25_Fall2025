#include <iostream>
using namespace std;

int main() {
    char item_name[100];
    int item_quantity;
    float item_cost;
    float total_cost;

    cout << "Enter the name of item:";
    cin >> item_name;
    cout << "Enter cost of 1 " << item_name << ":";
    cin>> item_cost;
    cout << "Enter the quantity of " << item_name << ":";
    cin >> item_quantity;

    total_cost = item_quantity * item_cost;

    cout << "--- Order Summary --- \nItem: " << item_name << "\nItem Quantity: " << item_quantity << "\nCost per Item: $" << item_cost ;
    cout << "\nTotal cost for " << item_quantity << " " << item_name << "s: $" << total_cost << endl;
    return 0;

}