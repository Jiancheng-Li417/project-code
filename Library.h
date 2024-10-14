#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "LibraryItem.h"
#include "User.h"

class Library {
private:
    std::vector<LibraryItem*> items;    
    std::vector<User*> users;           

public:
    
    ~Library();

    void addItem(LibraryItem* item);

    void addUser(User* user);

    void displayAllItems() const;

    void displayAllUsers() const;

    LibraryItem* findItem(const std::string& title) const;
    
    User* findUser(const std::string& name) const;

    void saveToFile(const std::string& filename) const;

    void loadFromFile(const std::string& filename);
};

#endif 