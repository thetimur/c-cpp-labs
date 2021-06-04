#include <cassert>
#include <algorithm>
namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t size() const;
    void fill(T elem);
private:
    T data_[N];
};

template<typename T, std::size_t N>
T& my_array<T, N>::at(std::size_t index) {
    assert(index >= 0 && index < N);
    return data_[index];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::at(std::size_t index) const {
    assert(index >= 0 && index < size());
    return data_[index];
}

template<typename T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t index) {
    return data_[index];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
    return data_[index];
}

template<typename T, std::size_t N>
bool my_array<T, N>::empty() const {
    return N == 0;
}

template<typename T, std::size_t N>
std::size_t my_array<T, N>::size() const {
    return N;
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(T elem) {
    std::fill(data_, data_ + N, elem);
}
/*
First part ready, smoke-compile works.
*/
} //namespace lab_13
