#include "Figure.hpp"

#include <cstdio>
#include <cstddef>

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    void print() const override;
    bool is_inside(int _x, int _y) const override;
    void zoom(int zoom_power) override;

private:
	int width, height;
};
