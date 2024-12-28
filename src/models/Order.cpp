
#include "models/Order.h"

void Order::addItem(const Item& item) {
    items.push_back(item);
}

void Order::setDeliveryLocation(double lat, double lon) {
    deliveryLocation = GeoLocation(lat, lon);
}

std::string Order::getId() const {
    return orderId;
}

const std::vector<Item>& Order::getItems() const {
    return items;
}

GeoLocation Order::getLocation() const {
    return deliveryLocation;
}
