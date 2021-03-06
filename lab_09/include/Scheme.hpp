#pragma once

#include "Figure.hpp"
#include <cstdio>
#include <cstddef>
#include <cassert>
#include <algorithm>

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures() const;
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y) const; // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);
    int find_by_id(int id) const;

private:

    std::size_t capacity = 0;
    std::size_t size = 0;
    Figure** figures_; // размер массива задается в конструкторе и больше не растет
};
