#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string author; 
    int pageCount;      

public:
    
    Book(const std::string& title, const std::string& id, const std::string& author, int pageCount);

    void displayInfo() const override;

    std::string getType() const override;

    std::string getAuthor() const;

    int getPageCount() const;

    void setAuthor(const std::string& newAuthor);

    void setPageCount(int newPageCount);
};

#endif 