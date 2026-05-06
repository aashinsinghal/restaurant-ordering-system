#pragma once
#include <string>

class MenuItem {
protected:
    std::string name;
    double price;
    std::string category;

public:
    MenuItem(const std::string& name, double price, const std::string& category);
    virtual ~MenuItem() = default;

    virtual void displayOptions() = 0;
    virtual std::string getSummary() const;
    virtual MenuItem* clone() const = 0;

    std::string getName() const;
    double getPrice() const;
};
