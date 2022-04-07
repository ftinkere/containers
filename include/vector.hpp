//
// Created by Frey Tinkerer on 9/23/21.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <memory>
#include <algorithm>

#include "iterator.hpp"
#include "cmp.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/vector
 *  TODO:
 *
 *  constructor					// done
 *  destructor					// done
 *  assign						// done
 *  operator=					// done
 *  get_allocator				// done
 *
 *  at							// done
 *  operator[]					// done
 *  front						// done
 *  back						// done
 *  data						// done
 *
 *  iterators: begin, end		// done
 *
 *  empty						// done
 *  size						// done
 *  max_size					// done
 *  reserve						// done
 *  capacity					// done
 *
 *  clear						// done
 *  insert						// done
 *  erase						// done
 *  push_back					// done
 *  pop_back					// done
 *  resize						// done
 *  swap, std::swap				// done
 *
 * std::equal					// done
 * std::lexicographical_compare	// done
 *  operator==					// done
 *  operator!=					// done
 *  operator<					// done
 *  operator<=					// done
 *  operator>					// done
 *  operator>=					// done
 *
 */

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
	// TODO:	typedef Allocator	allocator_type;
		typedef std::allocator<T> allocator_type;

	//	static_assert((is_same<typename allocator_type::value_type, value_type>::value),
	//			"Allocator::value_type must be same type as value_type");

		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef vector<value_type, allocator_type>			vector_type;

		typedef base_iterator<value_type>					iterator;
		typedef base_iterator<const value_type>				const_iterator;
//		typedef reverse_base_iterator<value_type, false>	reverse_iterator;
//		typedef reverse_base_iterator<value_type, true>		const_reverse_iterator;
	protected:
		allocator_type _allocator;
		pointer _start;
		pointer _end;
		pointer _end_cap;

	public:

		/**
		 * @brief Default constructor.
		 */
		vector(const allocator_type &allocator = allocator_type()) :
				_allocator(allocator),
				_start(0),
				_end(0),
				_end_cap(0) {};

		/**
		 *  @brief  Creates a new vector and fill it.
		 *  @param  n  The number of elements to initially create.
		 *  @param  value  An element to copy.
		 */
		vector(size_type n,
						value_type const &value = value_type(),
						const allocator_type &allocator = allocator_type()) :
				_allocator(allocator) {
			_pre_allocate(n);
			_construct_from_start_by_value(n, value);
		};

		/**
		 *  @brief  Creates a new vector and fill it by iterators.
		 *  @param  first  Begin iterator.
		 *  @param  last  End iterator.
		 */
		template<class Iter>
		vector(Iter first,
			   typename enable_if<!is_integral<Iter>::value,
					   Iter>::type last,
			   const allocator_type &allocator = allocator_type()) :
				_allocator(allocator) {
			_pre_allocate(last - first);
			_construct_from_start_by_iter(first, last);
		}


		/**
		 * @brief Copy constructor
		 */
		vector(vector_type const &other) :
				_allocator(other._allocator) {

			_pre_allocate(other.capacity());
			_construct_from_start_by_iter(other.begin(), other.end());
		}


		virtual ~vector() {
			for (pointer p = _start; p != _end; ++p) {
				_allocator.destroy(p);
			}
			_allocator.deallocate(_start, _end_cap - _start);
			_start = 0;
			_end = 0;
			_end_cap = 0;
		}

		// TODO: optimize for count < cap
		void assign(size_type count, value_type const &value) {

			_clear_deloc();
			_pre_allocate(count);

			_construct_from_start_by_value(count, value);
		}

		//TODO: optimize for new_size < cap
		template<class Iter>
		void assign(Iter first,
					typename enable_if<!is_integral<Iter>::value, Iter>::type last) {

			_clear_deloc();
			_pre_allocate(last - first);
			_construct_from_start_by_iter(first, last);
		}

		vector& operator=(vector_type const &other) {
			this->assign(other.begin(), other.end());
			return *this;
		}

		allocator_type get_allocator() const {
			return _allocator;
		}


		reference at(size_type pos) {
			if (pos >= size()) {
				throw std::out_of_range("Vector out of range.");
			}
			return _start[pos];
		}

		const_reference at(size_type pos) const {
			if (pos >= size()) {
				throw std::out_of_range("Vector out of range.");
			}
			return _start[pos];
		}

		reference operator[](size_type index) {
			return _start[index];
		};
		const_reference operator[](size_type index) const {
			return _start[index];
		};

		reference front() {
			return *begin();
		}

		const_reference front() const {
			return *begin();
		}

		reference back() {
			return *(end() - 1);
		}

		const_reference back() const {
			return *(end() - 1);
		}

		pointer data() {
			return pointer(_start);
		}

		const_pointer data() const {
			return const_pointer(_start);
		}


		iterator begin() {
			return iterator(_start);
		}

		iterator end() {
			return iterator(_end);
		}

		const_iterator begin() const {
			return const_iterator(_start);
		}

		const_iterator end() const {
			return const_iterator(_end);
		}

		const_iterator cbegin() const {
			return const_iterator(_start);
		}

		const_iterator cend() const {
			return const_iterator(_end);
		}

