//
// Created by Frey Tinkerer on 10/8/21.
//

#ifndef CONTAINERS_CMP_HPP
#define CONTAINERS_CMP_HPP

namespace ft {
template<typename Iter1, typename Iter2>
bool equal(Iter1 first1, Iter1 last1,
		   Iter2 first2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (*first1 != *first2) {
			return false;
		}
	}
	return true;
}

template<typename Iter1, typename Iter2, typename BinaryPredicate>
bool equal(Iter1 first1, Iter1 last1,
		   Iter2 first2, BinaryPredicate p) {
	for (; first1 != last1; ++first1) {
		if (!p(*first1, *first2)) {
			return false;
		}
	}
	return true;
}

template<typename Iter1, typename Iter2>
bool equal(Iter1 first1, Iter1 last1,
		   Iter2 first2, Iter2 last2) {
	if (last1 - first1 != last2 - first2) {
		return false;
	}
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (*first1 != *first2) {
			return false;
		}
	}
	return true;
}

template<typename Iter1, typename Iter2, typename BinaryPredicate>
bool equal(Iter1 first1, Iter1 last1,
		   Iter2 first2, Iter2 last2,
		   BinaryPredicate p) {
	if ((last1 - first1) != (last2 - first2)) {
		return false;
	}
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (!p(*first1, *first2)) {
			return false;
		}
	}
	return true;
}


template<class Iter1, class Iter2>
bool lexicographical_compare(Iter1 first1, Iter1 last1,
							 Iter2 first2, Iter2 last2) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
		if (*first1 < *first2) { return true; }
		if (*first2 < *first1) { return false; }
	}
	return (first1 == last1) && (first2 != last2);
}

template<class Iter1, class Iter2, class Compare>
bool lexicographical_compare(Iter1 first1, Iter1 last1,
							 Iter2 first2, Iter2 last2,
							 Compare comp) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
		if (comp(*first1, *first2)) { return true; }
		if (comp(*first2, *first1)) { return false; }
	}
	return (first1 == last1) && (first2 != last2) ;
}

}

#endif //CONTAINERS_CMP_HPP
