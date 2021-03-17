#include <stdio.h>

#include "Scheme.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"


int main() {
    Scheme scheme(10);

    printf("initialized!\n");

    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    printf("Add rect!\n");
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle1"));


    printf("Add circ!\n");


    scheme.print_all_figures();

    Figure* found = scheme.is_inside_figure(5, 5);
    if (found != nullptr) {
        found->print();
    } else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();

    return 0;
}