//		reverse_iterator rbegin() {
//			return reverse_iterator(_end - 1);
//		}
//
//		reverse_iterator rend() {
//			return reverse_iterator(_start - 1);
//		}
//
//		const_reverse_iterator rbegin() const {
//			return const_reverse_iterator(_end - 1);
//		}
//
//		const_reverse_iterator rend() const {
//			return const_reverse_iterator(_start - 1);
//		}
//
//		const_reverse_iterator crbegin() const {
//			return const_reverse_iterator(_end - 1);
//		}
//
//		const_reverse_iterator crend() const {
//			return const_reverse_iterator(_start - 1);
//		}



		bool empty() const {
			return _start == _end;
		}

		size_type size() const {
			return _end - _start;
		}

		size_type max_size() const {
			return _allocator.max_size();
		}

		size_type capacity() const {
			return _end_cap - _start;
		}

		void reserve(size_type new_cap) {
			if (new_cap > max_size()) {
				throw std::length_error("Can't reserve more than max size.");
			}
			if (new_cap > capacity()) {
				vector_type tmp(begin(), end());

				_clear_deloc();
				_pre_allocate(new_cap);
				_construct_from_start_by_iter(tmp.begin(), tmp.end());
			}
		}

		void clear() {
			if (_start != 0) {
				for (pointer p = _start; p != _end; ++p) {
					_allocator.destroy(p);
				}
				_end = _start;
			}
		}

		iterator insert(iterator pos, value_type const &value) {
			return insert(pos, 1, value);
		}

		iterator insert(iterator pos, size_type count, value_type const &value) {
			if (count == 0) {
				return pos;
			}
			size_type index = pos - begin();

			while (_end - 1 + count >= _end_cap) {
				_grow_capacity();
			}
			pointer p = _start + index;
			pointer b_end = _end;

			if (p < b_end) {
				if (p + count >= b_end) {
					_construct_from_by_iter(p + count, p, b_end);
					_construct_from_by_value(b_end, p + count - b_end, value);
					for (pointer pm = p; pm < b_end; ++pm) {
						*pm = value;
					}
				} else {
					_construct_from_by_iter(b_end, b_end - count, b_end);
					for (pointer pm = b_end - 1; pm >= p + count; --pm) {
						*pm = *(pm - count);
					}
					for (pointer pm = p; pm < p + count; ++pm) {
						*pm = value;
					}
				}
				_end = b_end + count;
			} else if (p == _end) {
				_construct_from_by_value(_end, count, value);
			} else {
				throw std::out_of_range("Invalid iterator in insert.");
			}

			return iterator(p);
		}

		template<typename Iter>
		iterator insert(iterator pos,
						Iter first,
						typename enable_if<!is_integral<Iter>::value, Iter>::type last) {
			if (first == last) {
				return pos;
			}
			size_type index = pos - begin();
			size_type count = last - first;

			while (_end - 1 + count >= _end_cap) {
				_grow_capacity();
			}
			pointer p = _start + index;

			for (Iter it = last - 1; it != first - 1; --it) {
				insert(iterator(p), *it);
			}

			return iterator(p);
		}


		iterator erase(iterator pos) {
			if (pos >= end()) {
				throw std::out_of_range("Invalid iterator in erase.");
			}
	//		for (iterator it = pos; it < end() - 1; ++it) {
	//			*it = *(it + 1);
	//		}
	//		_allocator.destroy(_end - 1);
	//		--_end;
	//		return pos;
			return erase(pos, pos + 1);
		}

		iterator erase(iterator first, iterator last) {
			if (last > end() || first < begin()) {
				throw std::out_of_range("Invalid iterator in erase.");
			}
			if (first == last) {
				return last;
			}

			size_type count = last - first;
			for (iterator it = first; it < end() - count; ++it) {
				*it = *(it + count);
			}

			for (size_type i = 0; i < count; ++i) {
				_allocator.destroy(_end - 1);
				--_end;
			}
			return first;
		}


		void push_back(value_type const &value) {
			insert(end(), value);
		}

		void pop_back() {
			erase(end() - 1);
		}

		void resize(size_type new_size) {
			resize(new_size, value_type());
		}

		void resize(size_type new_size, value_type const &value) {
			if (new_size == size()) { return; }
			if (new_size < size()) {
				erase(begin() + new_size, end());
				return;
			}
			while (size_type(_end_cap - _start) < new_size) {
				_grow_capacity();
			}
			_construct_from_by_value(_end, new_size - size(), value);
		}


		void swap(vector_type &other) {
			std::swap(this->_start, other._start);
			std::swap(this->_end, other._end);
			std::swap(this->_end_cap, other._end_cap);

	//		if (std::allocator_traits<allocator_type>::propagate_on_container_swap::value) {
	//			_VSTD::swap(this->_allocator, other._allocator);
	//		}
		}

	protected:
		void _pre_allocate(size_type n) {
			_start = _allocator.allocate(n);
			_end = _start;
			_end_cap = _start + n;
		}

		void _grow_capacity() {
			if (capacity() == max_size()) {
				throw std::length_error("Can't grow vector. Reached max size.'");
			}
			size_type new_len = capacity() == 0 ? 1 : capacity() * 2;
			if (new_len < capacity() || new_len > max_size()) {
				new_len = max_size();
			}
			vector_type tmp;
			tmp._pre_allocate(new_len);
			tmp._construct_from_start_by_iter(begin(), end());
			this->swap(tmp);
		}

		void _clear_deloc() {
			if (_start != 0) {
				for (pointer p = _start; p != _end; ++p) {
					_allocator.destroy(p);
				}
				_allocator.deallocate(_start, _end_cap - _start);
				_start = 0;
				_end = 0;
				_end_cap = 0;
			}
		}

		template<typename Iter>
		void _construct_from_start_by_iter(Iter first, Iter last) {
			pointer cur_ptr = _start;
			try {
				for (Iter cur_iter = first; cur_iter != last; ++cur_iter, ++cur_ptr) {
					_allocator.construct(cur_ptr, *cur_iter);
					++_end;
				}
			} catch (...) {
				for (pointer p = _start; p != cur_ptr; ++p) {
					_allocator.destroy(p);
				}
				throw;
			}
		}

		template<typename Iter>
		void _construct_from_by_iter(pointer from, Iter first, Iter last) {
			pointer cur_ptr = from;
			try {
				for (Iter cur_iter = first; cur_iter != last; ++cur_iter, ++cur_ptr) {
					_allocator.construct(cur_ptr, *cur_iter);
					++_end;
				}
			} catch (...) {
				for (pointer p = from; p != cur_ptr; ++p) {
					_allocator.destroy(p);
				}
				throw;
			}
		}

	//	template <typename Iter>
	//	void _r_construct_from_by_iter(pointer from, Iter first, Iter last) {
	//		pointer cur_ptr = from + (last - first);
	//		try {
	//			for (Iter cur_iter = last - 1; cur_iter != first - 1; --cur_iter, --cur_ptr) {
	//				_allocator.construct(cur_ptr, *cur_iter);
	//				++_end;
	//			}
	//		} catch (...) {
	//			for (pointer p = from + (last - first); p != cur_ptr; --p) {
	//				_allocator.destroy(p);
	//			}
	//			throw;
	//		}
	//	}


		void _construct_from_start_by_value(size_type n, value_type const &value) {
			pointer cur = _start;
			try {
				for (; n > 0; --n, ++cur) {
					_allocator.construct(cur, value);
					++_end;
				}
			} catch (...) {
				for (pointer p = _start; p < cur; ++p) {
					_allocator.destroy(p);
				}
				throw;
			}
		}

		void _construct_from_by_value(pointer from, size_type n, value_type const &value) {
			pointer cur = from;
			try {
				for (; n > 0; --n, ++cur) {
					_allocator.construct(cur, value);
					++_end;
				}
			} catch (...) {
				for (pointer p = from; p < cur; ++p) {
					_allocator.destroy(p);
				}
				throw;
			}
		}

	};

