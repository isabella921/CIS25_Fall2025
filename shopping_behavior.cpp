#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

/* file structure and logic

data structure Class (CustomerRecord):
defines the 5 required fields from  'shopping_behavior_updated.csv'
file: ID, Age, Gender, Item Purchased, and Category.
encapsulates the data for a single row/entry

util func (split):
parses a single line of CSV file,
splitting the string based on comma.

main function (main):
opens the CSV file ('shopping_behavior_updated.csv').
reads line by line, skipping the header line.
uses 'split' to parse each line.
converts the parsed string tokens (the first 5 columns) to their
appropriate data types (int, int, string, string, string).
stores the CustomerRecord objects in a vector.
displays the loaded data in a formatted table. */

// class to store data from CSV
class CustomerRecord {
public:
    int customer_id;
    int age;
    string gender;
    string item_purchased;
    string category;

    //constructor, takes in paramteres
    CustomerRecord(int id, int a, const string& g, const string& item, const string& cat)
        : customer_id(id), age(a), gender(g), item_purchased(item), category(cat) {}

    //method to display info and also sets width to make prettier lol
    void display() const {
        cout << "| " << setw(10) << customer_id
             << " | " << setw(4) << age
             << " | " << setw(7) << left << gender
             << " | " << setw(18) << left << item_purchased 
             << " | " << setw(15) << left << category
             << " |" << endl;
    }
};

//util function to split data
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    //vector to hold all data from dataset
    vector<CustomerRecord> dataset;
    string filename = "shopping_behavior_updated.csv";
    ifstream file(filename);

    //checks if file was opened
    if (!file.is_open()) {
        cerr << "error could not open the file" << filename << endl;
        return 1;
    }

    string line;
    //read and discard header line
    if (getline(file, line)) {
        cout << "header skipped: " << line.substr(0, line.find("purchase amount (USD)")) << "..." << endl;
    }

    int entries_loaded = 0;
    const int min_entries = 10;

    //reads from csv as a class, reads data by line until eof or min entries
    while (getline(file, line) && entries_loaded < min_entries) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() >= 5) { //check if at least 5 tokens
            try {
                int customer_id = stoi(tokens[0]); //index 0 is id
                int age = stoi(tokens[1]); //index1 is age
                string gender = tokens[2]; //index2 is gender shud be string
                string item_purchased = tokens[3]; //index3 is items purchased
                string category = tokens[4]; //index 4 is category

                //create new object and add to vector
                dataset.emplace_back(customer_id, age, gender, item_purchased, category);
                entries_loaded++;

            } catch (const std::exception& e) {
                //to catch errors not sure if this works tho
                cerr << "skipping errored row: " << line.substr(0, 50) << "... (" << e.what() << ")" << endl;
            }
        } else {
            cerr << "skipping row with not enough data: " << line << endl;
        }
    }

    file.close();

    cout << "\ndata parsing complete" << endl;
    cout << entries_loaded << " entries load" << endl;
    cout << "\nENTRIES" << endl;
    cout << "| " << setw(10) << "customer ID"
         << " | " << setw(4) << "age"
         << " | " << setw(7) << left << "gender"
         << " | " << setw(18) << left << "item Purchased"
         << " | " << setw(15) << left << "category"
         << " |" << endl;

    //iterates thru dataset and prints each item
    for (const auto& record : dataset) {
        record.display();
    }
    return 0;
}
/*output
header skipped: Customer ID,Age,Gender,Item Purchased,Category,Purchase Amount (USD),Location,Size,Color,Season,Review Rating,Subscription Status,Shipping Type,Discount A...ied,Promo Code Used,Previous Purchases,Payment Method,Frequency of Purchases

data parsing complete
10 entries load

ENTRIES
| customer ID |  age | gender  | item Purchased     | category        |
| 1          | 55   | Male    | Blouse             | Clothing        |
| 2          | 19   | Male    | Sweater            | Clothing        |
| 3          | 50   | Male    | Jeans              | Clothing        |
| 4          | 21   | Male    | Sandals            | Footwear        |
| 5          | 45   | Male    | Blouse             | Clothing        |
| 6          | 46   | Male    | Sneakers           | Footwear        |
| 7          | 63   | Male    | Shirt              | Clothing        |
| 8          | 27   | Male    | Shorts             | Clothing        |
| 9          | 26   | Male    | Coat               | Outerwear       |
| 10         | 57   | Male    | Handbag            | Accessories     |*/