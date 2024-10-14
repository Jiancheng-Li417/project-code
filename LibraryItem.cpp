#include "LibraryItem.h"
#include <iostream>

LibraryItem::LibraryItem(const std::string& title, const std::string& id)
    : title(title), id(id), checkedOut(false) {}

void LibraryItem::checkOut() {
    if (!checkedOut) {
        checkedOut = true;
        std::cout << "Item checked out successfully." << std::endl;
    } else {
        std::cout << "Item is already checked out." << std::endl;
    }
}

void LibraryItem::checkIn() {
    if (checkedOut) {
        checkedOut = false;
        std::cout << "Item checked in successfully." << std::endl;
    } else {
        std::cout << "Item is already checked in." << std::endl;
    }
}

bool LibraryItem::isCheckedOut() const {
    return checkedOut;
}

std::string LibraryItem::getTitle() const {
    return title;
}

std::string LibraryItem::getId() const {
    return id;
}

