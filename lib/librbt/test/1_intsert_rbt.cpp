#include "rbt.h"

int test_rbt_insert_rbt_right() {
    // The tree, were testing it yo
    rbt<char> r;
    // Create the grandparent / root
    char gk[] = "b";
    rbt_node<char> * g = r.insert_return_node(gk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, NULL);
    MACRO_TEST_POINTER_EQ(g->right, NULL);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    // Create the uncle
    char uk[] = "a";
    rbt_node<char> * u = r.insert_return_node(uk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, u);
    MACRO_TEST_POINTER_EQ(g->right, NULL);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_RED);
    // Create the parent
    char pk[] = "d";
    rbt_node<char> * p = r.insert_return_node(pk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, u);
    MACRO_TEST_POINTER_EQ(g->right, p);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_RED);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, NULL);
    MACRO_TEST_POINTER_EQ(p->right, NULL);
    MACRO_TEST_EQ(p->color, RBT_RED);
    // Create the sibling
    char sk[] = "c";
    rbt_node<char> * s = r.insert_return_node(sk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, u);
    MACRO_TEST_POINTER_EQ(g->right, p);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, s);
    MACRO_TEST_POINTER_EQ(p->right, NULL);
    MACRO_TEST_EQ(p->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(s->up, p);
    MACRO_TEST_POINTER_EQ(s->left, NULL);
    MACRO_TEST_POINTER_EQ(s->right, NULL);
    MACRO_TEST_EQ(s->color, RBT_RED);
    // Create the node
    char nk[] = "e";
    rbt_node<char> * n = r.insert_return_node(nk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, u);
    MACRO_TEST_POINTER_EQ(g->right, p);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, s);
    MACRO_TEST_POINTER_EQ(p->right, n);
    MACRO_TEST_EQ(p->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(s->up, p);
    MACRO_TEST_POINTER_EQ(s->left, NULL);
    MACRO_TEST_POINTER_EQ(s->right, NULL);
    MACRO_TEST_EQ(s->color, RBT_RED);
    MACRO_TEST_POINTER_EQ(n->up, p);
    MACRO_TEST_POINTER_EQ(n->left, NULL);
    MACRO_TEST_POINTER_EQ(n->right, NULL);
    MACRO_TEST_EQ(n->color, RBT_RED);
    return EXIT_SUCCESS;
}

int test_rbt_insert_rbt_left() {
    // The tree, were testing it yo
    rbt<char> r;
    // Create the grandparent / root
    char gk[] = "d";
    rbt_node<char> * g = r.insert_return_node(gk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, NULL);
    MACRO_TEST_POINTER_EQ(g->right, NULL);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    // Create the uncle
    char uk[] = "e";
    rbt_node<char> * u = r.insert_return_node(uk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, NULL);
    MACRO_TEST_POINTER_EQ(g->right, u);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_RED);
    // Create the parent
    char pk[] = "b";
    rbt_node<char> * p = r.insert_return_node(pk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, p);
    MACRO_TEST_POINTER_EQ(g->right, u);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_RED);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, NULL);
    MACRO_TEST_POINTER_EQ(p->right, NULL);
    MACRO_TEST_EQ(p->color, RBT_RED);
    // Create the sibling
    char sk[] = "c";
    rbt_node<char> * s = r.insert_return_node(sk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, p);
    MACRO_TEST_POINTER_EQ(g->right, u);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, NULL);
    MACRO_TEST_POINTER_EQ(p->right, s);
    MACRO_TEST_EQ(p->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(s->up, p);
    MACRO_TEST_POINTER_EQ(s->left, NULL);
    MACRO_TEST_POINTER_EQ(s->right, NULL);
    MACRO_TEST_EQ(s->color, RBT_RED);
    // Create the node
    char nk[] = "a";
    rbt_node<char> * n = r.insert_return_node(nk);
    MACRO_TEST_POINTER_EQ(g->up, NULL);
    MACRO_TEST_POINTER_EQ(g->left, p);
    MACRO_TEST_POINTER_EQ(g->right, u);
    MACRO_TEST_EQ(g->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(u->up, g);
    MACRO_TEST_POINTER_EQ(u->left, NULL);
    MACRO_TEST_POINTER_EQ(u->right, NULL);
    MACRO_TEST_EQ(u->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(p->up, g);
    MACRO_TEST_POINTER_EQ(p->left, n);
    MACRO_TEST_POINTER_EQ(p->right, s);
    MACRO_TEST_EQ(p->color, RBT_BLACK);
    MACRO_TEST_POINTER_EQ(s->up, p);
    MACRO_TEST_POINTER_EQ(s->left, NULL);
    MACRO_TEST_POINTER_EQ(s->right, NULL);
    MACRO_TEST_EQ(s->color, RBT_RED);
    MACRO_TEST_POINTER_EQ(n->up, p);
    MACRO_TEST_POINTER_EQ(n->left, NULL);
    MACRO_TEST_POINTER_EQ(n->right, NULL);
    MACRO_TEST_EQ(n->color, RBT_RED);
    return EXIT_SUCCESS;
}

