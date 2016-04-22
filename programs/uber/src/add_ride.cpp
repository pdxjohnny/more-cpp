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
        found->print();
        MACRO_PRINT("Done printing found %s\n" ,"");
        if(found == NULL) {
            errno = ENODEV;
            MACRO_LOG_FATAL("Could not find any cars in %s with make \'%s\' and model \'%s\'", car_category, car_make, car_model);
        // When we remove it make sure we get the next in the category
        } else if (found == category) {
            MACRO_PRINT_FILE_LINE("Bumping\n%s", "");
            if (0 == strcmp(car_category, "standard")) {
                standard = (uber::car *)category->bump();
            } else if (0 == strcmp(car_category, "premium")) {
                premium = (uber::car *)category->bump();
            } else if (0 == strcmp(car_category, "group")) {
                group = (uber::car *)category->bump();
            }
        }
        // transport::ride()
        // uber::ride(found);
        delete found;
        category->print();
        MACRO_PRINT("Done printing category %s\n" ,"");
        return EXIT_SUCCESS;
    }
    MACRO_PRINT("Add a ride standard|premium|group make model start_location end_location customer_info%s\n", "");
    return EXIT_SUCCESS;
}
