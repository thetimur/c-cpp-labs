#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int r, const char *_label) : Figure(id, x, y), r(r) {
    label = new char [std::strlen(_label) + 1];
    std::strcpy((char*)label, _label);
}

Circle::~Circle() {
    delete [] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d r = %d label = %s\n", id, x, y, r, label);
}

bool Circle::is_inside(int _x, int _y) const {
    return (_x - x) * (_x - x) + (_y - y) * (_y - y) <= r * r;
}

void Circle::zoom(int zoom_power) {
    r *= zoom_power;
}