//
// Created by Frey Tinkerer on 9/23/21.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <memory>
#include <algorithm>

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
 *  insert					// done?
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
			throw std::out_of_range("Vector out of range.");
		}
		return _start[index];
	}

	const_reference at(size_type pos) const {
		if (pos >= size()) {
			throw std::out_of_range("Vector out of range.");
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
		if (_start != nullptr) {
			for (pointer p = _start; p != _end; ++p) {
				_allocator.destroy(p);
			}
			_end = _start;
		}
	}

	iterator insert(iterator pos, value_type const& value) {
		size_type index = pos - begin();

		if (_end == _end_cap) {
			_grow_capacity();
		}
		pointer p = _start + index;

		if (p < _end) {
			_allocator.construct(_end, *(_end - 1));
			for (pointer pm = _end - 1; pm > p; pm--) {
				*pm = *(pm - 1);
			}
			*p = value;
			++_end;
		} else if (p == _end) {
			_allocator.construct(_end, value);
			++_end;
		} else {
			throw std::out_of_range("Invalid iterator in insert.");
		}

		return iterator(p);
	}

	// TODO: fix pos == begin
	iterator insert(iterator pos, size_type count, value_type const& value) {
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
			size_type shift_len = count <= b_end - p ? count : b_end - p;
			_construct_from_by_iter(b_end + count - shift_len, b_end - shift_len, b_end);
			for (pointer pm = b_end - shift_len; pm < b_end; ++pm) {
				*pm = value;
			}
			for (pointer pm = b_end; pm < b_end + count - shift_len; ++pm) {
				_allocator.construct(pm, value);
			}
			_end = b_end + count;
		} else if (p == _end) {
			_construct_from_by_value(_end, count, value);
		} else {
			throw std::out_of_range("Invalid iterator in insert.");
		}

		return iterator(p);
	}

	template <typename Iter>
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
		pointer b_end = _end;

		if (p < b_end) {
			Iter cur_iter = first;
			size_type shift_len = count <= b_end - p ? count : b_end - p;

			_construct_from_by_iter(b_end + count - shift_len, b_end - shift_len, b_end);
			for (pointer pm = b_end - shift_len; pm < b_end; ++pm, ++cur_iter) {
				*pm = *cur_iter;
			}
			for (pointer pm = b_end; pm < b_end + count - shift_len; ++pm, ++cur_iter) {
				_allocator.construct(pm, *cur_iter);
			}
			_end = b_end + count;
		} else if (p == _end) {
			_construct_from_by_iter(_end, first, last);
		} else {
			throw std::out_of_range("Invalid iterator in insert.");
		}

		return iterator(p);
	}


	void swap(vector_type& other) {
		std::swap(this->_start, other._start);
		std::swap(this->_end, other._end);
		std::swap(this->_end_cap, other._end_cap);

		if (std::allocator_traits<allocator_type>::propagate_on_container_swap::value) {
			_VSTD::swap(this->_allocator, other._allocator);
		}
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

	template <typename Iter>
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

	void _construct_from_by_value(pointer from, size_type n, value_type const& value) {
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


#endif //CONTAINERS_VECTOR_HPP
