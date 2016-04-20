#include "uber.h"

char uber::car_type(transport::car & car) {
    if (uber::is_premium(car)) {
        return UBER_CAR_PREMIUM;
    } else if (uber::is_group(car)) {
        return UBER_CAR_GROUP;
    }
    // It it doesnt match any then it standard
    return UBER_CAR_STANDARD;
}

char uber::is_premium(transport::car & car) {
    const char * match[] = {
        "MERCEDES BENZ",
        "PORSCHE",
        "BENTLY",
        "ASTON MARTIN",
        "BMW",
        "LAMBORGHINI",
        NULL,
    };
    int i;
    for (i = 0; match[i] != NULL; ++i) {
        // Only match make
        if (0 == strcmp(car.make(), match[i])) {
            return 1;
        }
    }
    return 0;
}

char uber::is_group(transport::car & car) {
    // If the model contains these words
    const char * match[] = {
        "4WD",
        "FWD",
        NULL,
    };
    int i;
    for (i = 0; match[i] != NULL; ++i) {
        // Only match make
        if (NULL != strstr(car.model(), match[i])) {
            return 1;
        }
    }
    return 0;
}
