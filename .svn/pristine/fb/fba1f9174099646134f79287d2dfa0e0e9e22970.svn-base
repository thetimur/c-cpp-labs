#include "point_list.h"

void add_point(Intrusive_list_t *current, int x, int y) {
    Point_t *new_head = malloc(sizeof(Point_t));
    (new_head -> x) = x;
    (new_head -> y) = y;
    (new_head -> node).prev = (new_head -> node).next = NULL;
    
    add_node(current, &(new_head -> node));
}

void remove_point(Intrusive_list_t *current, int x, int y) {
    Intrusive_node_t *cur = (current -> head);

    while ((cur -> next) != NULL) {
        Point_t *now = container_of((cur -> next), Point_t, node);
        
        if((now -> x) == x && (now -> y) == y){
            remove_node(current, cur -> next);
            free(now);
        } else {
            cur = cur -> next;
        }
    }
}

void show_all_points(Intrusive_list_t *current) {
    Intrusive_node_t *cur = (current -> head);
    
    while ((cur -> next) != NULL) {
        Point_t *now = container_of((cur -> next), Point_t, node);
        printf("(%d %d)", now -> x, now -> y);
        cur = (cur -> next);
        
        if ((cur -> next) != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

void remove_all_points(Intrusive_list_t *current) {
    Intrusive_node_t *cur = (current -> head);

    while ((cur -> next) != NULL) {
        Point_t *now = container_of((cur -> next), Point_t, node);
        
        remove_node(current, cur -> next);
        free(now);
    }
}
