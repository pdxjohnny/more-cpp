#include "uber.h"

int help(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    char functions[] = "help|list_cars|add_ride";
    MACRO_PRINT("Usage %s %s\n", argv[0], functions);
    return EXIT_SUCCESS;
}
