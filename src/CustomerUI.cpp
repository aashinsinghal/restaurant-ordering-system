#include "CustomerUI.h"
#include "UIUtils.h"
#include "Order.h"
#include <iostream>
#include <iomanip>

void runCustomerFlow(std::vector<Location*>& locations) {
    std::cout << "\nSelect a location:\n";
    for (size_t i = 0; i < locations.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << locations[i]->getName()
                  << "  (queue: " << locations[i]->getQueueDepth()
                  << " order(s), ~" << locations[i]->estimatePickupMinutes()
                  << " min wait)\n";
    }
    std::cout << "Choice: ";
    int locChoice = getValidInt(1, static_cast<int>(locations.size()));
    Location* location = locations[locChoice - 1];

    std::vector<MenuItem*> cart;

    while (true) {
        std::cout << "\n";
        location->displayMenu();
        std::cout << "  0. Done -- proceed to checkout\n";
        std::cout << "Add item (0 to checkout): ";

        int itemChoice = getValidInt(0, location->getMenuSize());
        if (itemChoice == 0) break;

        MenuItem* item = location->getMenuItem(itemChoice - 1)->clone();
        item->displayOptions();
        cart.push_back(item);

        std::cout << "\nAdded: " << item->getName() << "\n";
    }

    if (cart.empty()) {
        std::cout << "\nNo items selected. Returning to main menu.\n";
        return;
    }

    std::cout << "\nAny special instructions? (press Enter to skip): ";
    std::string instructions;
    std::getline(std::cin, instructions);

    Order* order = new Order(location->getName());
    for (MenuItem* item : cart)
        order->addItem(item);
    if (!instructions.empty())
        order->setSpecialInstructions(instructions);

    location->placeOrder(order);

    std::cout << "\n";
    order->printReceipt();
    std::cout << "\nEstimated pickup: " << location->estimatePickupMinutes()
              << " minute(s)\n";
    std::cout << "Show this Order ID at the counter: "
              << order->getOrderID() << "\n" << std::flush;
}
