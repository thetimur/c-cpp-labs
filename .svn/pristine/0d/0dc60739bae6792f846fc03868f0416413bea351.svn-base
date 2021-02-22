#ifndef CLIST_H_
#define CLIST_H_

#include "stddef.h"

struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
};
typedef struct intrusive_node Intrusive_node_t;

struct intrusive_list {
  struct intrusive_node *head;
};
typedef struct intrusive_list Intrusive_list_t;

void init_list(Intrusive_list_t *current);
void add_node(Intrusive_list_t *current, Intrusive_node_t *value);
void remove_node(Intrusive_list_t *current, Intrusive_node_t *value);
int get_length(Intrusive_list_t *current);

#endif //CLIST_H