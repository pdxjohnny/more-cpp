#include <libcircle.h>

circle::circle() : head(this), next(this), prev(this) {}

circle::circle(circle * existing) : head(this), next(this), prev(this) {
    existing->add(this);
}

circle::~circle() {
    // They should all share the same head, if this was the head then make the
    // next one the head
    if (next->head == this) {
        circle * curr = next;
        do {
            curr->head = this->next;
            curr = curr->next;
        } while (curr != this);
    }
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

circle * circle::add(circle * node) {
    switch (sort(node)) {
    // If the thind we are adding belongs before this thing
    case CIRCLE_HERE:
        MACRO_PRINT_FILE_LINE("Will add node before \'%p\' node\n", this);
        node->head = head;
        prev->next = node;
        node->prev = prev;
        node->next = this;
        this->prev = node;
        return node;
    case CIRCLE_NEXT:
        if (next == head) {
            MACRO_PRINT_FILE_LINE("       Will add %p   after %p\n", node, this);
            node->head = head;
            node->next = next;
            next->prev = node;
            node->prev = this;
            this->next = node;
            return node;
        }
        return next->add(node);
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
    } else if (next != head) {
        return next->get(find_me);
    }
    return NULL;
}

