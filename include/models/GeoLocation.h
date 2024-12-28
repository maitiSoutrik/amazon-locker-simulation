#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

struct GeoLocation {
    double latitude;
    double longitude;

    GeoLocation(double lat = 0.0, double lon = 0.0);
    double distanceTo(const GeoLocation& other) const;
};