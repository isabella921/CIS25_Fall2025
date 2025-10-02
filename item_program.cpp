#include <iostream> 
#include <fstream>  
#include <string>   

using namespace std;

class Item {
public:
    string name;
    int quantity;

    void saveToFile() {
        ofstream outFile("data.txt");
        if (outFile.is_open()) {
            outFile << name << " " << quantity << endl;
            outFile.close();
            cout << "data for " << name << " saved  to data.txt." << endl;
        } 
        else {
            cout << "error: file cannot e opened" << endl;
        }
    }

    void loadFromFile() {
        ifstream inFile("data.txt");
        if (inFile.is_open()) {
            string loaded_name;
            int loaded_quantity;
            if (inFile >> loaded_name >> loaded_quantity) {
                this->name = loaded_name;
                this->quantity = loaded_quantity;
                cout << "name: " << this->name << endl;
                cout << "quantity: " << this->quantity << endl;
            } else {
                cout << "error: cannot load file" << endl;
            }
            inFile.close();
        } else {
            cout << "error: file cannot be read" << endl;
        }
    }
};

int main() {
    Item tool;
    tool.name = "Wrench"; 
    tool.quantity = 25;   
    tool.saveToFile();
    tool.name = "Placeholder";
    tool.quantity = 0;
    cout << "\ncurrent:" << tool.name << endl;
    tool.loadFromFile();
    cout << "after load: " << tool.quantity << " units of " << tool.name << ".\n" << endl;
    return 0;
}
