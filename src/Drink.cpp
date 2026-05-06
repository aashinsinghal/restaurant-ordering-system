#include "Drink.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Drink::Drink(const std::string& name, double basePrice)
    : MenuItem(name, basePrice, "Drink"), size("Medium") {}

double Drink::adjustedPrice() const {
    if (size == "Small")  return price - 0.50;
    if (size == "Large")  return price + 0.50;
    return price;
}

void Drink::displayOptions() {
    std::cout << "\n--- Customize your " << name << " ---\n";
    std::cout << "Size:\n"
              << "  1. Small  (-$0.50)\n"
              << "  2. Medium (base price)\n"
              << "  3. Large  (+$0.50)\n"
              << "Choice: ";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: size = "Small"; break;
        case 3: size = "Large"; break;
        default: size = "Medium"; break;
    }
}

std::string Drink::getSummary() const {
    std::ostringstream oss;
    oss << "[" << category << "] " << name << " (" << size << ")"
        << " — $" << std::fixed << std::setprecision(2) << adjustedPrice();
    return oss.str();
}

MenuItem* Drink::clone() const { return new Drink(*this); }

double Drink::getPrice() const {
    return adjustedPrice();
}
