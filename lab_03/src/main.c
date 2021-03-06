#include "mergesort.h"
#include "stdio.h"

void print_error_message() {
    printf("Error: memory allocation failed.\n");
    exit(1);
}

/*
Comparators:
*/
int int_lt_comparator(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int char_lt_comparator(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

int str_lt_comparator(const void *a, const void *b) {

    const char *p1 = *(char**)a;
    const char *p2 = *(char**)b;

    while (*p1 && *p1 == *p2) {
        p1++, p2++;
    }

    return (*p1 > *p2) - (*p2 > *p1);
}

int main(int argc, char const *argv[]) {
    const char* type = argv[1];
    int elements = argc - 2;

    if (type[0] == 'i') {
        int *data = malloc(elements * sizeof(int));
        for (int i = 0; i < elements; i++) {
            data[i] = atoi(argv[i + 2]);
        }

        if (!mergesort(data, elements, sizeof(data[0]), int_lt_comparator)) {
            for (int i = 0; i < elements; i++) {
                if (i) {
                    printf(" ");
                }
                printf("%d", data[i]);
            }
        } else {
            print_error_message();
        }
        free(data);
    } else if (type[0] == 'c') {
        char *data = malloc(elements * sizeof(char));
        for (int i = 0; i < elements; i++) {
            data[i] = *argv[i + 2];
        }

        if (!mergesort(data, elements, sizeof(data[0]), char_lt_comparator)) {
            for (int i = 0; i < elements; i++) {
                if (i) {
                    printf(" ");
                }
                printf("%c", data[i]);
            }
        } else {
            print_error_message();
        }
        free(data);
    } else {
        char **data = malloc(elements * sizeof(char*));

        for (int i = 0; i < elements; i++) {
            data[i] = (char*)argv[i + 2];
        }

        if (!mergesort(data, elements, sizeof(data[0]), str_lt_comparator)) {
            for (int i = 0; i < elements; i++) {
                if (i) {
                    printf(" ");
                }
                printf("%s", data[i]);
            }
        } else {
            print_error_message();
        }   
        free(data);
    }
}
