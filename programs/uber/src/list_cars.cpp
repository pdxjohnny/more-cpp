#include "uber.h"


int list_cars(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides) {
    char * to_list = NULL;
    if (argc > 2) {
        to_list = argv[2];
        if (0 == strcmp(to_list, "standard")) {
            if (standard != NULL) {
                MACRO_PRINT("Standard cars%s\n", "");
                standard->print();
            } else {
                MACRO_PRINT("No standard cars%s\n", "");
            }
            return EXIT_SUCCESS;
        } else if (0 == strcmp(to_list, "premium")) {
            if (premium != NULL) {
                MACRO_PRINT("Premium cars%s\n", "");
                premium->print();
            } else {
                MACRO_PRINT("No premium cars%s\n", "");
            }
            return EXIT_SUCCESS;
        } else if (0 == strcmp(to_list, "group")) {
            if (group != NULL) {
                MACRO_PRINT("Group cars%s\n", "");
                group->print();
            } else {
                MACRO_PRINT("No group cars%s\n", "");
            }
            return EXIT_SUCCESS;
        }
        MACRO_PRINT("Categories available standard|premium|group%s\n", "");
        return EXIT_SUCCESS;
    }
    MACRO_PRINT("Add a category to list standard|premium|group%s\n", "");
    return EXIT_SUCCESS;
}
