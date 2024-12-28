#pragma once
#include <string>
#include "Package.h"

enum class LockerSize { 
    EXTRA_SMALL,
    SMALL, 
    MEDIUM, 
    LARGE,
    EXTRA_LARGE,
    DOUBLE_EXTRA_LARGE 
};

enum class LockerState { 
    CLOSED,
    BOOKED,
    AVAILABLE 
};

class Locker {
private:
    std::string lockerId;
    LockerSize lockerSize;
    std::string locationId;
    LockerState lockerState;
    Package* currentPackage;

public:
    Locker(const std::string& id, LockerSize size, const std::string& location);
    
    bool addPackage(Package* package);
    bool removePackage();
    bool isAvailable() const;

    // Getters
    std::string getId() const;
    LockerSize getSize() const;
    std::string getLocationId() const;
    LockerState getState() const;
    Package* getCurrentPackage() const;
};