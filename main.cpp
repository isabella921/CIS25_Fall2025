#include "finance_tracker.h"
#include <iomanip>
#include <limits>

//protos for ui
void display_menu();
void handle_add_account(FinanceTracker& tracker);
void handle_record_transaction(FinanceTracker& tracker);
void handle_generate_report(FinanceTracker& tracker);

int main() {
    FinanceTracker tracker;  //initializes and then loads data
    tracker.display_summary();  //checks if loaded successfully

    int choice;
    do {
        display_menu();
        std::cout << "enter choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "invalid input.\n";
            std::cin.clear(); //clears error flags and discards bad input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        //menu
        switch (choice) {
            case 1:
                handle_add_account(tracker);
                break;
            case 2:
                handle_record_transaction(tracker);
                break;
            case 3:
                tracker.display_summary();
                break;
            case 4:
                handle_generate_report(tracker);
                break;
            case 5:
                std::cout << "exiting application. data will be saved.\n"; //deconstruction happens automatically when program exited
                break;
            default:
                std::cout << "invalid choice. please try again.\n";
        }

    } while (choice != 5);
    return 0;
}

//displays menu for gui
void display_menu() {
    std::cout << "Bella's Personal Finance Tracker\n";
    std::cout << "1. Add New Account\n";
    std::cout << "2. Record Transaction (Income/Expense)\n";
    std::cout << "3. View Account Summary\n";
    std::cout << "4. Generate Report\n";
    std::cout << "5. Exit\n";
}

//handles user input for adding a new account.
void handle_add_account(FinanceTracker& tracker) {
    std::string name;
    double balance = 0.0;
    std::cout << "\nTO ADD NEW ACCOUNT:\n";
    std::cout << "Enter account name (Checking, Savings): ";
    std::getline(std::cin, name);

    std::cout << "Enter initial balance: $";
    if (!(std::cin >> balance)) {
        std::cout << "invalid balance. cannot create account\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tracker.add_account(name, balance);
}

//handles user input for transaction
void handle_record_transaction(FinanceTracker& tracker) {
    std::string account_name, type, category, description;
    double amount;
    int type_choice;
    std::cout << "\nTO RECORD TRANSACTION\n";
    std::cout << "Enter account name for transaction: ";
    std::getline(std::cin, account_name);
    
    if (!tracker.get_account(account_name)) { //check account exists first
        std::cout << "Account not found. Please create account first.\n";
        return;
    }
    std::cout << "Transaction type (1 - Income, 2 - Expense): ";

    if (!(std::cin >> type_choice) || (type_choice != 1 && type_choice != 2)) {
        std::cout << "Invalid choice. Transaction failed.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    type = (type_choice == 1) ? "Income" : "Expense";

    std::cout << "Enter category (ex: Salary, Rent, Groceries): ";
    std::getline(std::cin, category);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);
    std::cout << "Enter amount: $";

    if (!(std::cin >> amount) || amount <= 0) {
        std::cout << "Invalid amount. Transaction failed.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tracker.record_transaction(account_name, type, category, description, amount);
}

//handles input 4 generating a specific account report.
void handle_generate_report(FinanceTracker& tracker) {
    std::string account_name;
    std::cout << "\nGENERATE REPORT\n";
    std::cout << "Enter account name for report: ";
    std::getline(std::cin, account_name);
    tracker.generate_report(account_name);
}