
#include "models/GeoLocation.h"

GeoLocation::GeoLocation(double lat, double lon) 
    : latitude(lat), longitude(lon) {}

double GeoLocation::distanceTo(const GeoLocation& other) const {
    const double R = 6371.0; // Earth's radius in kilometers
    const double deg2rad = M_PI / 180.0;

    double lat1 = latitude * deg2rad;
    double lat2 = other.latitude * deg2rad;
    double dLat = (other.latitude - latitude) * deg2rad;
    double dLon = (other.longitude - longitude) * deg2rad;

    double a = sin(dLat/2) * sin(dLat/2) +
              cos(lat1) * cos(lat2) *
              sin(dLon/2) * sin(dLon/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}
