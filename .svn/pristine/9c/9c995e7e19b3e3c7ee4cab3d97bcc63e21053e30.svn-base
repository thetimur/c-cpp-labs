#include "clist.h"
#include "point_list.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

const size_t bin_size = 3;

void print(Intrusive_node_t *current, void *data) {
    Point_t *now = container_of(current, Point_t, node);
    printf((char*)data, now -> x, now -> y);
}

void print_text_file(Intrusive_node_t *current, void *data) {
    Point_t* now = container_of(current, Point_t, node);
    fprintf((FILE*)data, "%d %d\n", now->x, now->y);
}

void print_bin_file(Intrusive_node_t *current, void *data) {
    Point_t* now = container_of(current, Point_t, node);
    fwrite(&(now -> x), bin_size, 1, (FILE*)data);
    fwrite(&(now -> y), bin_size, 1, (FILE*)data);
}

void count(Intrusive_node_t *current, void *data) {
    if (current != NULL) {
        (*(int*)data)++;
    }
}

int main(int argc, char** argv) {
    assert(argc > 2);

    //We <3 constants
    const char* input_filename = argv[2];
    const char* action = argv[3];

    int x = 0, y = 0;    

    Intrusive_list_t l;
    init_list(&l);

    FILE *f;

    if (!strcmp(argv[1], "loadbin")) {
        f = fopen(input_filename, "rb");
        while (fread(&x, bin_size, 1, f) + fread(&y, bin_size, 1, f) == 2) {
            add_point(&l, x, y);
        }
    } else {
        f = fopen(input_filename, "r");
        while (fscanf(f, "%d %d", &x, &y) != EOF) {
            add_point(&l, x, y);
        }
    }
    fclose(f);

    if (!strcmp(action, "print")) {
    	char* format = argv[4];

    	apply(&l, (*print), format);
        printf("\n");
    } else if (!strcmp(action, "count")) {
    	int result = 0;

        apply(&l, (*count), &result);
        printf("%d\n", result);
    } else if (!strcmp(action, "savetext")) {
    	const char* output_filename = argv[4];
    	f = fopen(output_filename, "w");

    	apply(&l, (*print_text_file), f);

    	fclose(f);
    } else if (!strcmp(action, "savebin")) {
    	const char* output_filename = argv[4];
    	f = fopen(output_filename, "wb");

        apply(&l, (*print_bin_file), f);

    	fclose(f);
    } else {
    	printf("Unknown command\n");
    }

    remove_all_points(&l);
    free(((&l) -> head));
    return 0;
}