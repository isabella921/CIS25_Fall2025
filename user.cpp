#include "user.h"

void User::accessLevel() const {
    std::cout << "General Access\n";
}

void Employee::accessLevel() const {
    std::cout << "Employee Access\n";
}

void InventoryManager::accessLevel() const {
    std::cout << "Full Inventory Management Access\n"; 
}