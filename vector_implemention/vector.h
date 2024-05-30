#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

template<typename T, typename A = std::allocator<T>>
class vector {
	int sz;
	A allocator;

};

#endif