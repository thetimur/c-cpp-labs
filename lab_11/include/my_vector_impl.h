#include "my_vector.h"

int get_capacity(int need) {
    int capacity_ = 1;
    while (capacity_ < need) {
        capacity_ <<= 1;
    }
    return capacity_;
}

template<typename T>
void containers::my_vector<T>::clear_array() {
    for (std::size_t i = 0; i < size_; i++) {
        ((T*)(array_ + i * sizeof(T)))->~T();
    }
}

template<typename T>
containers::my_vector<T>::my_vector() : capacity_(1), size_(0) {
    array_ = new char[sizeof(T)];
}

template<typename T>
containers::my_vector<T>::my_vector(const my_vector<T> &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    array_ = new char[capacity_ * sizeof(T)];  
    for (std::size_t i = 0; i < size_; i++) {
        new (array_ + i * sizeof(T)) T(*((T*)(v.array_ + i * sizeof(T))));
    }
}

template<typename T>
containers::my_vector<T>::my_vector(std::size_t n) {
    capacity_ = get_capacity(n);
    size_ = n;
    array_ = new char[capacity_ * sizeof(T)];
    for (std::size_t i = 0; i < size_; i++) {
        new (array_ + i * sizeof(T)) T();
    }
}

template<typename T>
containers::my_vector<T>::~my_vector() {
    clear_array();
    size_ = 0;
    capacity_ = 0;
    delete [] array_;
    array_ = nullptr;
}


template<typename T>
containers::my_vector<T>& containers::my_vector<T>::operator = (const my_vector<T> &v) {
    clear_array();

    delete [] array_;

    size_ = v.size_;
    capacity_ = v.capacity_;
    array_ = new char[capacity_ * sizeof(T)];

    for (std::size_t i = 0; i < size_; i++) {
        new (array_ + i * sizeof(T)) T(*((T*)(v.array_ + i * sizeof(T))));
    }
    return *this;
}

template<typename T>
std::size_t containers::my_vector<T>::size() const {
    return size_;
}

template<typename T>
std::size_t containers::my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool containers::my_vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
T& containers::my_vector<T>::operator[](std::size_t index) const {
    return *((T*)(array_ + index * sizeof(T)));
}

template<typename T>
void containers::my_vector<T>::push_back(T t) {
    if (size_ == capacity_) {
        reserve(std::max((std::size_t)1, 2 * capacity_));
    }
    new (array_ + size_ * sizeof(T)) T(t);
    size_++;
}

template<typename T>
void containers::my_vector<T>::pop_back() {
    size_--;
    ((T*)(array_ + size_ * sizeof(T)))->~T();
}

template<typename T>
void containers::my_vector<T>::clear() {
    clear_array();
    size_ = 0;
}

template<typename T>
void containers::my_vector<T>::reserve(std::size_t size) {
    int new_capacity = get_capacity(size);    

    if (new_capacity <= capacity_) {
        return;
    }

    char* temp = array_;
    capacity_ = new_capacity;
    array_ = new char[new_capacity * sizeof(T)];

    std::memcpy(array_, temp, size_ * sizeof(T));

    delete [] temp;
}

template<typename T>
void containers::my_vector<T>::resize(std::size_t new_size) {
    reserve(new_size);
    if (size_ < new_size) {
        for (std::size_t i = size_; i < new_size; i++) {
            new (array_ + i * sizeof(T)) T();
        }
    } else if (new_size < size_) {
        for (std::size_t i = size_ - 1; i >= new_size; i--) {
            ((T*)(array_ + i * sizeof(T)))->~T();
        }   
    }
    size_ = new_size;
}
