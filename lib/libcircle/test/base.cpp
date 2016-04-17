#include "circle.h"

class test_circle : public circle {
public:
    test_circle(const char * key) : key(NULL) {
        MACRO_STRCPY_IF_NOT_NULL(this->key, key);
    };
    test_circle(const char * key, circle *& existing) : circle(existing), key(NULL) {
        MACRO_STRCPY_IF_NOT_NULL(this->key, key);
    };
    ~test_circle() {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(this->key);
    };
    virtual char match(circle *& node) {
        if (0 == strcmp(this->key, dynamic_cast<test_circle *>(node)->key)) {
            return 1;
        }
        return 0;
    };
    virtual char sort(circle *& node) {
        if (0 <= strcmp(this->key, dynamic_cast<test_circle *>(node)->key)) {
            return CIRCLE_NEXT;
        }
        return CIRCLE_HERE;
    };
private:
    char * key;
};

int test_circle_add() {
    char head_key[] = "a";
    test_circle * head = new test_circle(head_key);
    char mid1_key[] = "b";
    test_circle * mid1 = new test_circle(mid1_key);
    char mid2_key[] = "c";
    test_circle * mid2 = new test_circle(mid2_key);
    char tail_key[] = "d";
    test_circle * tail = new test_circle(tail_key);
    MACRO_DELETE_IF_NOT_NULL(head);
    MACRO_DELETE_IF_NOT_NULL(mid1);
    MACRO_DELETE_IF_NOT_NULL(mid2);
    MACRO_DELETE_IF_NOT_NULL(tail);
    return EXIT_SUCCESS;
}

