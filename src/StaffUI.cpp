#include "StaffUI.h"
#include "UIUtils.h"
#include "Order.h"
#include <iostream>
#include <stdexcept>

void runStaffFlow(std::vector<Location*>& locations) {
    std::cout << "\nStaff access only.\n";
    std::cout << "Password (hint: password): ";
    std::string attempt;
    std::cin >> attempt;
    std::cin.ignore();
    if (attempt != "password") {
        std::cout << "Incorrect password.\n";
        return;
    }

    std::cout << "\nSelect a location to manage:\n";
    for (size_t i = 0; i < locations.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << locations[i]->getName()
                  << "  (" << locations[i]->getQueueDepth() << " active order(s))\n";
    }
    std::cout << "Choice: ";
    int locChoice = getValidInt(1, static_cast<int>(locations.size()));
    Location* location = locations[locChoice - 1];

    while (true) {
        std::cout << "\n";
        location->displayQueue();

        if (location->getQueueDepth() == 0) {
            std::cout << "No active orders.\n";
        }

        std::cout << "Enter Order ID to update status (or 0 to go back): ";
        std::string input;
        if (!(std::cin >> input)) break;
        std::cin.ignore();

        if (input == "0") break;

        Order* order = location->findOrder(input);
        if (!order) {
            std::cout << "Order ID not found.\n";
            continue;
        }

        std::cout << "Current status: " << order->getStatusString() << "\n";
        try {
            order->advanceStatus();
            std::cout << "New status: " << order->getStatusString() << "\n";
        } catch (const std::logic_error& e) {
            std::cout << "Cannot advance: " << e.what() << "\n";
        }
    }
}
