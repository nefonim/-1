#pragma once

#include <algorithm>
#include <cstddef>

template<class T>
struct Array {
	T *ptr;
	size_t len;

	Array(size_t len) : ptr(new T[len]), len(len) {}

	Array(const Array &other) : Array(other.len) {
		std::copy(other.ptr, other.ptr + other.len, this->ptr);
	}

	Array(Array &&other) : ptr(other.ptr), len(other.len) {
		other.ptr = nullptr;
	}

	~Array() {
		delete[] this->ptr;
	}
};
