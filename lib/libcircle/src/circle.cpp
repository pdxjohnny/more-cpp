#include <libcircle.h>

circle::circle() : head(this), next(this), prev(this) {}

circle::circle(circle * existing) : head(this), next(this), prev(this) {
    existing->add(this);
}

circle::~circle() {
    // They should all share the same head, if this was the head then make the
    // next one the head
    if (next->head == this) {
        // We are dying so the next one becomes the head
        update_head(this->next);
    }
    // Deleteing this node removes it from the list
    prev->next = next;
    next->prev = prev;
}

circle * circle::bump() {
    // They should all share the same head, if this was the head then make the
    // next one the head
    if (next->head == this) {
        // We are dying so the next one becomes the head
        update_head(this->next);
    }
    // Deleteing this node removes it from the list
    prev->next = next;
    next->prev = prev;
    // We only car about ourself now
    head = this;
    next = this;
    prev = this;
    return next;
}

void circle::update_head(circle * set_to) {
    circle * curr = this;
    do {
        curr->head = set_to;
        curr = curr->next;
    } while (curr != this);
}

void circle::destroy() {
    circle * curr = this->next;
    circle * temp = NULL;
    while (curr != this) {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
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
    // Start addition at the head
    return head->add_node(node);
}

circle * circle::add_node(circle * node) {
    switch (sort(node)) {
    // If the thind we are adding belongs before this thing
    case CIRCLE_HERE:
        node->head = head;
        prev->next = node;
        node->prev = prev;
        node->next = this;
        this->prev = node;
        // If we are the head and we added before us then we need to make sure
        // that everyone knows that the new node is the head
        if (this == head) {
            update_head(node);
        }
        return node;
    case CIRCLE_NEXT:
        if (next == head) {
            node->head = head;
            node->next = next;
            next->prev = node;
            node->prev = this;
            this->next = node;
            return node;
        }
        return next->add_node(node);
    }
    return node;
}

char circle::remove(circle * find_me) {
    circle * find = get(find_me);
    if (find == NULL) {
        return -1;
    }
    delete find;
    find = NULL;
    return EXIT_SUCCESS;
}

circle * circle::get(circle * find_me) {
    if (match(find_me)) {
        return this;
    } else if (next != head) {
        return next->get(find_me);
    }
    return NULL;
}

// Just so that derived clases can make sure their sort functions are working
int circle::test_order(circle ** match_these) {
    circle * curr = head;
    do {
        // Bail in loop if we run out of things to match to or it doesnt match
        if (*match_these == NULL) {
            return -2;
        }
        if (!curr->match(*match_these)) {
            return -1;
        }
        curr = curr->next;
        ++match_these;
    } while (curr != head);
    return EXIT_SUCCESS;
}

// Derived classes will need to dynamic cast inside their callback
int circle::oneach(circle::each & each_class) {
    int err = EXIT_SUCCESS;
    circle * curr = head;
    do {
        err = each_class.do_func(curr);
        if (err != EXIT_SUCCESS) {
            return err;
        }
        curr = curr->next;
    } while (curr != head);
    return err;
}
