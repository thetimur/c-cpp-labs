#include "test_str.h"

void test_strcmp(){
    char *a = "HI!";
    char *b = "HI!";
    char *c = "Hello!";
    assert(my_strcmp(a, b) == 0);
    assert(my_strcmp(a, c) < 0);
    assert(my_strcmp(c, b) > 0);
    printf("%s\n", "my_strcmp test succesfully passed!");
}

void test_strcpy() {
    char a[] = "kekek";
    char b[] = "kekes";
    assert(my_strcmp(my_strcpy(a, b), "kekes") == 0);
    printf("%s\n", a);
    printf("%s\n", b);
    assert(my_strcmp(my_strcpy(a, ""), "") == 0);
    printf("%s\n", "my_strcpy test succesfully passed!");
}

void test_strlen() {
    char *a = "HI!";
    char *b = "Hello!";
    char *c = "";
    assert(my_strlen(a) == 3);
    assert(my_strlen(b) == 6);
    assert(my_strlen(c) == 0);
    printf("%s\n", "my_strlen test succesfully passed!");
}

void test_strcat() {
    char a[] = "kekek";
    char b[] = "kekes";
    char c[] = "";
    assert(my_strcmp(my_strcat(a, b), "kekekkekes") == 0);
    assert(my_strcmp(my_strcat(c, a), "kekekkekes") == 0);
    printf("%s\n", "my_strcat test succesfully passed!");
}
