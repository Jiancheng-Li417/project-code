#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h"


class DVD : public LibraryItem {
private:
    std::string director;   
    int duration;           
public:
    
    DVD(const std::string& title, const std::string& id, const std::string& director, int duration);

    void displayInfo() const override;

    std::string getType() const override;

    std::string getDirector() const;

    int getDuration() const;

    void setDirector(const std::string& newDirector);

    void setDuration(int newDuration);
};

#endif 