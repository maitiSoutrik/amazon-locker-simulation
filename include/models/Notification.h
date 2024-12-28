#pragma once
#include <string>
#include <iostream>
#include "../utils/TimeUtils.h"

class Notification {
private:
    std::string customerId;
    std::string orderId;
    std::string lockerId;
    std::string code;

public:
    Notification(const std::string& customer, const std::string& order,
                const std::string& locker, const std::string& accessCode)
        : customerId(customer), orderId(order), lockerId(locker), code(accessCode) {}

    void send() const;
};