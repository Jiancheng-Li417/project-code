#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "Library.h"
#include "Book.h"
#include "DVD.h"
#include "User.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidId(const std::string& id) {
    return !id.empty() && id.length() <= 10 && std::isalnum(id[0]);
}

bool isValidName(const std::string& name) {
    return !name.empty() && name.length() <= 50;
}

int getIntInput(const std::string& prompt, int min, int max) {
    int input;
    while (true) {
        std::cout << prompt;
        if (std::cin >> input && input >= min && input <= max) {
            clearInputBuffer();
            return input;
        }
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
        clearInputBuffer();
    }
}

std::string getStringInput(const std::string& prompt, bool (*validator)(const std::string&)) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validator(input)) {
            return input;
        }
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

void displayMenu() {
    std::cout << "\n=== Library Management System ===" << std::endl;
    std::cout << "1. Add new book" << std::endl;
    std::cout << "2. Add new DVD" << std::endl;
    std::cout << "3. Add new user" << std::endl;
    std::cout << "4. Display all items" << std::endl;
    std::cout << "5. Display all users" << std::endl;
    std::cout << "6. Borrow item" << std::endl;
    std::cout << "7. Return item" << std::endl;
    std::cout << "8. Find item" << std::endl;
    std::cout << "9. Find user" << std::endl;
    std::cout << "10. Save data to file" << std::endl;
    std::cout << "11. Load data from file" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Please choose an operation: ";
}

void addBook(Library& library) {
    std::string title = getStringInput("Enter book title: ", isValidName);
    std::string id = getStringInput("Enter ID: ", isValidId);
    std::string author = getStringInput("Enter author: ", isValidName);
    int pageCount = getIntInput("Enter page count: ", 1, 10000);

    Book* book = new Book(title, id, author, pageCount);
    library.addItem(book);
    std::cout << "New book《" << title << "》has been successfully added." << std::endl;
}

void addDVD(Library& library) {
    std::string title = getStringInput("Enter DVD title: ", isValidName);
    std::string id = getStringInput("Enter ID: ", isValidId);
    std::string director = getStringInput("Enter director: ", isValidName);
    int duration = getIntInput("Enter duration (minutes): ", 1, 1000);

    DVD* dvd = new DVD(title, id, director, duration);
    library.addItem(dvd);
    std::cout << "New DVD《" << title << "》has been successfully added." << std::endl;
}

void addUser(Library& library) {
    std::string name = getStringInput("Enter username: ", isValidName);
    std::string id = getStringInput("Enter user ID: ", isValidId);

    User* user = new User(name, id);
    library.addUser(user);
    std::cout << "New user " << name << " has been successfully added." << std::endl;
}

void borrowItem(Library& library) {
    std::string userName = getStringInput("Enter username: ", isValidName);
    std::string itemTitle = getStringInput("Enter the title of the item to borrow: ", isValidName);

    User* user = library.findUser(userName);
    LibraryItem* item = library.findItem(itemTitle);

    if (user && item) {
        if (item->isCheckedOut()) {
            std::cout << "Sorry,《" << itemTitle << "》is already checked out." << std::endl;
        } else {
            user->borrowItem(item);
            std::cout << "《" << itemTitle << "》has been successfully borrowed by " << userName << "." << std::endl;
        }
    } else {
        if (!user) std::cout << "User " << userName << " not found." << std::endl;
        if (!item) std::cout << "Item《" << itemTitle << "》 not found." << std::endl;
    }
}

void returnItem(Library& library) {
    std::string userName, itemTitle;

    std::cout << "Enter username: ";
    std::getline(std::cin, userName);
    std::cout << "Enter the title of the item to return: ";
    std::getline(std::cin, itemTitle);

    User* user = library.findUser(userName);
    LibraryItem* item = library.findItem(itemTitle);

    if (user && item) {
        if (user->returnItem(item)) {
            std::cout << "《" << itemTitle << "》has been successfully returned." << std::endl;
        } else {
            std::cout << "Return failed. " << userName << " may not have borrowed《" << itemTitle << "》。" << std::endl;
        }
    } else {
        if (!user) std::cout << "User " << userName << " not found." << std::endl;
        if (!item) std::cout << "Item《" << itemTitle << "》not found." << std::endl;
    }
}

void findItem(const Library& library) {
    std::string title = getStringInput("Enter the title of the item to find: ", isValidName);

    LibraryItem* item = library.findItem(title);
    if (item) {
        std::cout << "Item found:" << std::endl;
        item->displayInfo();
    } else {
        std::cout << "Item《" << title << "》not found." << std::endl;
    }
}

void findUser(const Library& library) {
    std::string name = getStringInput("Enter the username to find: ", isValidName);

    User* user = library.findUser(name);
    if (user) {
        std::cout << "User found:" << std::endl;
        std::cout << "Username: " << user->getName() << ", ID: " << user->getId() << std::endl;
        user->displayBorrowedItems();
    } else {
        std::cout << "User " << name << " not found." << std::endl;
    }
}

int main() {
    Library library;
    int choice;

    do {
        displayMenu();
        choice = getIntInput("", 0, 11);

        switch (choice) {
            case 1: addBook(library); break;
            case 2: addDVD(library); break;
            case 3: addUser(library); break;
            case 4: library.displayAllItems(); break;
            case 5: library.displayAllUsers(); break;
            case 6: borrowItem(library); break;
            case 7: returnItem(library); break;
            case 8: findItem(library); break;
            case 9: findUser(library); break;
            case 10:
                library.saveToFile("library_data.txt");
                std::cout << "Data has been successfully saved to file." << std::endl;
                break;
            case 11:
                library.loadFromFile("library_data.txt");
                std::cout << "Data has been successfully loaded from file." << std::endl;
                break;
            case 0:
                std::cout << "Thank you for using the Library Management System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}