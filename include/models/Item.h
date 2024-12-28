#pragma once
#include <string>

class Item {
private:
    std::string itemId;
    int quantity;

public:
    Item(const std::string& id, int qty = 1)
        : itemId(id), quantity(qty) {}

    // Getters
    std::string getId() const;
    int getQuantity() const;

    // Setters
    void setQuantity(int qty);
};
