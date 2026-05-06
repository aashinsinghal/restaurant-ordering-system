#include "MenuItem.h"
#include <sstream>
#include <iomanip>

MenuItem::MenuItem(const std::string& name, double price, const std::string& category)
    : name(name), price(price), category(category) {}

std::string MenuItem::getSummary() const {
    std::ostringstream oss;
    oss << "[" << category << "] " << name
        << " — $" << std::fixed << std::setprecision(2) << price;
    return oss.str();
}

std::string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }
