#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "GeoLocation.h"

class Order {
private:
    std::string orderId;
    std::vector<Item> items;
    GeoLocation deliveryLocation;

public:
    Order(const std::string& id) : orderId(id) {}

    void addItem(const Item& item);
    void setDeliveryLocation(double lat, double lon);
    
    // Getters
    std::string getId() const;
    const std::vector<Item>& getItems() const;
    GeoLocation getLocation() const;
};