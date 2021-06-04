#include "Scheme.hpp"

Scheme::Scheme(int capacity) : capacity(capacity), size(0) {
    figures_ = new Figure* [capacity];
    std::fill(figures_, figures_ + capacity, nullptr);
}

Scheme::~Scheme() {
    for (std::size_t i = 0; i < capacity; i++) {
        delete figures_[i];
        figures_[i] = nullptr;
    }
    delete [] figures_;
    figures_ = nullptr;
}

void Scheme::push_back_figure(Figure* fg) {
    figures_[size] = fg;
    size++;
}

int Scheme::find_by_id(int id) const {
    for (std::size_t i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id) {
            return i;
        }
    }
    return -1;
}

void Scheme::remove_figure(int id) {
    int index = find_by_id(id);
    for (std::size_t i = index; i < size - 1; i++) {
        std::swap(figures_[i], figures_[i + 1]);
    }
    size--;
    delete figures_[size];
    figures_[size] = nullptr;
}

void Scheme::print_all_figures() const {
    for (std::size_t i = 0; i < size; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int zoom_power) {
    int index = find_by_id(id);
    assert(index != -1);
    figures_[index]->zoom(zoom_power);
}

Figure* Scheme::is_inside_figure(int x, int y) const {
    for (std::size_t i = 0; i < size; i++) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    int index = find_by_id(id);
    assert(index != -1);
    figures_[index]->move(new_x, new_y);
}
