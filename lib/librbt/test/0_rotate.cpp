#include "rbt.h"

int test_rbt_rotate_right() {
    // Create the grandparent
    rbt_node<char> * g = new rbt_node<char>;
    g->up = g->left = g->right = NULL;
    g->up = NULL;
    g->color = RBT_BLACK;
    // Create the uncle
    rbt_node<char> * u = new rbt_node<char>;
    u->up = u->left = u->right = NULL;
    u->up = g;
    g->right = u;
    u->color = RBT_RED;
    // Create the parent
    rbt_node<char> * p = new rbt_node<char>;
    p->up = p->left = p->right = NULL;
    p->up = g;
    g->left = p;
    p->color = RBT_RED;
    // Create a sibling for the node just inserted
    rbt_node<char> * s = new rbt_node<char>;
    s->up = s->left = s->right = NULL;
    s->up = g;
    p->right = s;
    s->color = RBT_RED;
    // Create the node that was just inserted
    rbt_node<char> * n = new rbt_node<char>;
    n->up = n->left = n->right = NULL;
    n->up = p;
    p->left = n;
    n->color = RBT_RED;
    // Rotate right
    rbt<char> r;
    r.rotate_right(p);
    // Make sure all is correct
    MACRO_TEST_POINTER_EQ(p->up, NULL);
    MACRO_TEST_POINTER_EQ(g->up, p);
    MACRO_TEST_POINTER_EQ(n->up, p);
    MACRO_TEST_POINTER_EQ(p->left, n);
    MACRO_TEST_POINTER_EQ(p->right, g);
    MACRO_TEST_POINTER_EQ(g->left, s);
    MACRO_TEST_POINTER_EQ(g->right, u);
    // Free stuff
    MACRO_DELETE_IF_NOT_NULL(g);
    MACRO_DELETE_IF_NOT_NULL(u);
    MACRO_DELETE_IF_NOT_NULL(p);
    MACRO_DELETE_IF_NOT_NULL(s);
    MACRO_DELETE_IF_NOT_NULL(n);
    return EXIT_SUCCESS;
}

int test_rbt_rotate_left() {
    // Create the grandparent
    rbt_node<char> * g = new rbt_node<char>;
    g->up = g->left = g->right = NULL;
    g->up = NULL;
    g->color = RBT_BLACK;
    // Create the uncle
    rbt_node<char> * u = new rbt_node<char>;
    u->up = u->left = u->right = NULL;
    u->up = g;
    g->left = u;
    u->color = RBT_RED;
    // Create the parent
    rbt_node<char> * p = new rbt_node<char>;
    p->up = p->left = p->right = NULL;
    p->up = g;
    g->right = p;
    p->color = RBT_RED;
    // Create a sibling for the node just inserted
    rbt_node<char> * s = new rbt_node<char>;
    s->up = s->left = s->right = NULL;
    s->up = g;
    p->left = s;
    s->color = RBT_RED;
    // Create the node that was just inserted
    rbt_node<char> * n = new rbt_node<char>;
    n->up = n->left = n->right = NULL;
    n->up = p;
    p->right = n;
    n->color = RBT_RED;
    // Rotate right
    rbt<char> r;
    r.rotate_left(p);
    // Make sure all is correct
    MACRO_TEST_POINTER_EQ(p->up, NULL);
    MACRO_TEST_POINTER_EQ(g->up, p);
    MACRO_TEST_POINTER_EQ(n->up, p);
    MACRO_TEST_POINTER_EQ(p->right, n);
    MACRO_TEST_POINTER_EQ(p->left, g);
    MACRO_TEST_POINTER_EQ(g->right, s);
    MACRO_TEST_POINTER_EQ(g->left, u);
    // Free stuff
    MACRO_DELETE_IF_NOT_NULL(g);
    MACRO_DELETE_IF_NOT_NULL(u);
    MACRO_DELETE_IF_NOT_NULL(p);
    MACRO_DELETE_IF_NOT_NULL(s);
    MACRO_DELETE_IF_NOT_NULL(n);
    return EXIT_SUCCESS;
}

