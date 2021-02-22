#include "my_vector.h"
#include <cstdlib>
#include <cassert>

MyVector::MyVector() {
	_sz = 0;
	_cp = 0;
	_data = nullptr;
}

MyVector::MyVector(std::size_t init_capacity) {
	_cp = init_capacity;
	_sz = 0;
	_data = (int*)malloc(sizeof(int) * _cp);
}

MyVector::MyVector(MyVector &from) {
	_cp = from._sz;
	_sz = from._cp;
	_data = (int*)malloc(sizeof(int) * _cp);
	for (int i = 0; i < _sz; i++) {
		_data[i] = from._data[i];
	}
}

void MyVector::operator=(MyVector &from) {
	free(_data);
	_cp = from._sz;
	_sz = from._cp;
	_data = (int*)malloc(sizeof(int) * _cp);
	for (int i = 0; i < _sz; i++) {
		_data[i] = from._data[i];
	}
}

MyVector::~MyVector() {
	free(_data);
	_data = nullptr;
}

void MyVector::set(std::size_t index, int value) {
	assert(index < _sz);
	_data[index] = value;
}

int MyVector::get(std::size_t index) {
	assert(index < _sz);
	return _data[index];
}

std::size_t MyVector::size() {
	return _sz;
}
  	
std::size_t MyVector::capacity() {
	return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
	if (new_capacity < _sz) {
		return;
	}
	_data = (int*)realloc(_data, sizeof(int) * new_capacity);
	_cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
	if (new_size > _cp) {
		reserve(std::max(new_size, 2 * _cp));
	} else {
		reserve(new_size);
	}
	if (_sz < new_size) {
		memset(_data + _sz, 0, sizeof(int) * new_size - _sz);
	}
	_sz = new_size;
}

void MyVector::push_back(int value) {
	if (_sz == _cp) {
		reserve(std::max((std::size_t)1, 2 * _cp));
	}
	_data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
	push_back(value);
	int idx = _sz - 1;
	while (idx != index) {
		std::swap(_data[idx], _data[idx - 1]);
		idx--;
	}
}

void MyVector::erase(std::size_t index) {
	int idx = index;
	while (idx != _sz - 1) {
		std::swap(_data[idx], _data[idx + 1]);
		idx++;
	}
	_sz--;
	_data[_sz] = 0;
}