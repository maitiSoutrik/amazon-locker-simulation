#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include "Locker.h"
#include "GeoLocation.h"

class LockerLocation {
private:
    std::string locationId;
    std::vector<Locker*> lockers;
    double latitude;
    double longitude;
    std::chrono::system_clock::time_point openTime;
    std::chrono::system_clock::time_point closeTime;

public:
    LockerLocation(const std::string& id, double lat, double lon);
    ~LockerLocation();

    void addLocker(Locker* locker);
    const std::vector<Locker*>& getLockers() const;
    std::string getId() const;
    GeoLocation getLocation() const;
    double getLatitude() const;
    double getLongitude() const;
    bool isOpen() const;
    void setOperatingHours(std::chrono::system_clock::time_point open,
                          std::chrono::system_clock::time_point close);
    Locker* findAvailableLocker(LockerSize size) const;
    double distanceTo(const GeoLocation& other) const;
};