this code usese a base class User and defines a method accessLevel which is declared as virtual. the User class has and prints "general Access"
then i have an employee class that publicly inherits from User. This class has and prints "Employee Access"
then the InventoryManager class inherits from Employee and has the highest level of access. THis class prints "Full Inventory Management Access"
in the module10.cpp file, we test the code by creating an InventoryManager object and calling the accessLevel() function which prints the access level.
