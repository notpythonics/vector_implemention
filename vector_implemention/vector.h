#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

template<typename T>
class vector {
	int sz;
	std::allocator<T> allocator;
	T* elem;
	int space;
public:
	vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } {}

	vector(int r, const T& def = T()) : sz{ r }, elem{ allocator.allocate(r) }, space{ r } {
		for (int i = 0; i < r; ++i) allocator.construct(&elem[i], def);
	}

	~vector() {
		for (int i = 0; i < sz; ++i) allocator.destroy(&elem[i]);
		allocator.deallocate(elem, space);
	}
};

#endif