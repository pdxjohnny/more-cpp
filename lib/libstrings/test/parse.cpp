/*
 * John Andersen
 * File: libstrings/test/parse.cpp
*/

#include "strings.h"

int test_string_parse() {
    char * one = NULL;
    char * two = NULL;
    char * three = NULL;
    char ** data[] = {&one, &two, &three, NULL};
    // Parse in some data
    MACRO_TEST_EQ(strings::parse(data, "frist, second, third", ", "), EXIT_SUCCESS);
    // Make sure it was parsed in correctly
    MACRO_TEST_STR_EQ(one, "frist");
    MACRO_TEST_STR_EQ(two, "second");
    MACRO_TEST_STR_EQ(three, "third");
    // Free the data
    MACRO_DELETE_ARRAY_IF_NOT_NULL(one);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(two);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(three);
    return EXIT_SUCCESS;
}

int test_string_parse_fail() {
    char * one = NULL;
    char * two = NULL;
    char * three = NULL;
    char ** data[] = {&one, &two, &three, NULL};
    // Parse in some data
    MACRO_TEST_EQ(strings::parse(data, "frist, second", ", "), -1);
    // Make sure it was parsed in correctly
    MACRO_TEST_STR_EQ(one, "frist");
    MACRO_TEST_STR_EQ(two, "second");
    MACRO_TEST_POINTER_EQ(three, NULL);
    // Free the data
    MACRO_DELETE_ARRAY_IF_NOT_NULL(one);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(two);
    MACRO_DELETE_ARRAY_IF_NOT_NULL(three);
    return EXIT_SUCCESS;
}

int test_string_join_length() {
    // This is some bullshit so g++ doesnt complain
    char one_c[] = "first";
    char two_c[] = "second";
    char three_c[] = "third";
    char * one = one_c;
    char * two = two_c;
    char * three = three_c;
    // Make the data to join
    char ** data[] = {&one, &two, &three, NULL};
    // Find out how long the joined data should be
    MACRO_TEST_EQ(strings::join_length(data, ", ", NULL), 21);
    return EXIT_SUCCESS;
}

int test_string_join() {
    // This is some bullshit so g++ doesnt complain
    char one_c[] = "first";
    char two_c[] = "second";
    char four_c[] = "fourth";
    char * one = one_c;
    char * two = two_c;
    // Should become whatever we set if_null to be
    char * three = NULL;
    char * four = four_c;
    // Make the data to join
    char ** data[] = {&one, &two, &three, &four, NULL};
    // Find out how long the joined data should be
    MACRO_TEST_EQ(strings::join_length(data, ", ", "n/a"), 27);
    // Create the array that the joined data will go in
    char joined[27];
    // Join the strings
    MACRO_TEST_EQ(strings::join(joined, data, ", ", "n/a", 27), EXIT_SUCCESS);
    // Make sure they were joined correctly
    MACRO_TEST_STR_EQ(joined, "first, second, n/a, fourth");
    return EXIT_SUCCESS;
}

int test_string_join_fail() {
    // This is some bullshit so g++ doesnt complain
    char one_c[] = "first";
    char two_c[] = "second";
    char four_c[] = "fourth";
    char * one = one_c;
    char * two = two_c;
    // Should become whatever we set if_null to be
    char * three = NULL;
    char * four = four_c;
    // Make the data to join
    char ** data[] = {&one, &two, &three, &four, NULL};
    // Find out how long the joined data should be
    MACRO_TEST_EQ(strings::join_length(data, ", ", "n/a"), 27);
    // Create the array that the joined data will go in but make it too short
    // so that it fails
    char joined[25];
    // Join the strings it just return error because it could not finish
    // joining
    MACRO_TEST_EQ(strings::join(joined, data, ", ", "n/a", 25), -1);
    // Make sure it joined up until the one that was too long
    MACRO_TEST_STR_EQ(joined, "first, second, n/a, ");
    return EXIT_SUCCESS;
}

