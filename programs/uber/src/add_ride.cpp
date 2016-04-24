/*
 * John Andersen
 * File: uber/src/add_ride.cpp
*/

#include "uber.h"


int add_ride(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    char * car_category = NULL;
    char * car_make = NULL;
    char * car_model = NULL;
    char * customer_info = NULL;
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
        // Grab their customer info
        customer_info = argv[7];
        info::customer customer;
        if (customer.customer_from_string(customer_info) != EXIT_SUCCESS) {
            MACRO_PRINT("Customer infomation should contain name, phone #, credit card number, experation month and year, and ccv%s\n", "");
            MACRO_PRINT("Example: \'John Snow, 8007765543; 4456778366785436, 03, 99, 342\'%s\n", "");
            MACRO_LOG_FATAL("Bad customer info \'%s\'", customer_info);
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
            trip_to_add = new transport::ride(0.0, 5.0, 5.0, 5.0, start, end);
        } else if (0 == strcmp(car_category, "premium")) {
            category = premium = (uber::car *)found->bump();
            // $25 minimum on premium
            trip_to_add = new transport::ride(25.0, 6.0, 5.0, 5.0, start, end);
        } else if (0 == strcmp(car_category, "group")) {
            if (argc < 9) {
                MACRO_LOG_FATAL("Please specifiy how many people will be sharing the car with you (after customer info)%s", "");
            }
            category = group = (uber::car *)found->bump();
            const float base_group_fare = 5.0;
            float num_riders = strtof(argv[8], NULL) + 1.0;
            if (num_riders < 1.0 || num_riders > 50.0) {
                MACRO_LOG_FATAL("Either you are riding with no one, 0, or you are riding with less than 51 people, no car hold more than that, you said you were riding with %0.01f people", num_riders - 1.0);
            }
            MACRO_PRINT_FILE_LINE("The fare will be $%0.02f\n", base_group_fare / num_riders);
            trip_to_add = new transport::ride(0.0, base_group_fare / num_riders, 5.0, 5.0, start, end);
        }
        // Combine the trip and the ride
        uber::ride ride_to_add(*found, *trip_to_add, customer);
        ride_to_add.save(STDOUT_FILENO);
        // We have no use for these anymore
        MACRO_DELETE_IF_NOT_NULL(trip_to_add);
        MACRO_DELETE_IF_NOT_NULL(found);
        // Add that ride to the rides manager teh key wiith which we add with
        // be the time
        time_t treq = ride_to_add.time_requested();
        char * timestamp = std::ctime(&treq);
        rides[timestamp] = ride_to_add;
        return EXIT_SUCCESS;
    }
    MACRO_PRINT("Add a ride standard|premium|group make model start_location end_location customer_info%s\n", "");
    return EXIT_SUCCESS;
}