//	namespace std {
		template<typename T, typename Allocator>
		void swap(ft::vector<T, Allocator> &x, ft::vector<T, Allocator> &y) {
			x.swap(y);
		}
//	}

	template<typename T, typename Allocator>
	bool operator==(ft::vector<T, Allocator> const &lhs,
					ft::vector<T, Allocator> const &rhs) {
		return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename T, typename Allocator>
	bool operator!=(ft::vector<T, Allocator> const &lhs,
					ft::vector<T, Allocator> const &rhs) {
		return equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::not_equal_to<T>());
	}

	template<typename T, typename Allocator>
	bool operator<(ft::vector<T, Allocator> const &lhs,
				   ft::vector<T, Allocator> const &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less<T>());
	}

	template<typename T, typename Allocator>
	bool operator<=(ft::vector<T, Allocator> const &lhs,
					ft::vector<T, Allocator> const &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<T>());
	}

	template<typename T, typename Allocator>
	bool operator>(ft::vector<T, Allocator> const &lhs,
				   ft::vector<T, Allocator> const &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater<T>());
	}













	template<typename T, typename Allocator>
	bool operator>=(ft::vector<T, Allocator> const &lhs,
					ft::vector<T, Allocator> const &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater_equal<T>());
	}

}

#endif //CONTAINERS_VECTOR_HPP
