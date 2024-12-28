
#include "models/Item.h"

std::string Item::getId() const { 
    return itemId; 
}

int Item::getQuantity() const { 
    return quantity; 
}

void Item::setQuantity(int qty) { 
    quantity = qty; 
}
