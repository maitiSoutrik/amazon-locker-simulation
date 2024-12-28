
#pragma once
#include <string>

class ConsoleUI {
public:
    static void clearScreen();
    static void printHeader();
    static void printSuccess(const std::string& message);
    static void printError(const std::string& message);
    static void printWarning(const std::string& message);
    static void printMenu();
    static void printProcessing();
    static void printDivider();
};
