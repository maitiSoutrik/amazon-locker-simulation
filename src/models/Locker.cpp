
#include "models/Locker.h"

Locker::Locker(const std::string& id, LockerSize size, const std::string& location)
    : lockerId(id), lockerSize(size), locationId(location), 
      lockerState(LockerState::AVAILABLE), currentPackage(nullptr) {}

bool Locker::addPackage(Package* package) {
    if (lockerState != LockerState::AVAILABLE || !package) return false;
    currentPackage = package;
    lockerState = LockerState::BOOKED;
    return true;
}

bool Locker::removePackage() {
    if (lockerState != LockerState::BOOKED) return false;
    currentPackage = nullptr;
    lockerState = LockerState::AVAILABLE;
    return true;
}

bool Locker::isAvailable() const {
    return lockerState == LockerState::AVAILABLE;
}

std::string Locker::getId() const { return lockerId; }
LockerSize Locker::getSize() const { return lockerSize; }
std::string Locker::getLocationId() const { return locationId; }
LockerState Locker::getState() const { return lockerState; }
Package* Locker::getCurrentPackage() const { return currentPackage; }
