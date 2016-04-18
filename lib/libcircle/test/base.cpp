#include "circle.h"

class test_circle : public circle {
public:
    test_circle(const char * key) : key(NULL) {
        MACRO_STRCPY_IF_NOT_NULL(this->key, key);
    };
    test_circle(const char * key, circle * existing) : circle(), key(NULL) {
        MACRO_STRCPY_IF_NOT_NULL(this->key, key);
        existing->add(this);
    };
    ~test_circle() {
        MACRO_DELETE_ARRAY_IF_NOT_NULL(this->key);
    };
    virtual char match(circle * node) {
        MACRO_PRINT_FILE_LINE("Node to match is: %p\n", this);
        MACRO_PRINT_FILE_LINE("Node to match has key: %s\n", this->key);
        MACRO_PRINT_FILE_LINE("Node to add is: %p\n", dynamic_cast<test_circle *>(node));
        MACRO_PRINT_FILE_LINE("Node to add has key: %s\n", dynamic_cast<test_circle *>(node)->key);
        if (0 == strcmp(this->key, dynamic_cast<test_circle *>(node)->key)) {
            return 1;
        }
        return 0;
    };
    virtual char sort(circle * node) {
        MACRO_PRINT_FILE_LINE("Node to sort is: %p   key: %s\n", this, this->key);
        MACRO_PRINT_FILE_LINE("Node to add is:  %p   key: %s\n", dynamic_cast<test_circle *>(node), dynamic_cast<test_circle *>(node)->key);
        if (0 >= strcmp(this->key, dynamic_cast<test_circle *>(node)->key)) {
            return CIRCLE_NEXT;
        }
        return CIRCLE_HERE;
    };
private:
    char * key;
};

int test_circle_add_next_order() {
    // Add them
    test_circle * head = new test_circle("a");
    test_circle * mid1 = new test_circle("b", head);
    test_circle * mid2 = new test_circle("c", head);
    test_circle * tail = new test_circle("d", head);
    // Make sure they are in the right order
    test_circle * should_be[] = {
        head,
        mid1,
        mid2,
        tail,
        NULL
    };
    MACRO_TEST_EQ(head->test_order((circle **)should_be), EXIT_SUCCESS);
    // Delete them
    MACRO_DELETE_IF_NOT_NULL(head);
    MACRO_DELETE_IF_NOT_NULL(mid1);
    MACRO_DELETE_IF_NOT_NULL(mid2);
    MACRO_DELETE_IF_NOT_NULL(tail);
    return EXIT_SUCCESS;
}

int test_circle_destory() {
    // Create the first one
    test_circle * head = new test_circle("a");
    // Add them all to the first one
    head->add(new test_circle("b"));
    head->add(new test_circle("c"));
    head->add(new test_circle("d"));
    // Delete the list
    head->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(head);
    return EXIT_SUCCESS;
}

int test_circle_add_prev_order() {
    // Create the first one
    test_circle * head = new test_circle("d");
    // Add them all to the first one
    test_circle * mid1 = new test_circle("c", head);
    test_circle * mid2 = new test_circle("b", head);
    test_circle * tail = new test_circle("a", head);
    // Make sure they are in the right order
    test_circle * should_be[] = {
        tail,
        mid2,
        mid1,
        head,
        NULL
    };
    MACRO_TEST_EQ(head->test_order((circle **)should_be), EXIT_SUCCESS);
    // Delete the list
    head->destroy();
    // Delete the first one
    MACRO_DELETE_IF_NOT_NULL(head);
    return EXIT_SUCCESS;
}

