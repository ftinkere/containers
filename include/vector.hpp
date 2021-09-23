//
// Created by Frey Tinkerer on 9/23/21.
//

#ifndef CONTAINERS_VECTOR_CPP
#define CONTAINERS_VECTOR_CPP

#include <memory>
#include <type_traits>



/////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////

template <class T, class Allocator = std::allocator<T> >
class vector {
protected:
	typedef T			value_type;
// TODO:	typedef Allocator	allocator_type;
	typedef std::allocator<T>	allocator_type;

// TODO:	static_assert(T == allocator_type::type)

	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;

// TODO:	typedef iterator
	typedef pointer iterator;
	typedef const_pointer const_iterator;

	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef vector<value_type, allocator_type> vector_type;

	allocator_type _allocator;
	pointer _start;
	pointer _end;
	pointer _end_cap;

protected:

	void _pre_allocate(size_type n) {
		this->_start = this->_allocator.allocate(n);
		this->_end = this->_start;
		this->_end_cap = this->_start + n;
	}



public:

	/**
	 * @brief Default constructor.
	 */
	explicit vector(const allocator_type&	allocator = allocator_type()) :
			_allocator(allocator),
			_start(nullptr),
			_end(nullptr),
			_end_cap(nullptr) {};

	/**
	 *  @brief  Creates a new vector and fill it.
	 *  @param  n  The number of elements to initially create.
	 *  @param  value  An element to copy.
	 */
	explicit vector(size_type				n,
					value_type const&		value = value_type(),
					const allocator_type&	allocator = allocator_type()) :
			_allocator(allocator) {
		this->_pre_allocate(n);

		pointer cur = this->_start;
		try {
			for (; n > 0; --n, ++cur) {
				this->_allocator.construct(cur, value);
			}
			this->_end = this->_start + n;
		} catch (...) {
			for (pointer p = this->_start; p < cur; ++p) {
				this->_allocator.destroy(p);
			}
			throw;
		}
	};

	// TODO: iterator constructor. Need to differentiate between (n, value)
	/**
	 *  @brief  Creates a new vector and fill it by iterators.
	 *  @param  first  Begin iterator.
	 *  @param  last  End iterator.
	 */
	template <class Iter>
	vector(Iter first,
		   typename std::enable_if<std::is_pointer<Iter>::value, Iter>::type last,
		   const allocator_type& allocator = allocator_type()) :
		   _allocator(allocator) {
		this->_pre_allocate(last - first);


		pointer cur_ptr = this->_start;
		try {
			for (Iter cur_iter = first; cur_iter != last; ++cur_iter, ++cur_ptr) {
				this->_allocator.construct(cur_ptr, *cur_iter);
			}
			this->_end += last - first;
		} catch (...) {
			for (pointer p = this->_start; p != cur_ptr; ++p) {
				this->_allocator.destroy(p);
			}
			throw;
		}
	}


	/**
	 * @brief Copy constructor
	 */
	vector(vector_type const& other) :
			_allocator(other._allocator) {

		this->_pre_allocate(other.end() - other.begin());

		pointer cur_this = this->_start;
		try {
			for (iterator cur_other = other.begin(); cur_other != other.end(); ++cur_other, ++cur_this) {
				this->_allocator.construct(cur_this, *cur_other);
			}
			this->_end += other.end() - other.begin();
		} catch (...) {
			for (pointer p = this->_start; p != cur_this; ++p) {
				this->_allocator.destroy(p);
			}
			throw;
		}
	}

//	virtual ~vector() {
//		for (pointer p = this->_start; p != this->_end; ++p) {
//			this->_allocator.destroy(p);
//		}
//		this->_allocator.deallocate(this->_start, this->_end_cap - this->_start);
//	}


	// TODO: fix to iterators
	iterator begin() {
		return this->_start;
	}
	iterator end() {
		return this->_end;
	}

	iterator begin() const {
		return this->_start;
	}
	iterator end() const {
		return this->_end;
	}

	reference operator[](size_type index) {
		return this->_start[index];
	};
};


#endif //CONTAINERS_VECTOR_CPP
