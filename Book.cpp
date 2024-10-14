#include "Book.h"
#include <iostream>

Book::Book(const std::string& title, const std::string& id, const std::string& author, int pageCount)
    : LibraryItem(title, id), author(author), pageCount(pageCount) {}

void Book::displayInfo() const {
    std::cout << "Book: " << title << " (ID: " << id << ")" << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Page Count: " << pageCount << std::endl;
    std::cout << "Status: " << (checkedOut ? "Checked Out" : "Available") << std::endl;
}

std::string Book::getType() const {
    return "Book";
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getPageCount() const {
    return pageCount;
}

void Book::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
    std::cout << "Book author updated to: " << author << std::endl;
}

void Book::setPageCount(int newPageCount) {
    if (newPageCount > 0) {
        pageCount = newPageCount;
        std::cout << "Book page count updated to: " << pageCount << std::endl;
    } else {
        std::cout << "Error: Page count must be a positive number." << std::endl;
    }
}