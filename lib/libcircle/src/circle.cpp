#include <libcircle.h>

circle::circle() : head(this), next(this), prev(this) {}

circle::circle(circle *& existing) : head(this), next(this), prev(this) {
    existing->add(this);
}

circle::~circle() {
    // Deleteing this node removes it from the list
    prev->next = next;
    next->prev = prev;
}

/*
 * Example implementations
 */
/*
char circle::match(circle *& node) {
    if (0 == strcmp(this->key, key)) {
        return 1;
    }
    return 0;
}

char circle::sort(circle *& node) {
    if (0 <= strcmp(this->key, node->key)) {
        return CIRCLE_HERE;
    }
    return CIRCLE_NEXT;
}
*/

circle * circle::add(circle * add_node) {
    circle * node = NULL;
    switch (sort(add_node)) {
    // If the thind we are adding belongs before this thing
    case CIRCLE_HERE:
        prev->next = node;
        node->prev = prev;
        node->next = this;
        this->prev = node;
    case CIRCLE_NEXT:
        return next->add(add_node);
    }
    return node;
}

char circle::remove(circle *& find_me) {
    circle * find = get(find_me);
    if (find == NULL) {
        return -1;
    }
    delete find;
    find = NULL;
    return EXIT_SUCCESS;
}

circle * circle::get(circle *& find_me) {
    if (match(find_me)) {
        return this;
    } else if (next != head && next != this) {
        return next->get(find_me);
    }
    return NULL;
}

