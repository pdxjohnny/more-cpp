/*
* John Andersen
* File: Test lll
*/

#include "lll.h"

int main () {
MACRO_TEST(test_lll_add);
MACRO_TEST(test_lll_remove_increasing);
MACRO_TEST(test_lll_remove_decreasing);
MACRO_TEST(test_lll_remove_all);
return EXIT_SUCCESS;
}

