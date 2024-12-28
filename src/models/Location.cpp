#include "models/Location.h"

LockerLocation::LockerLocation(const std::string& id, double lat, double lon)
    : locationId(id), latitude(lat), longitude(lon) {
    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch());
    auto hours_since_midnight = today.count() % 24;

    openTime = now - std::chrono::hours(hours_since_midnight) + std::chrono::hours(6);
    closeTime = now - std::chrono::hours(hours_since_midnight) + std::chrono::hours(22);
}

LockerLocation::~LockerLocation() {
    for (auto locker : lockers) {
        delete locker;
    }
}

void LockerLocation::addLocker(Locker* locker) {
    lockers.push_back(locker);
}

const std::vector<Locker*>& LockerLocation::getLockers() const {
    return lockers;
}

std::string LockerLocation::getId() const {
    return locationId;
}

GeoLocation LockerLocation::getLocation() const {
    return GeoLocation(latitude, longitude);
}

double LockerLocation::getLatitude() const {
    return latitude;
}

double LockerLocation::getLongitude() const {
    return longitude;
}

bool LockerLocation::isOpen() const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(
        now.time_since_epoch()
    );
    auto hours = duration.count() % 24;

    auto openHours = std::chrono::duration_cast<std::chrono::hours>(
        openTime.time_since_epoch()
    ).count() % 24;

    auto closeHours = std::chrono::duration_cast<std::chrono::hours>(
        closeTime.time_since_epoch()
    ).count() % 24;

    return hours >= openHours && hours < closeHours;
}

void LockerLocation::setOperatingHours(
    std::chrono::system_clock::time_point open,
    std::chrono::system_clock::time_point close) {
    openTime = open;
    closeTime = close;
}

Locker* LockerLocation::findAvailableLocker(LockerSize size) const {
    for (auto locker : lockers) {
        if (locker->getSize() == size && 
            locker->getState() == LockerState::AVAILABLE) {
            return locker;
        }
    }
    return nullptr;
}

double LockerLocation::distanceTo(const GeoLocation& other) const {
    GeoLocation thisLocation(latitude, longitude);
    return thisLocation.distanceTo(other);
}