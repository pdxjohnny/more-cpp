/*
 * John Andersen
 * File: libuser/include/libuser.h
*/
#include <libuser.h>

user::basic::basic() : std::ostream(this) {}

user::basic::~basic() {}

int user::basic::overflow(int c) {
    std::cout.put(c);
    return 0;
}
