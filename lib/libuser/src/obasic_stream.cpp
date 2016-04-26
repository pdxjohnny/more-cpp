#include "user.h"

user::obasic_stream::~obasic_stream () {}

typename user::obasic_stream::int_type user::obasic_stream::overflow (typename user::obasic_stream::int_type c)
{
    std::cout.put(c);
    return c;
}
