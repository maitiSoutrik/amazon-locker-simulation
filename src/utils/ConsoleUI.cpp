
#include "utils/ConsoleUI.h"
#include <iostream>

void ConsoleUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        std::cout << "\033[2J\033[1;1H";
    #endif
}

void ConsoleUI::printHeader() {
    std::cout << "\033[1;34m============================\033[0m\n";
    std::cout << "\033[1;32mAmazon Locker System\033[0m\n";
    std::cout << "\033[1;34m============================\033[0m\n\n";
}

void ConsoleUI::printSuccess(const std::string& message) {
    std::cout << "\033[1;32m✓ " << message << "\033[0m\n";
}

void ConsoleUI::printError(const std::string& message) {
    std::cout << "\033[1;31m✗ " << message << "\033[0m\n";
}

void ConsoleUI::printWarning(const std::string& message) {
    std::cout << "\033[1;33m! " << message << "\033[0m\n";
}

void ConsoleUI::printMenu() {
    std::cout << "\n1. Place Package\n";
    std::cout << "2. Pickup Package\n";
    std::cout << "3. Return Package\n";
    std::cout << "4. Exit\n";
    std::cout << "\nChoice: ";
}

void ConsoleUI::printProcessing() {
    std::cout << "\033[1;36mProcessing...\033[0m\n";
}

void ConsoleUI::printDivider() {
    std::cout << "\033[1;34m----------------------------\033[0m\n";
}
