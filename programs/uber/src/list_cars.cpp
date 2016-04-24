/*
 * John Andersen
 * File: uber/src/list_cars.cpp
*/

#include "uber.h"


int list_cars(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    char * to_list = NULL;
    char *** list = NULL;
    if (argc > 2) {
        to_list = argv[2];
        if (0 == strcmp(to_list, "standard")) {
            if (standard != NULL) {
                MACRO_PRINT("Standard cars%s\n", "");
                list = standard->unique_makes_models();
            }
        } else if (0 == strcmp(to_list, "premium")) {
            if (premium != NULL) {
                MACRO_PRINT("Premium cars%s\n", "");
                list = premium->unique_makes_models();
            }
        } else if (0 == strcmp(to_list, "group")) {
            if (group != NULL) {
                MACRO_PRINT("Group cars%s\n", "");
                list = group->unique_makes_models();
            }        }
        if (list != NULL) {
            char *** car_list = list;
            int i = 0;
            for (; *car_list != NULL; ++car_list) {
                if (**car_list != NULL) {
                    ++i;
                    MACRO_PRINT("%-7d %s\n", i, **car_list);
                }
            }
            MACRO_DELETE_ARRAY_OF_STRINGS(list);
            return EXIT_SUCCESS;
        }
        MACRO_LOG_FATAL("Categories available standard|premium|group, no %s cars are currently available", to_list);
    }
    MACRO_LOG_FATAL("Add a category to list standard|premium|group%s", "");
}
