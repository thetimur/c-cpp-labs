#include "str.h"
#include "stdio.h"

char *my_strcpy(char* restrict s1, const char* restrict s2) {
    char *buf = s1;

    while ((*s1++ = *s2++) != '\0');

    return buf;
}

char *my_strcat(char* restrict s1, const char* restrict s2) {
    char *buf = s1;

    while (*s1 != '\0') {
        s1++;
    }

    while ((*s1++ = *s2++) != '\0');

    return buf;
}

int my_strcmp(char *s1, char *s2) {
    char *p1 = s1;
    char *p2 = s2;

    while (*p1 && *p1 == *p2) {
        p1++, p2++;
    }

    return (*p1 > *p2) - (*p2 > *p1);
}

size_t my_strlen(const char *s) {
    const char* buf = s;

    while(*buf != 0) {
        buf++;
    }
    
    return buf - s;
}
