#include "info.h"
#include <libinfo.h>

info::location::location() : lng(0.0), lat(0.0) {}

info::location::location(location & copy) : info::address(copy), lng(copy.lng), lat(copy.lat) {}

info::location::location(double lng, double lat) : lng(lng), lat(lat) {}

info::location::location(int zip, const char * street, const char * city, const char * state_or_province, const char * country) : info::address(zip, street, city, state_or_province, country), lng(0.0), lat(0.0) {}

info::location::~location() {}

void info::location::clear () {
    // Clear the address
    info::address::clear();
    // Clear the lng lat
    lng = 0.0;
    lat = 0.0;
}

int info::location::address_from_string(const char * from) {
    // Populate the address data
    info::address::address_from_string(from);
    // We no longer know the latitude and longitude of our location so clear it
    lng = 0.0;
    lat = 0.0;
    return EXIT_SUCCESS;
}

int info::location::lnglat(double * lng, double * lat) {
    if (lng != NULL) {
        *lng = this->lng;
    }
    if (lat != NULL) {
        *lat = this->lat;
    }
    return EXIT_SUCCESS;
}

int info::location::lnglat(double lng, double lat) {
    // We no longer know the latitude and longitude of our location so clear it
    this->lng = lng;
    this->lat = lat;
    // Clear the address data
    info::address::clear();
    return EXIT_SUCCESS;
}

float info::location::distance_in_miles(const location & point) {
    /*
     * dlon = lon2 - lon1
     * dlat = lat2 - lat1
     * a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2
     * c = 2 * atan2( sqrt(a), sqrt(1-a) )
     * d = R * c (where R is the radius of the Earth)
    */
    // Make sure the we have lng and lat and the opther point does too
    MACRO_CANT_EQ(lng, 0.0);
    MACRO_CANT_EQ(lat, 0.0);
    MACRO_CANT_EQ(point.lng, 0.0);
    MACRO_CANT_EQ(point.lat, 0.0);
    // Convert from degrees to radians
    double lat_r = lat * M_PI / 180.0;
    double plat_r = point.lat * M_PI / 180.0;
    double dlng = (lng - point.lng) * M_PI / 180.0;
    double dlat = (lat - point.lat) * M_PI / 180.0;
    // Preform the haversine formula
    double a = pow(sin(dlat / 2.0), 2.0) +
        (cos(lat_r) * cos(plat_r) *
        pow(sin(dlng / 2.0), 2.0));
    return INFO_EARTHS_RADIUS_IN_MILES * 2.0 * atan2(
        sqrt(a), sqrt(1.0 - a)
    );
}

