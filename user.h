#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>

class User {
public:
    virtual void accessLevel() const;
    virtual ~User() {}
};

class Employee : public User {
public:
    void accessLevel() const override;
    virtual ~Employee() {}
};

class InventoryManager : public Employee {
public:
    void accessLevel() const override;
    virtual ~InventoryManager() {}
};

#endif // USER_H