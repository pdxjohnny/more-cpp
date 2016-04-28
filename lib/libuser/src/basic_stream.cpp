#include "user.h"

user::basic_stream::~basic_stream () {}

typename user::basic_stream::int_type user::basic_stream::overflow (typename user::basic_stream::int_type c) {
    std::cout.put(c);
    return c;
}

typename user::basic_stream::int_type user::basic_stream::underflow () {
    char tmp[1];
    /*
    std::cin.get(tmp, 1);
    */
    tmp[0] = '\0';
    return user::basic_stream::int_type(EOF);
}
