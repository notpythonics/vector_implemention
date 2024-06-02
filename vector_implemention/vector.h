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

	vector(const vector& arg) {
		elem = allocator.allocate(arg.sz);
		for (int i = 0; i < arg.sz; ++i) allocator.construct(&elem[i], arg.elem[i]);
		space = sz = arg.sz;
	}

	vector(vector&& arg) : sz{ arg.sz }, space{ arg.space } {
		elem = arg.elem;
		arg.elem = nullptr;
	}

	T& operator=(const vector& arg) {
		if (space >= arg.space) {
			for (int i = 0; i < sz; ++i) allocator.destroy(&elem[i]);
			for (int i = 0; i < arg.sz; ++i) allocator.construct(&elem[i], arg.elem[i]);
			return;
		}

		for (int i = 0; i < sz; ++i) allocator.destroy(&elem[i]);
		allocator.deallocate(elem, space);

		T* ptr = allocator.allocate(arg.sz);
		for (int i = 0; i < arg.sz; ++i) allocator.construct(&ptr[i], arg.elem[i]);
		elem = ptr;
		space = sz = arg.sz;
		return *this;
	}

	T& operator=(vector&& arg) {
		for (int i = 0; i < sz; ++i) allocator.destroy(&elem[i]);
		allocator.deallocate(elem, space);

		elem = arg.elem;
		sz = arg.sz;
		space = arg.space;
		arg.elem = nullptr;
	}

	T& operator[](int i) { return elem[i]; }
	const T& operator[](int i) const { return elem[i]; }

	void reserve(int new_allocation) {
		if (new_allocation <= space) return;

		T* ptr = allocator.allocate(new_allocation);
		for (int i = 0; i < sz; ++i) allocator.construct(&ptr[i], elem[i]);
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

	T& at(int i) {
		if (!(i > -1 && i < space))
			throw std::out_of_range{"out of range accses uwu"};
		return elem[i];
	}

	const T& at(int i) const {
		if (!(i > -1 && i < space))
			throw std::out_of_range{ "out of range accses uwu" };
		return elem[i];
	}

	int size() { return sz; }
	int capacity() { return space; }
};

#endif