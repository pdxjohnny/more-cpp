/*
 * John Andersen
 * File: libtransport/test/0_car.cpp
*/

#include "transport.h"

int test_car_unspecified() {
    // Make the car object
    transport::car car;
    // Make the string to put the formated car in
    char car_string[400];
    // Put the car transportrmation in that string
    MACRO_TEST_EQ(car.car_to_string(car_string, 400), 0);
    // Make sure the transportrmation put in was correct
    MACRO_TEST_STR_EQ(car_string, "unavailable, unavailable, unavailable, unavailable, unavailable");
    return EXIT_SUCCESS;
}

int test_car_car_to_string() {
    // Make the car object
    transport::car car(2002, "Ford", "Explorer", "YYZ911", NULL);
    // Make the string to put the formated car in
    char car_string[400];
    // Put the car transportrmation in that string
    MACRO_TEST_EQ(car.car_to_string(car_string, 400), 0);
    // Make sure the transportrmation put in was correct
    MACRO_TEST_STR_EQ(car_string, "2002, Ford, Explorer, YYZ911, unavailable");
    return EXIT_SUCCESS;
}

int test_car_car_to_string_fail() {
    // Make the car object
    transport::car car(2002, "Ford", "Explorer", "YYZ911", NULL);
    // Make the string to put the formated car in
    char car_string[3];
    // Cant put all that in tree characters! Should be -1 for fail
    MACRO_TEST_EQ(car.car_to_string(car_string, 3), -1);
    return EXIT_SUCCESS;
}

int test_car_car_from_string() {
    // Make the car object
    transport::car car;
    // Fill the car with this transportrmation
    MACRO_TEST_EQ(car.car_from_string("2002, Ford, Explorer, YYZ911, unavailable"), 0);
    // Make the string to put the formated car in
    char car_string[400];
    // Put the car transportrmation in that string
    MACRO_TEST_EQ(car.car_to_string(car_string, 400), 0);
    // Make sure the transportrmation put in was correct
    MACRO_TEST_STR_EQ(car_string, "2002, Ford, Explorer, YYZ911, unavailable");
    return EXIT_SUCCESS;
}

int test_car_car_from_string_fail() {
    // Make the car object
    transport::car car;
    // A really long car
    char long_car[600];
    // Because valgrind doesnt like memset
    int i;
    for (i = 0; i < 600; ++i) {
        long_car[i] = 'a';
    }
    long_car[600] = '\0';
    // Fill the car with the transportrmation that is too long
    MACRO_TEST_EQ(car.car_from_string(long_car), -1);
    return EXIT_SUCCESS;
}

int test_car_clear() {
    // Make the car object
    transport::car car(2002, "Ford", "Explorer", "YYZ911", NULL);
    // Make the string to put the formated car in
    char car_string[400];
    // Put the car transportrmation in that string
    MACRO_TEST_EQ(car.car_to_string(car_string, 400), 0);
    // Make sure the transportrmation put in was correct
    MACRO_TEST_STR_EQ(car_string, "2002, Ford, Explorer, YYZ911, unavailable");
    // It is set so clear it
    car.clear();
    // Put the car transportrmation in that string
    MACRO_TEST_EQ(car.car_to_string(car_string, 400), 0);
    // Make sure the transportrmation put in was correct
    MACRO_TEST_STR_EQ(car_string, "unavailable, unavailable, unavailable, unavailable, unavailable");
    return EXIT_SUCCESS;
}

