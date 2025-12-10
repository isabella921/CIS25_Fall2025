#include <iostream>
#include <string> 
using namespace std;

class Product {
private:
    int id;
    string name;
    float price;

public:
    Product() : id(0), name("Unknown"), price(0.0) {
        cout << "default constructor" << endl;
    }
    Product(int i, string n, float p) : id(i), name(n), price(p) {
        cout << "constructor called." << name << " (ID: " << id << ")." << endl;
    }

    ~Product() {
        cout << "destructor called for " << name << " (ID: " << id << ")." << endl;
    }
    void printDetails() {
        cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

int main() {
    cout << "creating new product" << endl;
    Product productA(101, "Notebook", 4.99); 
    
    cout << "\ncreating default product" << endl;
    Product productB; 
    cout << "newproduct: ";
    productA.printDetails();
    
    cout << "default product: ";
    productB.printDetails();
    return 0;
}