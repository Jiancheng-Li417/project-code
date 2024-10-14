#include "Library.h"
#include "Book.h"
#include "DVD.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Library::~Library() {
    for (auto item : items) {
        delete item;
    }
    for (auto user : users) {
        delete user;
    }
}

void Library::addItem(LibraryItem* item) {
    items.push_back(item);
}

void Library::addUser(User* user) {
    users.push_back(user);
}

void Library::displayAllItems() const {
    std::cout << "Library Collection：" << std::endl;
    for (const auto& item : items) {
        item->displayInfo();
        std::cout << std::endl;
    }
}

void Library::displayAllUsers() const {
    std::cout << "Library Users：" << std::endl;
    for (const auto& user : users) {
        std::cout << "Username：" << user->getName() << ", ID: " << user->getId() << std::endl;
    }
}

LibraryItem* Library::findItem(const std::string& title) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [&title](const LibraryItem* item) { return item->getTitle() == title; });
    return it != items.end() ? *it : nullptr;
}

User* Library::findUser(const std::string& name) const {
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const User* user) { return user->getName() == name; });
    return it != users.end() ? *it : nullptr;
}

void Library::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return;
    }

    file << items.size() << std::endl;
    for (const auto& item : items) {
        file << item->getType() << std::endl;
        file << item->getTitle() << std::endl;
        file << item->getId() << std::endl;
        file << item->isCheckedOut() << std::endl;

        if (item->getType() == "Book") {
            Book* book = dynamic_cast<Book*>(item);
            file << book->getAuthor() << std::endl;
            file << book->getPageCount() << std::endl;
        } else if (item->getType() == "DVD") {
            DVD* dvd = dynamic_cast<DVD*>(item);
            file << dvd->getDirector() << std::endl;
            file << dvd->getDuration() << std::endl;
        }
    }

    file << users.size() << std::endl;
    for (const auto& user : users) {
        file << user->getName() << std::endl;
        file << user->getId() << std::endl;
    }

    std::cout << "Library data saved to file: " << filename << std::endl;
}

void Library::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
        return;
    }

    for (auto item : items) delete item;
    items.clear();
    for (auto user : users) delete user;
    users.clear();

    int itemCount;
    file >> itemCount;
    file.ignore(); 
    for (int i = 0; i < itemCount; ++i) {
        std::string type, title, id;
        bool checkedOut;
        
        std::getline(file, type);
        std::getline(file, title);
        std::getline(file, id);
        file >> checkedOut;
        file.ignore(); 

        LibraryItem* item = nullptr;
        if (type == "Book") {
            std::string author;
            int pageCount;
            std::getline(file, author);
            file >> pageCount;
            file.ignore(); 
            item = new Book(title, id, author, pageCount);
        } else if (type == "DVD") {
            std::string director;
            int duration;
            std::getline(file, director);
            file >> duration;
            file.ignore();
            item = new DVD(title, id, director, duration);
        }

        if (item) {
            if (checkedOut) item->checkOut();
            items.push_back(item);
        }
    }

    int userCount;
    file >> userCount;
    file.ignore(); 
    for (int i = 0; i < userCount; ++i) {
        std::string name, id;
        std::getline(file, name);
        std::getline(file, id);
        users.push_back(new User(name, id));
    }

    std::cout << "Library data loaded from file: " << filename << std::endl;
}