#include "uber.h"

int test_uber_ride_ride_from_string() {
    // Time created
    time_t timestamp = time(NULL) - (time_t)1000;
    // Make it parse this and if it comes out the same were good
    char input[500];
    sprintf(input,
        "2000 NE Glisan Street, Portland, OR, 97268"
        ", USA . 44.350000 . -122.350000 - "
        "1000 SW Salmon Street, Portland, OR, 97225"
        ", USA . 43.350000 . -121.350000"
        " - 20.000000 - 85.189499 - 255.568481 / 340.757996"
        " / 1999, TOYOTA, CARMERY, YYZ-998, DBI2J298WEKJNSDF"
        " / John Snow, 7778884343; 7788990066554433, 05, 06, 978 / %ld",
        timestamp
    );
    // output is slightly different because of floats
    char output[500];
    sprintf(output,
        "2000 NE Glisan Street, Portland, OR, 97268"
        ", USA . 44.349998 . -122.349998 - "
        "1000 SW Salmon Street, Portland, OR, 97225"
        ", USA . 43.349998 . -121.349998"
        " - 20.000000 - 85.189499 - 255.568481 / 340.757996"
        " / 1999, TOYOTA, CARMERY, YYZ-998, DBI2J298WEKJNSDF"
        " / John Snow, 7778884343; 7788990066554433, 05, 06, 978 / %ld",
        timestamp
    );
    // Make the ride object
    uber::ride ride;
    // Make the string to put the formated ride in
    char ride_string[1000];
    // Parse it in
    MACRO_TEST_EQ(ride.ride_from_string(input), 0);
    // Put the ride into a string to check against
    MACRO_TEST_EQ(ride.ride_to_string(ride_string, 1000), 0);
    // Check it
    MACRO_TEST_MEM_STR_EQ(ride_string, output);
    return EXIT_SUCCESS;
}
