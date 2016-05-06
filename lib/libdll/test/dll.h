/*
 * John Andersen
 * File: libdll/test/dll.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <libmacro.h>
#include <libdll.h>

int test_dll_node_basic_add();
int test_dll_node_basic_remove_increasing();
int test_dll_node_basic_remove_decreasing();
int test_dll_node_basic_remove_all();
int test_dll_node_basic_remove_self();
int test_dll_node_basic_get_index0();
int test_dll_node_basic_get();
int test_dll_node_basic_copy();
int test_dll_basic_add();
int test_dll_basic_remove();
int test_dll_basic_remove_all();
int test_dll_basic_get();
int test_dll_basic_operator_subscript();
int test_dll_basic_operator_copy();
int test_dll_node_add();
int test_dll_node_remove_increasing();
int test_dll_node_remove_decreasing();
int test_dll_node_remove_all();
int test_dll_node_remove_self();
int test_dll_node_get_index0();
int test_dll_node_get();
int test_dll_node_correct_data();
int test_dll_add();
int test_dll_remove();
int test_dll_remove_all();
int test_dll_get();
int test_dll_operator_subscript();
int test_dll_correct_data();
int test_dll_operator_copy();
