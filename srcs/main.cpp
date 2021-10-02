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
//
//	{
//		int ints[] = {0, 1, 2, 3, 4, 5};
//		::vector<int> a(ints, ints + 6);
//		::vector<int> b(a);
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
		::vector<int> b;

		b.assign(10, 3);

		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		b = a;

		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		b.assign(a.rbegin(), a.rend());

		std::cout << "r:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "a:";
		for (::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		std::cout << "Capacity b: "<< b.capacity() << " size b: " << b.size() << std::endl;
		b.reserve(10);
		std::cout << "Reserve for b 10, new capacity: " << b.capacity() << " size b: " << b.size() << std::endl;
		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;

		b.clear();
		std::cout << "Clear b. Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;

		b.insert(b.begin(), 0);
		b.insert(b.begin() + 1, 1);
		b.insert(b.begin(), -1);
		for (int i = 3; i < 10; ++i) {
			b.insert(b.begin() + i, i);
		}
		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;

		b.insert(b.end(), a.rbegin(), a.rend());
		b.insert(b.begin(), 10, -21);
//		b.insert(b.begin(), a.rbegin(), a.rend());

		std::cout << "b:";
		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
			std::cout << " " << *it;
		}
		std::cout << std::endl;
		std::cout << "Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;

	}
	std::cout << std::endl;


	return 0;
}
