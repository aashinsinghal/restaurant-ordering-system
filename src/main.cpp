#include <iostream>
#include <vector>
#include "Location.h"
#include "CustomerUI.h"
#include "StaffUI.h"
#include "UIUtils.h"

int main() {
    std::vector<Location*> locations = {
        new Location("Downtown"),
        new Location("Uptown"),
        new Location("Airport")
    };

    while (true) {
        std::cout << "\n=== Restaurant Ordering System ===\n";
        std::cout << "  1. Customer  — Place an Order\n";
        std::cout << "  2. Staff     — Manage Orders\n";
        std::cout << "  3. Exit\n";
        std::cout << "Choice: ";

        int choice = getValidInt(1, 3);
        switch (choice) {
            case 1: runCustomerFlow(locations); break;
            case 2: runStaffFlow(locations);    break;
            case 3:
                for (Location* loc : locations) delete loc;
                std::cout << "\nGoodbye!\n";
                return 0;
        }
    }
}
