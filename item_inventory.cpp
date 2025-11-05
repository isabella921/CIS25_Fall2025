#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

class Item {
public:
    std::string item_name;
    int quantity;
    Item() : item_name(""), quantity(0) {}
    Item(const std::string& n, int q) : item_name(n), quantity(q) {} //constructer
};

void displayInventory(const Item inventory[], int size) {
    if (size == 0) {
        std::cout << "\nInventory is currently empty.\n";
        return;
    }

    std::cout << "\ncurrent inventory:\n";
    std::cout << std::left << std::setw(20) << "Item name" << "Quantity\n";
    for (int i=0; i < size; ++i) {
        if (!inventory[i].item_name.empty()) {
            std::cout << std::left << std::setw(20) << inventory[i].item_name << inventory[i].quantity << "\n";
        }
    }
}

void searchItem(const Item inventory[], int size, const std::string& searchName) {
    bool found = false;
    for (int i= 0; i <size; ++i) {
        if (inventory[i].item_name == searchName) {
            std::cout << "\nThe quantity of " << inventory[i].item_name << " is: " << inventory[i].quantity << "\n";
            found = true;
            break; 
        }
    }
    if (!found) {
        std::cout << "\nitem " << searchName << " not found in the inventory.\n";
    }
}

void updateItemQuantity(Item inventory[], int size, const std::string& updateName) { //this is my optional add in bella make sure this works
    int newQuantity;
    bool found = false;
    for (int i=0; i< size; ++i) {
        if (inventory[i].item_name == updateName) {
            found = true;
            std::cout << "current quantity for " << updateName << " is: " << inventory[i].quantity << "\n";
            std::cout << "Please enter the new quantity: ";
            while (!(std::cin >> newQuantity) || newQuantity < 0) {
                std::cout << "inventory cannot be a negative number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            inventory[i].quantity = newQuantity;
            std::cout << "quantity for " << updateName << "successfully updated to" << newQuantity << ".\n";
            return;
        }
    }
    if (!found) {std::cout << "item" << updateName << "not found. cannot update the quantity.\n";
    }
}

void deleteItemByName(Item inventory[], int* size, const std::string& deleteName) { //also optional - supposed to select item and delete
    int indexToDelete = -1;
    for (int i = 0; i < *size; ++i) {
        if (inventory[i].item_name == deleteName) {
            indexToDelete = i; //bel this shifts everything donw i believe u cant delete from a fixed array
            break;
        }
    }
    if (indexToDelete == -1) {
        std::cout << "\nItem" << deleteName << "was not found. Cannot delete.\n";
        return;
    }
    for (int i = indexToDelete; i < *size - 1; ++i) {
        inventory[i] = inventory[i + 1];
    }
    (*size)--;
    inventory[*size] = Item("", 0);  //clears last element
    std::cout << "\nItem" << deleteName << " was deleted.\n";
}

int main() {
    const int MAX_INVENTORY_SIZE = 5;
    Item inventory[MAX_INVENTORY_SIZE] = {}; 
    int currentItemCount = 0; 
    std::cout << "\n Inventory Setup: (max " << MAX_INVENTORY_SIZE << " items)\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears buffer
    for (int i = 0; i < MAX_INVENTORY_SIZE; ++i) {
        std::string nameInput;
        int quantityInput;
        std::cout << "\nEnter info for item #" << currentItemCount + 1 << " (or type quit to exit):\n";
        std::cout << "Name: ";
        std::getline(std::cin, nameInput);
        if (nameInput == "quit" || nameInput == "Quit") {
            std::cout << "\nstopping entry.\n";
            break;
        }
        std::cout << "Quantity: ";
        while (!(std::cin >> quantityInput) || quantityInput < 0) {
            std::cout << "Error. quanitity cannot be negative: ";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inventory[i].item_name = nameInput;
        inventory[i].quantity = quantityInput;
        currentItemCount++;
    }

    displayInventory(inventory, currentItemCount);
    std::cout << "\ndelete item:\n";
    if (currentItemCount > 0) {
        std::string deleteName;
        std::cout << "Enter name of the item you wish to delete: ";
        if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::getline(std::cin, deleteName);
        deleteItemByName(inventory, &currentItemCount, deleteName);
        displayInventory(inventory, currentItemCount); 
    } else { std::cout << "there are no items to be deleted.\n";
    }
    std::cout << "\nsearch for item:\n";
    if (currentItemCount > 0) {
        std::string searchName;
        std::cout << "Enter name of the item you want to search for:";
        if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::getline(std::cin, searchName);
        searchItem(inventory, currentItemCount, searchName);
    }
    std::cout << "\nupdate quantity for an item:\n";
    if (currentItemCount > 0) {
        std::string updateName;
        std::cout << "Enter name of the item you want to update the quanitity of: ";
        if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::getline(std::cin, updateName);
        updateItemQuantity(inventory, currentItemCount, updateName);
        displayInventory(inventory, currentItemCount);
    }
    std::cout << "\ndone:)\n";
    return 0;
}
