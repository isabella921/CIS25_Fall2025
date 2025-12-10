#include "finance_tracker.h"
#include <map>
#include <iomanip>
using namespace std;
//helper funcs

void FinanceTracker::save_data() { //saves all account and transaction data to file
    std::ofstream outfile(DATA_FILE);
    if (!outfile.is_open()) {
        std::cerr << "error could not open file." << std::endl;
        return;
    }

        outfile << accounts.size() << std::endl; //writes number of accs

    for (const auto& acc : accounts) { //writes each account details and transactions such as name, balance, transaction count
        outfile << acc.name << "," << acc.balance << "," << acc.transactions.size() << "\n";
            for (const auto& t : acc.transactions) {
                outfile << t.to_csv() << std::endl;
        }
    }
    outfile.close();
    std::cout << "data saved successfully.\n";
}

void FinanceTracker::load_data() { //loads all account and transaction data from file
    std::ifstream infile(DATA_FILE);
    if (!infile.is_open()) { //file does not exist yet so we start with empty file
        return;
    }
    std::string line;
    size_t num_accounts = 0;
    if (std::getline(infile, line)) { //reads number of accounts
        try { num_accounts = std::stoul(line);
        } catch (...) {
            std::cerr << "warning: data file error or empty.\n"; //incase of malformed files
            infile.close();
            return;
        }
    }

    for (size_t i = 0; i < num_accounts; ++i) { //read each account and transactions
        if (std::getline(infile, line)) { //reads header
            std::stringstream ss(line);
            std::string name_str, balance_str, num_transactions_str;
            std::getline(ss, name_str, ',');
            std::getline(ss, balance_str, ',');
            std::getline(ss, num_transactions_str, ',');
            double balance = std::stod(balance_str);
            size_t num_transactions = std::stoul(num_transactions_str);
            Account acc(name_str, balance);

            for (size_t j = 0; j < num_transactions; ++j) { //reads each transaction
                if (std::getline(infile, line)) {
                    std::stringstream ts(line);
                    std::string date, type, category, description, amount_str;
                    std::getline(ts, date, ',');
                    std::getline(ts, type, ',');
                    std::getline(ts, category, ',');
                    std::getline(ts, description, ',');
                    std::getline(ts, amount_str, ',');
                    double amount = std::stod(amount_str);
                    Transaction t(date, type, category, description, amount);
                    //add transaction w out updating balance
                    acc.transactions.push_back(t); 
                }
            }
            accounts.push_back(acc);
        }
    }
    infile.close();
}

FinanceTracker::FinanceTracker() { //constructor loads existing data when created
    load_data();
}

FinanceTracker::~FinanceTracker() { //deconstructor saves data when program exit
    save_data();
}

void FinanceTracker::add_account(const std::string& name, double initial_balance) { //adds new acc to tracker
    if (get_account(name) != nullptr) {
        std::cout << "account '" << name << "' already exists.\n";
        return;
    }
        accounts.emplace_back(name, initial_balance);
    std::cout << "account '" << name << "' created with initial balance $" << initial_balance << ".\n";
}

Account* FinanceTracker::get_account(const std::string& name) 
{ //gets pointer to an account by name. only for internal usse
    for (auto& acc : accounts) {
        if (acc.name == name) {
            return &acc;
        }
    }
    return nullptr;
}

//recorrds new transaction into specific account.
void FinanceTracker::record_transaction(const std::string& account_name, const std::string& type, const std::string& category, const std::string& description, double amt) {
    Account* acc = get_account(account_name);
    if (!acc) {
        std::cout << "error: account '" << account_name << "' not found.\n";
        return;
    }
    std::string date = get_current_date();
    Transaction t(date, type, category, description, amt);
    acc->add_transaction(t);
    std::cout << type << " of $" << amt << " recorded in " << account_name << ".\n";
}

void FinanceTracker::display_summary() const { //displays current balance for all accounts
 
    double total_net_worth = 0.0;
    std::cout << "\nfinancial summary:\n";
    for (const auto& acc : accounts) {
        std::cout << "account: " << acc.name << " ---  balance: $" << acc.balance << "\n";
        total_net_worth += acc.balance;
    }
    if (total_net_worth == 0.0 && accounts.empty()) {
        std::cout << "no accounts found.\n";}
    std::cout << "total net worth: $" << total_net_worth << std::endl;
}

void FinanceTracker::generate_report(const std::string& account_name) const { //creates report with sorted transactions and category totals for specific account
    const Account* acc = nullptr;
    for (const auto& a : accounts) {
        if (a.name == account_name) {
            acc = &a;
            break;
        }
    }
    if (!acc) 
    {
        std::cout << "error: account '" << account_name << "' not found.\n";
        return;
    }

    std::vector<Transaction> sorted_transactions = acc->transactions;
    std::sort(
        sorted_transactions.begin(), 
        sorted_transactions.end(), //sorts transactions by date (uses string comparison)
        [](const Transaction& a, const Transaction& b) {
            return a.date < b.date;
        }
    );

    std::cout << "\ntransaction report for " << acc->name << std::endl;
    std::cout << "current balance: $" << acc->balance << std::endl;
    std::cout << "category summary\n";
    std::map<std::string, double> cat_totals;
    double total_income = 0.0;
    double total_expense = 0.0;

    for (const auto& t : sorted_transactions) 
    {
        if (t.type == "income") 
        {
            cat_totals["income: " + t.category] += t.amount;
            total_income += t.amount;
        } else {
            cat_totals["expense: " + t.category] += t.amount;
            total_expense += t.amount;
        }
    }

    for (const auto& pair : cat_totals) {
        std::cout << pair.first << ": $" << pair.second << std::endl;
    }
    std::cout << "total income: $" << total_income << std::endl;
    std::cout << "total expense: $" << total_expense << std::endl;
    std::cout << "net flow: $" << (total_income - total_expense) << "\n";

    std::cout << "detailed transactuions by date\n";
    for (const auto& t : sorted_transactions) {
        std::cout << "[" << t.date << "] | " 
                  << (t.type == "Income" ? "INCOME" : "EXPENSE") << " | "
                  << "$" << t.amount << " | " << t.category << " | " 
                  << t.description << "\n";
    }
}

std::string FinanceTracker::get_current_date() { //gets current date as stiring in YYYYMMDD format
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << std::setfill('0') << std::setw(2) << 1 + ltm->tm_mon << "-" 
       << std::setfill('0') << std::setw(2) << ltm->tm_mday;
    return ss.str();
}