#pragma once
#include <string>
#include <vector>
#include "MenuItem.h"

enum class OrderStatus { PENDING, PREPARING, READY, FULFILLED };

class Order {
private:
    std::string orderID;
    std::vector<MenuItem*> items;
    OrderStatus status;
    std::string specialInstructions;
    std::string locationName;

    static std::string generateID();

public:
    explicit Order(const std::string& locationName);
    ~Order();

    Order(const Order&) = delete;
    Order& operator=(const Order&) = delete;

    void addItem(MenuItem* item);
    void setSpecialInstructions(const std::string& instructions);
    void advanceStatus();

    OrderStatus getStatus() const;
    std::string getStatusString() const;
    std::string getOrderID() const;
    double getTotal() const;
    void printReceipt() const;
};
