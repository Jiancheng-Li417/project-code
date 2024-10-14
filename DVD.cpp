#include "DVD.h"
#include <iostream>

DVD::DVD(const std::string& title, const std::string& id, const std::string& director, int duration)
    : LibraryItem(title, id), director(director), duration(duration) {}

void DVD::displayInfo() const {
    std::cout << "DVD: " << title << " (ID: " << id << ")" << std::endl;
    std::cout << "Director: " << director << std::endl;
    std::cout << "Duration: " << duration << " minutes" << std::endl;
    std::cout << "Status: " << (checkedOut ? "Checked Out" : "Available") << std::endl;
}

std::string DVD::getType() const {
    return "DVD";
}

std::string DVD::getDirector() const {
    return director;
}

int DVD::getDuration() const {
    return duration;
}

void DVD::setDirector(const std::string& newDirector) {
    director = newDirector;
    std::cout << "DVD director updated to: " << director << std::endl;
}

void DVD::setDuration(int newDuration) {
    if (newDuration > 0) {
        duration = newDuration;
        std::cout << "DVD duration updated to: " << duration << " minutes" << std::endl;
    } else {
        std::cout << "Error: Duration must be a positive number." << std::endl;
    }
}