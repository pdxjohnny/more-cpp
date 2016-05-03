/*
 * John Andersen
 * File: liblll/test/lll.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <libmacro.h>
#include <liblll.h>

int test_lll_node_basic_add();
int test_lll_node_basic_remove_increasing();
int test_lll_node_basic_remove_decreasing();
int test_lll_node_basic_remove_all();
int test_lll_node_basic_remove_self();
int test_lll_node_basic_get_index0();
int test_lll_node_basic_get();
int test_lll_basic_add();
int test_lll_basic_remove();
int test_lll_basic_remove_all();
int test_lll_basic_get();
int test_lll_basic_operator_subscript();
