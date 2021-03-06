#include "clist.h"
#include "stdlib.h"

void init_list(Intrusive_list_t *current) {
	(current -> head) = malloc(sizeof(Intrusive_node_t));
	((current -> head) -> prev) = NULL;
	((current -> head) -> next) = NULL;
}

void add_node(Intrusive_list_t *current, Intrusive_node_t *value) {
	Intrusive_node_t *head = (current -> head);

	while ((head -> next) != NULL) {
		head = (head -> next);
	}

	(value -> prev) = head;
	(head -> next) = value;
}

void remove_node(Intrusive_list_t *current, Intrusive_node_t *value) {
	Intrusive_node_t *head = (value -> prev);

	(head -> next) = (value -> next);

	if ((value -> next) != NULL) {
		((value -> next) -> prev) = head;
	}
}

int get_length(Intrusive_list_t *current) {
	Intrusive_node_t *head = (current -> head);
	int result = 0;
	
	while ((head -> next) != NULL) {
		head = (head -> next);
		result++;
	}

	return result;
}

void apply(Intrusive_list_t *list, void (*op)(Intrusive_node_t *node, void *data), void *data) {
    Intrusive_node_t *cur = list -> head;
    while(cur -> next) {
        (*op)(cur -> next, data);
        cur = cur -> next;
    }
}
