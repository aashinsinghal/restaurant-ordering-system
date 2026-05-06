#include "Entree.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Entree::Entree(const std::string& name, double price)
    : MenuItem(name, price, "Entree"), temperature("Medium"), cheeseType("None") {}

void Entree::displayOptions() {
    std::cout << "\n--- Customize your " << name << " ---\n";

    std::cout << "Temperature:\n"
              << "  1. Well Done\n"
              << "  2. Medium\n"
              << "  3. Rare\n"
              << "Choice: ";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: temperature = "Well Done"; break;
        case 3: temperature = "Rare";      break;
        default: temperature = "Medium";   break;
    }

    std::cout << "Cheese:\n"
              << "  1. American\n"
              << "  2. Swiss\n"
              << "  3. None\n"
              << "Choice: ";
    std::cin >> choice;
    switch (choice) {
        case 1: cheeseType = "American"; break;
        case 2: cheeseType = "Swiss";    break;
        default: cheeseType = "None";    break;
    }
}

MenuItem* Entree::clone() const { return new Entree(*this); }

std::string Entree::getSummary() const {
    std::ostringstream oss;
    oss << MenuItem::getSummary()
        << "\n  Temperature: " << temperature
        << "\n  Cheese: "      << cheeseType;
    return oss.str();
}
