
#include "models/Package.h"

Package::Package(const std::string& id, double size, const std::string& order)
    : packageId(id), packageSize(size), orderId(order) {}

std::string Package::getId() const { return packageId; }
double Package::getSize() const { return packageSize; }
std::string Package::getOrderId() const { return orderId; }

LockerPackage::LockerPackage(const std::string& id, double size, const std::string& order,
                const std::string& locker, const std::string& accessCode)
    : Package(id, size, order), lockerId(locker), code(accessCode),
        codeValidDays(3), packageDeliveryTime(std::chrono::system_clock::now()) {}

std::string LockerPackage::getLockerId() const { return lockerId; }

bool LockerPackage::isValidCode(const std::string& inputCode) const {
    return code == inputCode;
}

bool LockerPackage::verifyCode(const std::string& inputCode) const {
    if (!isValidCode(inputCode)) return false;
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - packageDeliveryTime);
    return duration.count() < (codeValidDays * 24);
}

int LockerPackage::getRemainingPickupTime() const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - packageDeliveryTime);
    int remainingHours = (codeValidDays * 24) - duration.count();
    return remainingHours > 0 ? remainingHours : 0;
}
