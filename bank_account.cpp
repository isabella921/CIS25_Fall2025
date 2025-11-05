#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;
const string transaction_file = "transactions.txt";
class bank_account {
private:
    double balance;
    void saveTransaction(const string& type, double amount, const string& item = "") {
        ofstream outFile(transaction_file, ios::app);
        if (outFile.is_open()) {
            outFile << fixed << setprecision(2);
            if (type == "deposit") {
                outFile << "Deposit: +" << amount << "New balance: " << balance << endl;
            } else if (type == "purchase") {
                outFile << "Purchase: -" << amount << " (" << item << ") new balance: " << balance << endl;
            } else if (type == "intial depost") {
                outFile << "Initial deposit: +" << amount << " new balance: " << balance << endl;
            }
            outFile.close();
        } else {
            cout << "error: cannot open file" << endl;
        }
    }

public:
    bank_account(double initial_balance = 0.0) : balance(0.0) {
        if (initial_balance >= 0) {
            this->balance = initial_balance;
            saveTransaction("Initial deposit:", initial_balance);
        } else {
            cout << "cannot have a negative value. setting initial balance to $0.00" << endl;
            saveTransaction("Initial Deposit", 0.0);
        }
        cout << fixed << setprecision(2);
        cout << "Account created with initial balance: $" << this->balance << endl;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            saveTransaction("deposit", amount);
            cout << "deposit: $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be greater than $0.00." << endl;
        }
    }

    void makePurchase(double cost, const string& item) {
        if (cost > 0) {
            if (cost <= balance) {
                balance -= cost;
                saveTransaction("purchase", cost, item);
                cout << "Purchased: " << item << " for $" << cost << ". new balance: $" << balance << endl;
            } else {
                cout << "Transaction failed: insufficient funds for " << item << "." << endl;
            }
        } else {
            cout << "pPurchase cost must be above $0.00." << endl;
        }
    }

    void printFinalBalance() const {
        cout << "Final account balance: $" << balance << endl;
    }

    void displayTransactionHistory() const {
        ifstream inFile(transaction_file);
        string line;
        cout << "\n Transaction history from (transactions.txt)" << endl;
        if (inFile.is_open()) {
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Transaction history file not found" << endl;
        }
    }
};

int main() { //just a note everytime i run this file it adds to same transactions test so maybe delete old file after testing to submit new one for midtemr
    bank_account myAccount(500.00); 
    myAccount.deposit(150.75);
    myAccount.makePurchase(25.50, "Gold bean cafe");
    myAccount.deposit(200.00);
    myAccount.makePurchase(1000.00, "Apple laptop"); //this wone shoujld fail bc not enough funds
    myAccount.makePurchase(50.00, "trader joes");
    myAccount.printFinalBalance();
    myAccount.displayTransactionHistory();
    return 0;
}