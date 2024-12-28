#include <iostream>
#include <memory>
#include <iomanip>
#include <algorithm>  // Added for std::all_of
#include "models/Locker.h"
#include "models/Package.h"
#include "models/Location.h"
#include "models/Notification.h"
#include "services/LockerService.h"
#include "services/OTPService.h"
#include "utils/ConsoleUI.h"
#include "utils/TimeUtils.h"

void initializeTestLockers(LockerService& service) {
    auto location = std::make_unique<LockerLocation>("LOC1", 37.7749, -122.4194); // San Francisco coordinates

    // Add extra small lockers (up to 500 cubic cm)
    for (int i = 1; i <= 2; i++) {
        location->addLocker(new Locker("XS" + std::to_string(i), LockerSize::EXTRA_SMALL, "LOC1"));
    }

    // Add small lockers (501-1000 cubic cm)
    for (int i = 1; i <= 3; i++) {
        location->addLocker(new Locker("S" + std::to_string(i), LockerSize::SMALL, "LOC1"));
    }

    // Add medium lockers (1001-2500 cubic cm)
    for (int i = 1; i <= 3; i++) {
        location->addLocker(new Locker("M" + std::to_string(i), LockerSize::MEDIUM, "LOC1"));
    }

    // Add large lockers (2501-5000 cubic cm)
    for (int i = 1; i <= 2; i++) {
        location->addLocker(new Locker("L" + std::to_string(i), LockerSize::LARGE, "LOC1"));
    }

    // Add extra large lockers (5001-10000 cubic cm)
    location->addLocker(new Locker("XL1", LockerSize::EXTRA_LARGE, "LOC1"));

    // Add double extra large lockers (10001-20000 cubic cm)
    location->addLocker(new Locker("XXL1", LockerSize::DOUBLE_EXTRA_LARGE, "LOC1"));

    service.addLocation(std::move(location));
}

void displayPackageSizeGuide() {
    std::cout << "\033[1;36m\nPackage Size Guide:\033[0m\n";
    std::cout << "┌─────────────────────┬───────────────────────┐\n";
    std::cout << "│ Locker Type         │ Size Range (cubic cm) │\n";
    std::cout << "├─────────────────────┼───────────────────────┤\n";
    std::cout << "│ Extra Small         │ Up to 500            │\n";
    std::cout << "│ Small               │ 501-1000             │\n";
    std::cout << "│ Medium              │ 1001-2500            │\n";
    std::cout << "│ Large               │ 2501-5000            │\n";
    std::cout << "│ Extra Large         │ 5001-10000           │\n";
    std::cout << "│ Double Extra Large  │ 10001-20000          │\n";
    std::cout << "└─────────────────────┴───────────────────────┘\n";
    std::cout << "\nNote: Please enter the package size in cubic centimeters (length × width × height)\n";
    std::cout << "Maximum package size allowed: 20000 cubic cm\n\n";
}

void displayLocationStatus(LockerService& service, LockerLocation* location) {
    if (location) {
        int availableLockers = service.getAvailableLockerCount(location);
        std::cout << "\033[1;33m\nLocation Status:\033[0m\n";
        std::cout << "┌─────────────────────────────────┐\n";
        std::cout << "│ Location ID: " << std::setw(19) << location->getId() << "│\n";
        std::cout << "│ Available Lockers: " << std::setw(14) << availableLockers << "│\n";
        std::cout << "└─────────────────────────────────┘\n";

        auto sizeDistribution = service.getLockerSizeDistribution(location);
        std::cout << "\n\033[1;33mLocker Availability by Size:\033[0m\n";
        std::cout << "┌─────────────────────┬───────────┐\n";
        std::cout << "│ Size                │ Available │\n";
        std::cout << "├─────────────────────┼───────────┤\n";
        std::cout << "│ Extra Small         │ " << std::setw(9) << sizeDistribution[LockerSize::EXTRA_SMALL] << " │\n";
        std::cout << "│ Small               │ " << std::setw(9) << sizeDistribution[LockerSize::SMALL] << " │\n";
        std::cout << "│ Medium              │ " << std::setw(9) << sizeDistribution[LockerSize::MEDIUM] << " │\n";
        std::cout << "│ Large               │ " << std::setw(9) << sizeDistribution[LockerSize::LARGE] << " │\n";
        std::cout << "│ Extra Large         │ " << std::setw(9) << sizeDistribution[LockerSize::EXTRA_LARGE] << " │\n";
        std::cout << "│ Double Extra Large  │ " << std::setw(9) << sizeDistribution[LockerSize::DOUBLE_EXTRA_LARGE] << " │\n";
        std::cout << "└─────────────────────┴───────────┘\n";

        if (availableLockers == 0) {
            ConsoleUI::printError("This location is currently full!");
        }
    }
}

