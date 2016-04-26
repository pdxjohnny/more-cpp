/*
 * John Andersen
 * File: libuser/include/libuser.h
*/
#include <libuser.h>

user::obasic::obasic() : std::ios(0), std::ostream(&obasic_stream_instance) {}

user::obasic::~obasic() {}
