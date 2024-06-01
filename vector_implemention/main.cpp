#include <iostream>
#include "vector.h"

int main() {
	vector<int> v;
	v.reserve(1);
	v[0] = 1;
	std::cout << v.at(0) << '\n';

	//std::cout << v.at(-99) << '\n';
}