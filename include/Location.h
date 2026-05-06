#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"
#include "Order.h"

class Location {
private:
    std::string name;
    std::vector<MenuItem*> menu;
    std::vector<Order*> activeOrders;

    void loadMenu();

public:
    explicit Location(const std::string& name);
    ~Location();

    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

    std::string getName() const;
    int getMenuSize() const;
    void displayMenu() const;
    MenuItem* getMenuItem(int index);
    void placeOrder(Order* order);
    int getQueueDepth() const;
    int estimatePickupMinutes() const;
    void displayQueue() const;
    Order* findOrder(const std::string& orderID);
};
