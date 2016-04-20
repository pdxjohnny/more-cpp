#include "uber.h"

int test_uber_car_type_standard() {
    transport::car car(1999, "Toyota", "Camery", "QQZ-553", "23J2RE9FUSENWERJWEJ");
    MACRO_TEST_EQ(uber::car_type(car), UBER_CAR_STANDARD);
    return EXIT_SUCCESS;
}

int test_uber_car_type_group() {
    transport::car car(1999, "Ford", "Excursion 4WD", "QQZ-553", "23J2RE9FUSENWERJWEJ");
    MACRO_TEST_EQ(uber::car_type(car), UBER_CAR_GROUP);
    return EXIT_SUCCESS;
}

int test_uber_car_type_premium() {
    transport::car car(1999, "BMW", "320", "QQZ-553", "23J2RE9FUSENWERJWEJ");
    MACRO_TEST_EQ(uber::car_type(car), UBER_CAR_PREMIUM);
    return EXIT_SUCCESS;
}
