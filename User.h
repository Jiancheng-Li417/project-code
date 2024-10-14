#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "LibraryItem.h"

class User {
private:
    std::string name;                
    std::string id;                  
    std::vector<LibraryItem*> borrowedItems; 
public:

    User(const std::string& name, const std::string& id);

    void borrowItem(LibraryItem* item);

    bool returnItem(LibraryItem* item);

    void displayBorrowedItems() const;

    std::string getName() const;

    std::string getId() const;
};

#endif 