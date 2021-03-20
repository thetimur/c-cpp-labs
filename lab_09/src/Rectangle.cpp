#include "Rectangle.hpp"


Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int _x, int _y) const {
	return 2 * abs(x - _x) <= width && 2 * abs(x - _x) <= height;
}

void Rectangle::zoom(int zoom_power) {
	width *= zoom_power;
	height *= zoom_power;
}