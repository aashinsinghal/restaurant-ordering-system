#pragma once
#include "MenuItem.h"

class Entree : public MenuItem {
private:
    std::string temperature;
    std::string cheeseType;

public:
    Entree(const std::string& name, double price);
    ~Entree() override = default;

    void displayOptions() override;
    std::string getSummary() const override;
    MenuItem* clone() const override;
};
