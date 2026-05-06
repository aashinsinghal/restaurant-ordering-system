#include "Location.h"
#include "Entree.h"
#include "Drink.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Location::Location(const std::string& name) : name(name) {
    loadMenu();
}

Location::~Location() {
    for (MenuItem* item : menu)
        delete item;
    for (Order* order : activeOrders)
        delete order;
}

void Location::loadMenu() {
    if (name == "Airport") {
        menu.push_back(new Entree("Classic Burger",  12.99));
        menu.push_back(new Entree("Grilled Chicken", 14.99));
        menu.push_back(new Drink("Soda",              3.99));
    } else if (name == "Uptown") {
        menu.push_back(new Entree("Grilled Chicken", 13.49));
        menu.push_back(new Entree("Veggie Wrap",     11.49));
        menu.push_back(new Entree("Truffle Burger",  16.99));
        menu.push_back(new Drink("Soda",              2.99));
        menu.push_back(new Drink("Sparkling Water",   2.49));
    } else {
        menu.push_back(new Entree("Classic Burger",   10.99));
        menu.push_back(new Entree("Grilled Chicken",  13.49));
        menu.push_back(new Entree("BBQ Bacon Burger", 14.99));
        menu.push_back(new Drink("Soda",               2.99));
        menu.push_back(new Drink("Lemonade",           3.49));
    }
}

std::string Location::getName() const { return name; }
int Location::getMenuSize() const { return static_cast<int>(menu.size()); }

void Location::displayMenu() const {
    std::cout << "--- " << name << " Menu ---\n";
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << "  " << (i + 1) << ". "
                  << menu[i]->getName()
                  << " -- $" << menu[i]->getPrice() << "\n";
    }
}

MenuItem* Location::getMenuItem(int index) {
    if (index < 0 || static_cast<size_t>(index) >= menu.size())
        throw std::out_of_range("Menu index out of range.");
    return menu[index];
}

void Location::placeOrder(Order* order) {
    activeOrders.push_back(order);
}

int Location::getQueueDepth() const {
    int count = 0;
    for (const Order* order : activeOrders)
        if (order->getStatus() != OrderStatus::FULFILLED)
            ++count;
    return count;
}

int Location::estimatePickupMinutes() const {
    return getQueueDepth() * 5;
}

void Location::displayQueue() const {
    std::cout << "--- " << name << " Queue (" << activeOrders.size() << " order(s)) ---\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const Order* order : activeOrders) {
        std::cout << "  [" << order->getOrderID() << "]"
                  << "  Status: " << order->getStatusString()
                  << "  Total: $" << order->getTotal() << "\n";
    }
}

Order* Location::findOrder(const std::string& orderID) {
    for (Order* order : activeOrders)
        if (order->getOrderID() == orderID)
            return order;
    return nullptr;
}
