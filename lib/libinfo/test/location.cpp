#include "info.h"

int test_location_lnglat() {
    // Make the location object
    info::location loc;
    double lng = -122.35;
    double lat = 45.35;
    double t_lng, t_lat;
    // Set and make sure it was set correctly
    loc.lnglat(lng, lat);
    // Get what they were set to
    loc.lnglat(&t_lng, &t_lat);
    // Make sure they are correct
    MACRO_TEST_FLOAT_EQ(lng, t_lng);
    MACRO_TEST_FLOAT_EQ(lat, t_lat);
    // All is well
    return EXIT_SUCCESS;
}

