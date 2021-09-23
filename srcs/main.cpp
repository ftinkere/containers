#include <iostream>
#include <vector>

#include "vector.hpp"

int main() {
//	{
//		std::vector<int> a(5, 1);
//		::vector<int> b(5, 1);
//
//		std::cout << "a[2]: " << a[2] << std::endl;
//		std::cout << "a[4]: " << a[4] << std::endl;
//		std::cout << "b[2]: " << b[2] << std::endl;
//		std::cout << "b[4]: " << b[4] << std::endl;
//	}
//	std::cout << std::endl;
//
//	{
//		int ints[] = {0, 1, 2, 3, 4, 5};
//		std::vector<int> a(ints, ints + 6);
//		::vector<int> b(ints, ints + 6);
//
//		std::cout << "a[2]: " << a[2] << std::endl;
//		std::cout << "a[4]: " << a[4] << std::endl;
//		std::cout << "b[2]: " << b[2] << std::endl;
//		std::cout << "b[4]: " << b[4] << std::endl;
//	}
//	std::cout << std::endl;

	{
		int ints[] = {0, 1, 2, 3, 4, 5};
		::vector<int> a(ints, ints + 6);
		::vector<int> b(a);

		std::cout << "a[2]: " << a[2] << std::endl;
		std::cout << "a[4]: " << a[4] << std::endl;
		std::cout << "b[2]: " << b[2] << std::endl;
		std::cout << "b[4]: " << b[4] << std::endl;
	}
	std::cout << std::endl;


	return 0;
}
