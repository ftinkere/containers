#include <iostream>
#include <vector>
#include <iomanip>

#include "vector.hpp"



const std::string green_color = "\033[0;32m";
const std::string yellow_color = "\033[1;33m";
const std::string reset_color = "\033[0m";
const std::string green_arrow_right = green_color + "==> " + reset_color;
const std::string green_arrow_left = green_color + " <==" + reset_color;

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
//
//	{
//		int ints[] = {0, 1, 2, 3, 4, 5};
//		::vector<int> a(ints, ints + 6);
//		::vector<int> b;
//
//		b.assign(10, 3);
//
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		b = a;
//
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		b.assign(a.rbegin(), a.rend());
//
//		std::cout << "r:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		std::cout << "a:";
//		for (::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		std::cout << "Capacity b: "<< b.capacity() << " size b: " << b.size() << std::endl;
//		b.reserve(10);
//		std::cout << "Reserve for b 10, new capacity: " << b.capacity() << " size b: " << b.size() << std::endl;
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
//		b.clear();
//		std::cout << "Clear b. Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;
//
//		b.insert(b.begin(), 0);
//		b.insert(b.begin() + 1, 1);
//		b.insert(b.begin(), -1);
//		for (int i = 3; i < 10; ++i) {
//			b.insert(b.begin() + i, i);
//		}
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//		std::cout << "Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;
//
//		b.clear();
//		b.insert(b.end(), 0);
//		b.insert(b.end(), 1);
//		b.insert(b.end(), 2);
//
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//
////		b.insert(b.begin() + 3, 10, -21);
//		b.insert(b.begin(), a.begin(), a.end());
//
//		b.erase(b.begin() + 5);
//
//		std::cout << "b:";
//		for (::vector<int>::iterator it = b.begin(); it != b.end(); ++it) {
//			std::cout << " " << *it;
//		}
//		std::cout << std::endl;
//		std::cout << "Size b: " << b.size() << " capacity b: " << b.capacity() << std::endl;
//
//	}
//	std::cout << std::endl;

	{
		std::vector<int>	stdvec;
		::vector<int>		ftvec;

		stdvec.reserve(10);
		ftvec.reserve(10);

		std::cout << "\t"
				  << green_arrow_right
				  << "Insertion"
				  << green_arrow_left
				  << std::endl;
		for (int i = 0; i < 10; ++i) {
			std::vector<int>::iterator stdit = stdvec.insert(stdvec.end(), i);
			::vector<int>::iterator ftit = ftvec.insert(ftvec.end(), i);

			std::cout << "std base: " << stdit.base()
					  << " std val: " << *stdit
					  << std::endl;
			std::cout << "ft  base: " << ftit.base()
					  << " ft  val: " << *ftit
					  << std::endl
					  << std::endl;
		}

		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Removing"
				  << green_arrow_left
				  << std::endl;
		for (int i = 0; i < 5; ++i) {
			std::vector<int>::iterator stdit = stdvec.erase(stdvec.begin(), stdvec.begin() + 2);
			::vector<int>::iterator ftit = ftvec.erase(ftvec.begin(), ftvec.begin() + 2);

			if (stdit != stdvec.end()) {
				std::cout << "std base: " << stdit.base()
						  << " std val: " << *stdit
						  << std::endl;
			} else {
				std::cout << "std base: " << stdit.base()
						  << " std val: " << "{end}"
						  << std::endl;
			}
			if (ftit != ftvec.end()) {
				std::cout << "ft  base: " << ftit.base()
						  << " ft  val: " << *ftit
						  << std::endl
						  << std::endl;
			} else {
				std::cout << "ft  base: " << ftit.base()
						  << " ft  val: " << "{end}"
						  << std::endl
						  << std::endl;
			}
		}

		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Pushing"
				  << green_arrow_left
				  << std::endl;
		for (int i = 0; i < 10; ++i) {
			stdvec.push_back(i);
			ftvec.push_back(i);
		}

		std::cout << "\t"
				  << green_arrow_right
				  << "Pop back 3 times"
				  << green_arrow_left
				  << std::endl;
		for (int i = 0; i < 3; ++i) {
			stdvec.pop_back();
			ftvec.pop_back();
		}

		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Resize to 5"
				  << green_arrow_left
				  << std::endl;
		stdvec.resize(5);
		ftvec.resize(5);
		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Resize to 8 with default"
				  << green_arrow_left
				  << std::endl;
		stdvec.resize(8);
		ftvec.resize(8);
		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Resize to 10 with 21"
				  << green_arrow_left
				  << std::endl;
		stdvec.resize(10, 21);
		stdvec.resize(10, 21);
		ftvec.resize(10, 21);
		ftvec.resize(10, 21);
		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::vector<int> stdtmp;
		stdtmp.push_back(42);
		std::swap(stdtmp, stdvec);

		::vector<int> fttmp;
		fttmp.push_back(42);
		std::swap(fttmp, ftvec);

		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Equal"
				  << green_arrow_left
				  << std::endl;
		std::cout << std::boolalpha << ::equal(stdvec.begin(), stdvec.end(), ftvec.begin()) << ", other way: ";
		std::cout << std::boolalpha << ::equal(stdvec.begin(), stdvec.end(), ftvec.begin(), ftvec.end()) << std::endl;
		std::cout << "after push 0 to ft: ";
		ftvec.push_back(0);
		std::cout << std::boolalpha << ::equal(stdvec.begin(), stdvec.end(), ftvec.begin(), ftvec.end()) << std::endl;
		std::cout << std::endl;

		std::swap(stdtmp, stdvec);
		std::swap(fttmp, ftvec);
		std::cout << "\t"
				  << green_arrow_right
				  << "std vec"
				  << green_arrow_left
				  << std::endl;
		for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		::vector<int> cpvec(stdvec.begin(), stdvec.end());
		std::cout << "\t"
				  << green_arrow_right
				  << "Lexicographical compare"
				  << green_arrow_left
				  << std::endl;
		std::cout << "cpvec < ftvec: " << std::boolalpha << (cpvec < ftvec) << std::endl;
		std::cout << "cpvec <= ftvec: " << std::boolalpha << (cpvec <= ftvec) << std::endl;
		std::cout << "cpvec > ftvec: " << std::boolalpha << (cpvec > ftvec) << std::endl;
		std::cout << "cpvec >= ftvec: " << std::boolalpha << (cpvec >= ftvec) << std::endl;

		cpvec.push_back(0);
		ftvec.push_back(1);

		std::cout << "\t"
				  << green_arrow_right
				  << "cp  vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = cpvec.begin(); it != cpvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "\t"
				  << green_arrow_right
				  << "ft vec"
				  << green_arrow_left
				  << std::endl;
		for (::vector<int>::iterator it = ftvec.begin(); it != ftvec.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "\t"
				  << green_arrow_right
				  << "Lexicographical compare"
				  << green_arrow_left
				  << std::endl;
		std::cout << "cpvec < ftvec: " << std::boolalpha << (cpvec < ftvec) << std::endl;
		std::cout << "cpvec <= ftvec: " << std::boolalpha << (cpvec <= ftvec) << std::endl;
		std::cout << "cpvec > ftvec: " << std::boolalpha << (cpvec > ftvec) << std::endl;
		std::cout << "cpvec >= ftvec: " << std::boolalpha << (cpvec >= ftvec) << std::endl;

	}
	std::cout << std::endl;


	return 0;
}
