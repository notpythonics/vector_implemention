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

	T& operator[](int i) { return elem[i]; }
	const T& operator[](int i) const { return elem[i]; }

	void reserve(int new_allocation) {
		if (new_allocation <= space) return;

		T* ptr = allocator.allocate(new_allocation);
		for (int i = 0; i < sz; ++i) ptr[i] = elem[i];
		for (int i = 0; i < sz; ++i) allocator.destroy(&elem[i]);
		allocator.deallocate(elem, space);
		elem = ptr;
		space = new_allocation;
	}

	void push_back(const T& val) {
		if (sz == space) reserve(space + 1);

		allocator.construct(&elem[sz], val);
		++sz;
	}

	int size() { return sz; }
	int capacity() { return space; }
};

#endif