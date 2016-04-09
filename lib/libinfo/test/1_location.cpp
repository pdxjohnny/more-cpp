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

int test_location_lnglat_clear_address() {
    // Make the location object
    info::location loc(97225, "1000 SW Salmon Street", "Portland", "OR", "USA");
    loc.lnglat(-122.35, 45.35);
    // Make sure that address was cleared
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(loc.address_to_string(addr_string, 400), 0);
    // Make sure that it was all n/a
    MACRO_TEST_STR_EQ(addr_string, "n/a, n/a, n/a, n/a, n/a");
    // All is well
    return EXIT_SUCCESS;
}

int test_location_lnglat_clear_lnglat() {
    // Make the location object
    info::location loc(-122.35, 45.35);
    // Now set the location to an address
    MACRO_TEST_EQ(loc.address_from_string("1000 SW Salmon Street, Portland, OR, 97225, USA"), 0);
    // Make sure that address was cleared
    char addr_string[400];
    // Put the address information in that string
    MACRO_TEST_EQ(loc.address_to_string(addr_string, 400), 0);
    // Grab the lng lat values
    double lng, lat;
    loc.lnglat(&lng, &lat);
    // Make sure that it was all 0.0
    MACRO_TEST_FLOAT_EQ(lng, 0.0);
    MACRO_TEST_FLOAT_EQ(lat, 0.0);
    // All is well
    return EXIT_SUCCESS;
}

