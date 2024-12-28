
#pragma once
#include <string>
#include <chrono>

// Forward declaration to avoid circular dependency
class Locker;

class Package {
protected:
    std::string packageId;
    double packageSize;
    std::string orderId;

public:
    Package(const std::string& id, double size, const std::string& order);
    virtual ~Package() = default;

    std::string getId() const;
    double getSize() const;
    std::string getOrderId() const;
};

class LockerPackage : public Package {
private:
    std::string lockerId;
    std::string code;
    int codeValidDays;
    std::chrono::system_clock::time_point packageDeliveryTime;

public:
    LockerPackage(const std::string& id, double size, const std::string& order,
                  const std::string& locker, const std::string& accessCode);

    std::string getLockerId() const;
    bool isValidCode(const std::string& inputCode) const;
    bool verifyCode(const std::string& inputCode) const;
    int getRemainingPickupTime() const;
};
