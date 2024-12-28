
#include "services/LockerService.h"
#include <limits>

LockerLocation* LockerService::findNearestLocation(const GeoLocation& customerLocation) {
    if (locations.empty()) return nullptr;

    LockerLocation* nearest = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (const auto& location : locations) {
        double distance = location->distanceTo(customerLocation);
        if (distance < minDistance) {
            minDistance = distance;
            nearest = location.get();
        }
    }
    return nearest;
}

Locker* LockerService::findAvailableLocker(LockerLocation* location, double packageSize) {
    if (!location) return nullptr;
    if (packageSize <= 0 || packageSize > MAX_PACKAGE_SIZE) return nullptr;

    LockerSize requiredSize;
    if (packageSize <= 500) requiredSize = LockerSize::EXTRA_SMALL;
    else if (packageSize <= 1000) requiredSize = LockerSize::SMALL;
    else if (packageSize <= 2500) requiredSize = LockerSize::MEDIUM;
    else if (packageSize <= 5000) requiredSize = LockerSize::LARGE;
    else if (packageSize <= 10000) requiredSize = LockerSize::EXTRA_LARGE;
    else requiredSize = LockerSize::DOUBLE_EXTRA_LARGE;

    for (auto& locker : location->getLockers()) {
        if (locker->getSize() == requiredSize && locker->getState() == LockerState::AVAILABLE) {
            return locker;
        }
    }

    for (auto& locker : location->getLockers()) {
        if (static_cast<int>(locker->getSize()) > static_cast<int>(requiredSize) && 
            locker->getState() == LockerState::AVAILABLE) {
            return locker;
        }
    }

    return nullptr;
}

std::map<LockerSize, int> LockerService::getLockerSizeDistribution(LockerLocation* location) {
    std::map<LockerSize, int> distribution = {
        {LockerSize::EXTRA_SMALL, 0},
        {LockerSize::SMALL, 0},
        {LockerSize::MEDIUM, 0},
        {LockerSize::LARGE, 0},
        {LockerSize::EXTRA_LARGE, 0},
        {LockerSize::DOUBLE_EXTRA_LARGE, 0}
    };

    if (!location) return distribution;

    for (auto& locker : location->getLockers()) {
        if (locker->getState() == LockerState::AVAILABLE) {
            distribution[locker->getSize()]++;
        }
    }
    return distribution;
}

void LockerService::addLocation(std::unique_ptr<LockerLocation> location) {
    locations.push_back(std::move(location));
}

int LockerService::getAvailableLockerCount(LockerLocation* location) {
    if (!location) return 0;
    int count = 0;
    for (auto& locker : location->getLockers()) {
        if (locker->getState() == LockerState::AVAILABLE) {
            count++;
        }
    }
    return count;
}

double LockerService::getMaxPackageSize() const {
    return MAX_PACKAGE_SIZE;
}
