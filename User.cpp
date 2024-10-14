#include "User.h"
#include <iostream>
#include <algorithm>

User::User(const std::string& name, const std::string& id) : name(name), id(id) {}


void User::borrowItem(LibraryItem* item) {
    if (!item->isCheckedOut()) {
        item->checkOut();
        borrowedItems.push_back(item);
        std::cout << name << " has successfully borrowed " << item->getTitle() << std::endl;
    } else {
        std::cout << "Sorry, " << item->getTitle() << " is already checked out." << std::endl;
    }
}


bool User::returnItem(LibraryItem* item) {
    auto it = std::find(borrowedItems.begin(), borrowedItems.end(), item);
    if (it != borrowedItems.end()) {
        item->checkIn();
        borrowedItems.erase(it);
        std::cout << name << " has successfully returned " << item->getTitle() << std::endl;
        return true;
    } else {
        std::cout << "Error：" << name << " has not borrowed " << item->getTitle() << std::endl;
        return false;
    }
}

void User::displayBorrowedItems() const {
     std::cout << "Items borrowed by " << name << ":" << std::endl;
    for (const auto& item : borrowedItems) {
        std::cout << "- " << item->getTitle() << " (" << item->getType() << ")" << std::endl;
    }
}

std::string User::getName() const {
    return name;
}

std::string User::getId() const {
    return id;
}