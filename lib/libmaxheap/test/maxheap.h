/*
 * John Andersen
 * File: libmaxheap/test/0_order.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <libmacro.h>
#include <libmaxheap.h>

template <typename dt>
class test_maxheap: public maxheap<dt> {
/*
 * This is left as an example of how to provide custom search functions
 */
/*
protected:
    int search_maxheap(char * key, maxheap_node<dt> * & root) {
        MACRO_PRINT_FILE_LINE("Searching for %s\n", key);
        return maxheap<dt>::search_maxheap(key, root);
    };
*/
};


int test_maxheap_order();
