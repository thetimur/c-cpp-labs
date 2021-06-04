#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();
        my_vector(std::size_t n);
        my_vector(const my_vector &other);
        my_vector<T>& operator=(const my_vector &other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T& operator[](std::size_t index) const;

        void push_back(T t);
        void pop_back();
        void clear();
        template<typename U>
        friend std::ostream& operator<< (std::ostream& os, const my_vector<U> &m);

    private:
        void clear_array();
        std::size_t capacity_;
        std::size_t size_;
        char* array_;
    };

    template<typename T>
    std::ostream& operator <<(std::ostream &os, const my_vector<T> &e) {
        for (std::size_t i = 0; i < e.size_; i++) {
            os << *(T*)(e.array_ + i * sizeof(T));
            if (i != e.size_ - 1) {
                os << " ";
            }
        }
        return os;
    }

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
