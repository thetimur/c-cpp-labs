#ifndef POINT_LIST_H
#define POINT_LIST_H

#include "clist.h"
#include "stdlib.h"
#include "stdio.h"
#include "stddef.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct point {
    int x, y;
    Intrusive_node_t node;
};

typedef struct point Point_t;

void add_point(Intrusive_list_t *current, int x, int y);
void remove_point(Intrusive_list_t *current, int x, int y);
void show_all_points(Intrusive_list_t *current);
void remove_all_points(Intrusive_list_t *current);

#endif //POINT_LIST_H