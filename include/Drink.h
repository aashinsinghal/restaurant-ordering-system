#pragma once
#include "MenuItem.h"

class Drink : public MenuItem {
private:
    std::string size;

    double adjustedPrice() const;

public:
    Drink(const std::string& name, double basePrice);
    ~Drink() override = default;

    void displayOptions() override;
    std::string getSummary() const override;
    MenuItem* clone() const override;
    double getPrice() const;
};
