#include "Order.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <random>

std::string Order::generateID() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 9999);
    std::ostringstream oss;
    oss << "ORD-" << std::setfill('0') << std::setw(4) << dist(rng);
    return oss.str();
}

Order::Order(const std::string& locationName)
    : orderID(generateID()), status(OrderStatus::PENDING), locationName(locationName) {}

Order::~Order() {
    for (MenuItem* item : items)
        delete item;
}

void Order::addItem(MenuItem* item) {
    items.push_back(item);
}

void Order::setSpecialInstructions(const std::string& instructions) {
    specialInstructions = instructions;
}

void Order::advanceStatus() {
    switch (status) {
        case OrderStatus::PENDING:   status = OrderStatus::PREPARING; break;
        case OrderStatus::PREPARING: status = OrderStatus::READY;     break;
        case OrderStatus::READY:     status = OrderStatus::FULFILLED; break;
        case OrderStatus::FULFILLED:
            throw std::logic_error("Order " + orderID + " is already fulfilled.");
    }
}

std::string Order::getStatusString() const {
    switch (status) {
        case OrderStatus::PENDING:   return "Pending";
        case OrderStatus::PREPARING: return "Preparing";
        case OrderStatus::READY:     return "Ready";
        case OrderStatus::FULFILLED: return "Fulfilled";
    }
    return "Unknown";
}

OrderStatus Order::getStatus() const { return status; }
std::string Order::getOrderID() const { return orderID; }

double Order::getTotal() const {
    double total = 0.0;
    for (const MenuItem* item : items)
        total += item->getPrice();
    return total;
}

void Order::printReceipt() const {
    std::cout << "========================================\n";
    std::cout << "  RECEIPT\n";
    std::cout << "  Order ID : " << orderID << "\n";
    std::cout << "  Location : " << locationName << "\n";
    std::cout << "  Status   : " << getStatusString() << "\n";
    std::cout << "----------------------------------------\n";
    for (const MenuItem* item : items)
        std::cout << item->getSummary() << "\n";
    std::cout << "----------------------------------------\n";
    if (!specialInstructions.empty())
        std::cout << "  Note: " << specialInstructions << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  TOTAL    : $" << getTotal() << "\n";
    std::cout << "========================================\n";
}
