/*
 * John Andersen
 * File: libcircle/test/circle.cpp
*/

#include "circle.h"

int main() {
MACRO_TEST(test_circle_add_next_order);
MACRO_TEST(test_circle_destory);
MACRO_TEST(test_circle_add_prev_order);
MACRO_TEST(test_circle_add_random);
MACRO_TEST(test_circle_delete);
MACRO_TEST(test_circle_oneach);
return EXIT_SUCCESS;
}