void displayPackagePickupTimeRemaining(const LockerPackage* package) {
    if (package) {
        auto remainingHours = package->getRemainingPickupTime();
        int days = remainingHours / 24;
        int hours = remainingHours % 24;

        std::cout << "\nTime Remaining for Pickup:\n";
        if (days > 0) {
            std::cout << days << " day(s) ";
        }
        std::cout << hours << " hour(s)\n";

        if (remainingHours < 24) {
            std::cout << "\nWarning: Package pickup deadline approaching!\n";
        }
    }
}

void displayPackageDetails(const LockerPackage* package, const Locker* locker) {
    if (package && locker) {
        std::cout << "\033[1;32m\nPackage Details:\033[0m\n";
        std::cout << "┌─────────────────────────────────────┐\n";
        std::cout << "│ Package ID: " << std::setw(23) << package->getId() << " │\n";
        std::cout << "│ Order ID: " << std::setw(25) << package->getOrderId() << " │\n";
        std::cout << "│ Locker ID: " << std::setw(24) << locker->getId() << " │\n";
        std::cout << "│ Location: " << std::setw(25) << locker->getLocationId() << " │\n";
        std::cout << "│ Size: " << std::setw(29) << static_cast<int>(locker->getSize()) << " │\n";
        std::cout << "└─────────────────────────────────────┘\n";

        auto remainingHours = package->getRemainingPickupTime();
        int days = remainingHours / 24;
        int hours = remainingHours % 24;

        std::cout << "\033[1;36m\nPickup Time Remaining:\033[0m\n";
        std::cout << "┌─────────────────────────────────────┐\n";
        if (days > 0) {
            std::cout << "│ " << days << " day(s) and " << hours << " hour(s) remaining      │\n";
        } else {
            std::cout << "│ " << hours << " hour(s) remaining                  │\n";
        }
        std::cout << "└─────────────────────────────────────┘\n";

        if (remainingHours < 24) {
            ConsoleUI::printError("Warning: Package pickup deadline approaching!");
        }
    }
}

void processPackagePickup(LockerService& service, const std::string& lockerId, const std::string& code) {
    auto location = service.findNearestLocation(GeoLocation());
    if (!location) {
        ConsoleUI::printError("Location not found!");
        return;
    }

    Locker* locker = nullptr;
    for (auto& l : location->getLockers()) {
        if (l->getId() == lockerId) {
            locker = l;
            break;
        }
    }

    if (!locker) {
        ConsoleUI::printError("Locker not found!");
        return;
    }

    auto package = dynamic_cast<LockerPackage*>(locker->getCurrentPackage());
    if (!package) {
        ConsoleUI::printError("No package in this locker!");
        return;
    }

    if (package->verifyCode(code)) {
        displayPackageDetails(package, locker);
        std::cout << "\nVerifying access code...\n";
        if (locker->removePackage()) {
            ConsoleUI::printSuccess("Package retrieved successfully!");
            delete package;
        } else {
            ConsoleUI::printError("Failed to retrieve package!");
        }
    } else {
        ConsoleUI::printError("Invalid or expired access code!");
        std::cout << "Note: Access codes expire after 3 days from delivery.\n";
    }
}

void processReturnRequest(const std::string& orderId, LockerService& service) {
    auto location = service.findNearestLocation(GeoLocation());
    if (!location) {
        ConsoleUI::printError("No locker locations available!");
        return;
    }

    // Find suitable locker for return
    auto locker = service.findAvailableLocker(location, 1000.0); // Default to medium size for returns
    if (!locker) {
        ConsoleUI::printError("No available lockers for return at this location!");
        std::cout << "Please try a different location or come back later.\n";
        return;
    }

    // Generate return code
    std::string returnCode = OTPService::generateOTP();

    // Create return package
    auto returnPackage = new LockerPackage(
        "RET" + orderId,
        1000.0, // Default size for returns
        orderId,
        locker->getId(),
        returnCode
    );

    // Place return package in locker
    if (locker->addPackage(returnPackage)) {
        ConsoleUI::printSuccess("Return request processed successfully!");
        std::cout << "\033[1;36m\nReturn Instructions:\033[0m\n";
        std::cout << "┌────────────────────────────────────────┐\n";
        std::cout << "│ Please place your return in:           │\n";
        std::cout << "│ Location: " << std::setw(25) << location->getId() << " │\n";
        std::cout << "│ Locker: " << std::setw(28) << locker->getId() << " │\n";
        std::cout << "│ Access Code: " << std::setw(23) << returnCode << " │\n";
        std::cout << "└────────────────────────────────────────┘\n";
        std::cout << "\nThis code will expire in 24 hours.\n";

        // Send return confirmation notification
        Notification notification(
            "CUST123", // In a real system, this would be the actual customer ID
            orderId,
            locker->getId(),
            returnCode
        );
        notification.send();

        displayLocationStatus(service, location);
    } else {
        ConsoleUI::printError("Failed to process return request!");
        delete returnPackage;
    }
}

