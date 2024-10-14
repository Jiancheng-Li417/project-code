#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>


class LibraryItem {
protected:
    std::string title;  
    std::string id;     
    bool checkedOut;    

public:

    LibraryItem(const std::string& title, const std::string& id);
    virtual ~LibraryItem() = default;

    virtual void displayInfo() const = 0;

    virtual std::string getType() const = 0;

    void checkOut();

    void checkIn();

    bool isCheckedOut() const;

    std::string getTitle() const;

    std::string getId() const;
};

#endif 