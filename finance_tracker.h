#ifndef finance_tracker_h
#define finance_tracker_h
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <ctime>

//data structures
class Transaction {
public:
    std::string date;
    std::string type; //either income or expense type
    std::string category;
    std::string description;
    double amount;

    //constructor for class
    Transaction(std::string d, std::string t, std::string cat, std::string desc, double amt)
        : date(d), type(t), category(cat), description(desc), amount(amt) {}

    //method to convert transaction into string for file storage in csv
    std::string to_csv() const {
        return date + "," + type + "," + category + "," + description + "," + std::to_string(amount);
    }
};

class Account {
public:
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

    //constructor
    Account(std::string n, double bal = 0.0) : name(n), balance(bal) {}

    //method to add transaction and update balance
    void add_transaction(const Transaction& t) {
        transactions.push_back(t);
        if (t.type == "Income") {
            balance += t.amount;
        } else {
            balance -= t.amount;
        }
    }

    //method to convert account to string for file storage
    std::string to_string() const {
        return name + "," + std::to_string(balance);
    }
};
//THIS IS MAIN CLASS
class FinanceTracker {
private:
    std::vector<Account> accounts;
    const std::string DATA_FILE = "finance_data.txt";
    //helper funcs
    void save_data();
    void load_data();

public:
    FinanceTracker();
    ~FinanceTracker(); //deconstructor to make sure data is saved when exited

    void add_account(const std::string& name, double initial_balance = 0.0);
    Account* get_account(const std::string& name);

    void record_transaction(const std::string& account_name, const std::string& type, 
                            const std::string& category, const std::string& description, 
                            double amount);
    
    void display_summary() const;
    void generate_report(const std::string& account_name) const;

    //funct to get date in YYYY-MM-DD
    std::string get_current_date();
};

#endif // finance_tracker_h