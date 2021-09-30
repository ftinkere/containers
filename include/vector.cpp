//
// Created by Frey Tinkerer on 9/23/21.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <memory>

#include "iterator.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/vector
 *  TODO:
 *
 *  constructor				// done
 *  destructor				// done
 *  assign					// done
 *  operator=				// done
 *  get_allocator			// done
 *
 *  at						// done
 *  operator[]				// done
 *  front					// done
 *  back					// done
 *  data					// done
 *
 *  iterators: begin, end	// done
 *
 *  empty					// done
 *  size					// done
 *  max_size				// done
 *  reserve					// done
 *  capacity				// done
 *
 *  clear					// done
 *  insert
 *  erase
 *  push_back
 *  pop_back
 *  resize
 *  swap, std::swap
 *
 *  operator==
 *  operator!=
 *  operator<
 *  operator<=
 *  operator>
 *  operator>=
 *
 */


template<class T, class Allocator = std::allocator<T> >
class vector {
public:
	typedef T value_type;
// TODO:	typedef Allocator	allocator_type;
	typedef std::allocator<T> allocator_type;

	static_assert((is_same<typename allocator_type::value_type, value_type>::value),
				  "Allocator::value_type must be same type as value_type");

	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;

	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;

	typedef vector<value_type, allocator_type> vector_type;

	typedef normal_iterator<pointer, vector_type> iterator;
	typedef normal_iterator<const_pointer, vector_type> const_iterator;
	typedef reverse_iterator<const_pointer, vector_type> const_reverse_iterator;
	typedef reverse_iterator<pointer, vector_type> reverse_iterator;

protected:
	allocator_type _allocator;
	pointer _start;
	pointer _end;
	pointer _end_cap;

public:

	/**
	 * @brief Default constructor.
	 */
	explicit vector(const allocator_type &allocator = allocator_type()) :
			_allocator(allocator),
			_start(nullptr),
			_end(nullptr),
			_end_cap(nullptr) {};

	/**
	 *  @brief  Creates a new vector and fill it.
	 *  @param  n  The number of elements to initially create.
	 *  @param  value  An element to copy.
	 */
	explicit vector(size_type n,
					value_type const &value = value_type(),
					const allocator_type &allocator = allocator_type()) :
			_allocator(allocator) {
		_pre_allocate(n);
		_construct_from_start_by_value(n, value);
	};

	// TODO: enable_if, is_integral
	// TODO: iterator constructor. Need to differentiate between (n, value)
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
		_start = nullptr;
		_end = nullptr;
		_end_cap = nullptr;
	}

	// TODO: optimize for count < cap
	void assign(size_type count, value_type const &value) {

		_clear_deloc();
		_pre_allocate(count);

		_construct_from_start_by_value(count, value);
	}

	// TODO: optimize for new_size < cap
	template<class Iter>
	void assign(Iter first,
				typename enable_if<!is_integral<Iter>::value, Iter>::type last) {

		_clear_deloc();
		_pre_allocate(last - first);
		_construct_from_start_by_iter(first, last);
	}

	vector_type &operator=(vector_type const &other) {
		this->assign(other.begin(), other.end());
		return *this;
	}

	allocator_type get_allocator() const {
		return _allocator;
	}


	reference at(size_type pos) {
		if (pos >= size()) {
			throw std::out_of_range("vector");
		}
		return _start[index];
	}

	const_reference at(size_type pos) const {
		if (pos >= size()) {
			throw std::out_of_range("vector");
		}
		return _start[index];
	}

	reference operator[](size_type index) {
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
		return iterator(_end);;
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

	reverse_iterator rbegin() {
		return reverse_iterator(_end);
	}

	reverse_iterator rend() {
		return reverse_iterator(_start);;
	}

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(_end);
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(_start);
	}

	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(_end);
	}

	const_reverse_iterator crend() const {
		return const_reverse_iterator(_start);
	}


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
			throw std::length_error("reserve");
		}
		if (new_cap > capacity()) {
			vector_type tmp(begin(), end());

			_clear_deloc();
			_pre_allocate(new_cap);
			_construct_from_start_by_iter(tmp.begin(), tmp.end());
		}
	}

	void clear() {
		if (_start != nullptr) {
			for (pointer p = _start; p != _end; ++p) {
				_allocator.destroy(p);
			}
			_end = _start;
		}
	}

protected:

	void _pre_allocate(size_type n) {
		_start = _allocator.allocate(n);
		_end = _start;
		_end_cap = _start + n;
	}

	void _clear_deloc() {
		if (_start != nullptr) {
			for (pointer p = _start; p != _end; ++p) {
				_allocator.destroy(p);
			}
			_allocator.deallocate(_start, _end_cap - _start);
			_start = nullptr;
			_end = nullptr;
			_end_cap = nullptr;
		}
	}

	template <typename Iter>
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


	void _construct_from_start_by_value(size_type n, value_type const& value) {
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

};


#endif //CONTAINERS_VECTOR_HPP
