/*
 * John Andersen
 * File: libbst/test/0_order.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <libmacro.h>
#include <libbst.h>

template <typename dt>
class test_bst: public bst<dt> {
/*
 * This is left as an example of how to provide custom search functions
 */
/*
protected:
    int search_bst(char * key, bst_node<dt> * & root) {
        MACRO_PRINT_FILE_LINE("Searching for %s\n", key);
        return bst<dt>::search_bst(key, root);
    };
*/
};


int test_bst_order();
