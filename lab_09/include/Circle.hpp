#pragma once

#include "Figure.hpp"
#include <cstdio>
#include <cstddef>
#include <cstring>

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int r, const char* label);
    ~Circle();

    void print() const override;
    bool is_inside(int _x, int _y) const override;
    void zoom(int zoom_power) override;

private:
    const char* label;
    int r;
};
