#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct Item {
    std::string name;
    int id;
};

bool compareByID(const Item& a, const Item& b) {
    return a.id < b.id;
}

Item* binarySearch(Item* arr, int size, int targetID) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        
        int mid = low + (high - low) / 2;

        if (arr[mid].id == targetID) {
            return &arr[mid]; //if found
        } else if (arr[mid].id < targetID) {
            low = mid + 1; //search upper
        } else {
            high = mid - 1;
        }
    }

    return nullptr; //didnt find anything
}

int main() {
    const int INVENTORY_SIZE = 100;
    Item* inventory = new Item[INVENTORY_SIZE];

    std::cout << "inventory system\n";
    std::cout << "allocated memory for " << INVENTORY_SIZE << " items.\n\n";

    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        inventory[i].id = 100 + i;
        inventory[i].name = "item #" + std::to_string(inventory[i].id);
    }
    std::sort(inventory, inventory + INVENTORY_SIZE, compareByID);

    int targetID;
    std::cout << "please enter an id to search for: ";
    if (!(std::cin >> targetID)) {
        std::cerr << "error, invalid input\n";
        delete[] inventory;
        return 1;
    }

    Item* foundItem = binarySearch(inventory, INVENTORY_SIZE, targetID); //bella make sure this searches properly pls

    std::cout << "\nresult:n";
    if (foundItem) {
        std::cout << "success! item found:\n";
        std::cout << "ID:" << foundItem->id << "\n";
        std::cout << "Name: " << foundItem->name << "\n";
    } else {
        std::cout << "failed. id " << targetID << " was not found in inventory.\n";
    }

    std::cout << "deleting memory...\n";
    delete[] inventory;
    inventory = nullptr;

    std::cout << "complete\n";
    return 0;
}