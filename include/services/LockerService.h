
#pragma once
#include <vector>
#include <memory>
#include <map>
#include "../models/Locker.h"
#include "../models/Location.h"

class LockerService {
private:
    std::vector<std::unique_ptr<LockerLocation>> locations;
    const double MAX_PACKAGE_SIZE = 20000.0;

public:
    LockerLocation* findNearestLocation(const GeoLocation& customerLocation);
    Locker* findAvailableLocker(LockerLocation* location, double packageSize);
    std::map<LockerSize, int> getLockerSizeDistribution(LockerLocation* location);
    void addLocation(std::unique_ptr<LockerLocation> location);
    int getAvailableLockerCount(LockerLocation* location);
    double getMaxPackageSize() const;
};
