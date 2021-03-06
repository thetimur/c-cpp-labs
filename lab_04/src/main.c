#include "clist.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct point {
  int x, y;
  Intrusive_node_t node;
};

typedef struct point Point_t;

const int COMMAND_MAX_LEN = 239;

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

int main() {
     Intrusive_list_t l;
     init_list(&l);

     while (1) {
        char *command = malloc(COMMAND_MAX_LEN * sizeof(char));
        scanf("%239s", command);
        if (!strcmp("add", command)) {
            int x = 0, y = 0;
            scanf("%d %d", &x, &y);
            add_point(&l, x, y);
        } else if (!strcmp("len", command)) {
            printf("%d\n", get_length(&l));
        } else if (!strcmp("print", command)) {
            show_all_points(&l);
        } else if (!strcmp("exit", command)) {
            free(command);
            remove_all_points(&l);
            free(((&l) -> head));
            return 0;
        } else if (!strcmp("rma", command)) {
            remove_all_points(&l);
        } else if (!strcmp("rm", command)) {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&l, x, y);
        } else {
            printf("Unknown command\n");
        }
        free(command);
     }
}