int main() {
    try {
        // Initialize services
        LockerService lockerService;
        initializeTestLockers(lockerService);
        ConsoleUI::printSuccess("Locker system initialized successfully!");

        // Main program loop
        while (true) {
            ConsoleUI::clearScreen();
            ConsoleUI::printHeader();
            ConsoleUI::printMenu();

            std::string input;
            std::getline(std::cin, input);
            int choice;

            try {
                choice = std::stoi(input);
            } catch (...) {
                ConsoleUI::printError("Invalid input! Please enter a number.");
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                continue;
            }

            switch (choice) {
                case 1: {
                    // Place Package
                    std::string orderId;
                    double packageSize;

                    std::cout << "Enter Order ID: ";
                    std::getline(std::cin, orderId);

                    if (orderId.empty()) {
                        ConsoleUI::printError("Order ID cannot be empty!");
                        break;
                    }

                    // Find nearest location first
                    auto location = lockerService.findNearestLocation(GeoLocation());
                    if (!location) {
                        ConsoleUI::printError("No locker locations available!");
                        break;
                    }

                    displayLocationStatus(lockerService, location);
                    displayPackageSizeGuide();

                    std::cout << "Enter Package Size (in cubic cm): ";
                    std::string sizeInput;
                    std::getline(std::cin, sizeInput);

                    try {
                        packageSize = std::stod(sizeInput);
                        if (packageSize <= 0) {
                            throw std::invalid_argument("Size must be positive");
                        }
                        if (packageSize > lockerService.getMaxPackageSize()) {
                            ConsoleUI::printError("Package size exceeds maximum allowed size!");
                            break;
                        }
                    } catch (...) {
                        ConsoleUI::printError("Invalid package size!");
                        break;
                    }

                    // Find available locker
                    auto locker = lockerService.findAvailableLocker(location, packageSize);
                    if (!locker) {
                        ConsoleUI::printError("No suitable locker available for this package size!");
                        std::cout << "Please try a different location or come back later.\n";
                        break;
                    }

                    // Generate OTP and create package
                    std::string otp = OTPService::generateOTP();
                    auto package = new LockerPackage(
                        "PKG" + orderId, packageSize, orderId,
                        locker->getId(), otp
                    );

                    // Place package in locker
                    if (locker->addPackage(package)) {
                        ConsoleUI::printSuccess("Package placed successfully!");
                        displayPackageDetails(package, locker);

                        // Send notification
                        Notification notification("CUST123", orderId, locker->getId(), otp);
                        notification.send();

                        // Display updated location status
                        displayLocationStatus(lockerService, location);
                    } else {
                        ConsoleUI::printError("Failed to place package!");
                        delete package;
                    }
                    break;
                }
                case 2: {
                    // Pickup Package
                    std::string lockerId, code;

                    std::cout << "Enter Locker ID: ";
                    std::getline(std::cin, lockerId);

                    if (lockerId.empty()) {
                        ConsoleUI::printError("Locker ID cannot be empty!");
                        break;
                    }

                    std::cout << "Enter Access Code: ";
                    std::getline(std::cin, code);

                    if (code.empty()) {
                        ConsoleUI::printError("Access code cannot be empty!");
                        break;
                    }

                    processPackagePickup(lockerService, lockerId, code);
                    break;
                }
                case 3: {
                    // Return Package
                    std::string orderId;
                    std::cout << "Enter Order ID for return: ";
                    std::getline(std::cin, orderId);

                    if (orderId.empty()) {
                        ConsoleUI::printError("Order ID cannot be empty!");
                        break;
                    }

                    // Validate order ID format using std::all_of with proper header
                    if (orderId.length() < 3 || !std::all_of(orderId.begin(), orderId.end(),
                        [](char c) { return std::isalnum(c); })) {
                        ConsoleUI::printError("Invalid Order ID format!");
                        std::cout << "Order ID must be at least 3 characters long and contain only letters and numbers.\n";
                        break;
                    }

                    processReturnRequest(orderId, lockerService);
                    break;
                }
                case 4:
                    ConsoleUI::printSuccess("Thank you for using Amazon Locker System!");
                    return 0;
                default:
                    ConsoleUI::printError("Invalid choice! Please select 1-4.");
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    } catch (const std::exception& e) {
        ConsoleUI::printError("An unexpected error occurred: " + std::string(e.what()));
        return 1;
    }

    return 0;
}