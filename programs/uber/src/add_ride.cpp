#include "uber.h"


int add_ride(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    char * car_category = NULL;
    char * car_make = NULL;
    char * car_model = NULL;
    char * start_location = NULL;
    char * end_location = NULL;
    uber::car * category = NULL;
    if (argc > 7) {
        // Find the category to get the car from
        car_category = argv[2];
        if (0 == strcmp(car_category, "standard")) {
            category = standard;
        } else if (0 == strcmp(car_category, "premium")) {
            category = premium;
        } else if (0 == strcmp(car_category, "group")) {
            category = group;
        }
        // If they failed to pick a vaild category then exit
        if (category == NULL) {
            errno = ENODEV;
            MACRO_LOG_FATAL("No cars available for %s category", car_category);
        }
        // The locations
        start_location = argv[5];
        end_location = argv[6];
        info::location start;
        if (start.location_from_string(start_location) != EXIT_SUCCESS) {
            MACRO_PRINT("Location should be an address followed be the latitude and longitude of that address%s\n", "");
            MACRO_PRINT("Example: \'12 SW Q street, Portland, OR, 97225, USA . 45.45 . -122.34\'%s\n", "");
            MACRO_LOG_FATAL("Bad location \'%s\'", start_location);
        }
        info::location end;
        if (end.location_from_string(end_location) != EXIT_SUCCESS) {
            MACRO_PRINT("Location should be an address followed be the latitude and longitude of that address%s\n", "");
            MACRO_PRINT("Example: \'12 SW Q street, Portland, OR, 97225, USA . 45.45 . -122.34\'%s\n", "");
            MACRO_LOG_FATAL("Bad location \'%s\'", end_location);
        }
        // Grab a car from one of those categories
        car_make = argv[3];
        car_model = argv[4];
        uber::car find (0, car_make, car_model, "", "");
        uber::car * found = (uber::car *)category->get(&find);
        if(found == NULL) {
            errno = ENODEV;
            MACRO_LOG_FATAL("Could not find any cars in %s with make \'%s\' and model \'%s\'", car_category, car_make, car_model);
        }
        transport::ride * trip_to_add = NULL;
        // Remove the car with bump and then set the pricing options and start
        // and end locations for this ride
        if (0 == strcmp(car_category, "standard")) {
            category = standard = (uber::car *)found->bump();
            trip_to_add = new transport::ride(0.0, 5.0, 2.0, 2.0, 5.0, 5.0, start, end);
        } else if (0 == strcmp(car_category, "premium")) {
            category = premium = (uber::car *)found->bump();
            trip_to_add = new transport::ride(0.0, 2.0, 5.0, 5.0, 5.0, 5.0, start, end);
        } else if (0 == strcmp(car_category, "group")) {
            category = group = (uber::car *)found->bump();
            trip_to_add = new transport::ride(0.0, 5.0, 1.0, 1.0, 1.0, 1.0, start, end);
        }
        // Combine the trip and the ride
        uber::ride ride_to_add(*found, *trip_to_add);
        // We have no use for these anymore
        MACRO_DELETE_IF_NOT_NULL(trip_to_add);
        MACRO_DELETE_IF_NOT_NULL(found);
        // Add that ride to the rides manager teh key wiith which we add with
        // be the time
        time_t now = time(NULL);
        char * timestamp = ctime(&now);
        rides[timestamp] = ride_to_add;
        return EXIT_SUCCESS;
    }
    MACRO_PRINT("Add a ride standard|premium|group make model start_location end_location customer_info%s\n", "");
    return EXIT_SUCCESS;
}
