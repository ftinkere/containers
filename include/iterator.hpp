//
// Created by Frey Tinkerer on 9/24/21.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

template <bool, typename T = void>
	struct enable_if {};
template <typename T>
	struct enable_if<true, T> { typedef T type; };


template <typename T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T					value_type;
		typedef integral_constant	type;
	};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;


template <typename T>	struct is_integral						: public false_type {};

template <>				struct is_integral<bool>				: public true_type {};
template <>				struct is_integral<char>				: public true_type {};
template <>				struct is_integral<signed char>			: public true_type {};
template <>				struct is_integral<unsigned char>		: public true_type {};
template <>				struct is_integral<wchar_t>				: public true_type {};

template <>				struct is_integral<short>				: public true_type {};
template <>				struct is_integral<unsigned short>		: public true_type {};
template <>				struct is_integral<int>					: public true_type {};
template <>				struct is_integral<unsigned int>		: public true_type {};
template <>				struct is_integral<long>				: public true_type {};
template <>				struct is_integral<unsigned long>		: public true_type {};
template <>				struct is_integral<long long>			: public true_type {};
template <>				struct is_integral<unsigned long long>	: public true_type {};


template <typename T, typename U>	struct is_same			: public false_type {};
template <typename T>				struct is_same<T, T>	: public true_type {};

//------------------------------------------------------------------------------------------


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename _Category,
		  typename _T,
		  typename _Difference	= ptrdiff_t,
		  typename _Pointer		= _T*,
		  typename _Reference	= _T&>
struct iterator {
	typedef _Category	iterator_category;
	typedef _T			value_type;
	typedef _Difference	difference_type;
	typedef _Pointer	pointer;
	typedef _Reference	reference;
};


template <typename Iter>
struct iterator_traits {
	typedef typename Iter::iterator_category	iterator_category;
	typedef typename Iter::value_type		value_type;
	typedef typename Iter::difference_type	difference_type;
	typedef typename Iter::pointer			pointer;
	typedef typename Iter::reference			reference;
};

template <typename _T>
struct iterator_traits<_T*> {
	typedef random_access_iterator_tag			iterator_category;
	typedef typename std::remove_cv<_T>::type	value_type;
	typedef ptrdiff_t 							difference_type;
	typedef _T*									pointer;
	typedef _T&									reference;
};


// Normal iterator
template <typename Iter, typename Container>
class normal_iterator :
		public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference> {
public:
	typedef Iter		iterator_type;
	typedef Container	container_type;

	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
	typedef normal_iterator<iterator_type, container_type>		this_type;

protected:
	iterator_type _current;

public:

	normal_iterator() : _current(iterator_type ()) {};
	normal_iterator(iterator_type const& current) : _current(current) {};
	normal_iterator(this_type const& other) : _current(other._current) {};
	virtual ~normal_iterator() {}

	this_type& operator=(this_type const& other) {
		_current = other._current;
	};

	iterator_type const& base() const { return _current; };

	// input, forward iterator required

	reference operator*() const {
		return *_current;
	};

	pointer operator->() const {
		return (pointer)addressof(*_current);
	};

	this_type& operator++() {
		++_current;
		return *this;
	};

	this_type operator++(int) {
		return this_type(_current++);
	};

	// bidirectional iterator required

	this_type& operator--() {
		--_current;
		return *this;
	};

	this_type operator--(int) {
		return this_type(_current--);
	};

	// random access iterator required

	reference operator[](difference_type const& n) const {
		return _current[n];
	};

	this_type& operator+=(difference_type const& n) {
		_current += n;
		return *this;
	};

	this_type operator+(difference_type const& n) const {
		return this_type(_current + n);
	};

	this_type& operator-=(difference_type const& n) {
		_current -= n;
		return *this;
	};

	this_type operator-(difference_type const& n) const {
		return this_type(_current - n);
	};
};

template <typename IterL, typename IterR, typename Container>
typename normal_iterator<IterL, Container>::difference_type
operator-(normal_iterator<IterL, Container> const& l_iter,
		  normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() - r_iter.base();
};

template <typename Iter, typename Container>
typename normal_iterator<Iter, Container>::difference_type
operator-(normal_iterator<Iter, Container> const& l_iter,
		  normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() - r_iter.base();
};

template <typename Iter, typename Container>
normal_iterator<Iter, Container>
operator+(typename normal_iterator<Iter, Container>::difference_type const& n,
		  normal_iterator<Iter, Container> const& iter) {
	return normal_iterator<Iter, Container>(iter.base() + n);
};

template <typename IterL, typename IterR, typename Container>
bool operator==(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() == r_iter.base();
};

template <typename Iter, typename Container>
bool operator==(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() == r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator!=(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() != r_iter.base();
};

template <typename Iter, typename Container>
bool operator!=(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() != r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator<(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() < r_iter.base();
};

template <typename Iter, typename Container>
bool operator<(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() < r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator>(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() > r_iter.base();
};

template <typename Iter, typename Container>
bool operator>(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() > r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator<=(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() <= r_iter.base();
};

template <typename Iter, typename Container>
bool operator<=(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() <= r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator>=(normal_iterator<IterL, Container> const& l_iter,
				normal_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() >= r_iter.base();
};

template <typename Iter, typename Container>
bool operator>=(normal_iterator<Iter, Container> const& l_iter,
				normal_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() >= r_iter.base();
};






// Reverse iterator
template <typename Iter, typename Container>
class reverse_iterator :
		public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference> {
public:
	typedef Iter		iterator_type;
	typedef Container	container_type;

	typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iter>::value_type			value_type;
	typedef typename iterator_traits<Iter>::difference_type		difference_type;
	typedef typename iterator_traits<Iter>::pointer				pointer;
	typedef typename iterator_traits<Iter>::reference			reference;
	typedef reverse_iterator<iterator_type, container_type>		this_type;

protected:
	iterator_type _current;

public:

	reverse_iterator() : _current(iterator_type ()) {};
	reverse_iterator(iterator_type const& current) : _current(current) {};
	reverse_iterator(this_type const& other) : _current(other._current) {};
	virtual ~reverse_iterator() {}


	this_type& operator=(this_type const& other) {
		_current = other._current;
	};

	iterator_type const& base() const { return _current; };

	// input, forward iterator required

//	reference operator*() const {
	reference operator*() {
		iterator_type t = _current;
		return *--t;
	};

	pointer operator->() const {
		return (pointer)addressof(*--_current);
	};

	this_type& operator++() {
		--_current;
		return *this;
	};

	this_type operator++(int) {
		return this_type(_current--);
	};

	// bidirectional iterator required

	this_type& operator--() {
		++_current;
		return *this;
	};

	this_type operator--(int) {
		return this_type(_current++);
	};

	// random access iterator required

	reference operator[](difference_type const& n) const {
		return _current[n];
	};

	this_type& operator+=(difference_type const& n) {
		_current -= n;
		return *this;
	};

	this_type operator+(difference_type const& n) const {
		return this_type(_current - n);
	};

	this_type& operator-=(difference_type const& n) {
		_current += n;
		return *this;
	};

	this_type operator-(difference_type const& n) const {
		return this_type(_current + n);
	};
};

template <typename IterL, typename IterR, typename Container>
typename reverse_iterator<IterL, Container>::difference_type
operator-(reverse_iterator<IterL, Container> const& l_iter,
		  reverse_iterator<IterR, Container> const& r_iter) {
	return r_iter.base() - l_iter.base();
};

template <typename Iter, typename Container>
typename reverse_iterator<Iter, Container>::difference_type
operator-(reverse_iterator<Iter, Container> const& l_iter,
		  reverse_iterator<Iter, Container> const& r_iter) {
	return r_iter.base() - l_iter.base();
};

template <typename Iter, typename Container>
reverse_iterator<Iter, Container>
operator+(typename reverse_iterator<Iter, Container>::difference_type const& n,
		  reverse_iterator<Iter, Container> const& iter) {
	return reverse_iterator<Iter, Container>(iter.base() + n);
};

template <typename IterL, typename IterR, typename Container>
bool operator==(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() == r_iter.base();
};

template <typename Iter, typename Container>
bool operator==(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() == r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator!=(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() != r_iter.base();
};

template <typename Iter, typename Container>
bool operator!=(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() != r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator<(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() < r_iter.base();
};

template <typename Iter, typename Container>
bool operator<(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() < r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator>(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() > r_iter.base();
};

template <typename Iter, typename Container>
bool operator>(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() > r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator<=(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() <= r_iter.base();
};

template <typename Iter, typename Container>
bool operator<=(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() <= r_iter.base();
};

template <typename IterL, typename IterR, typename Container>
bool operator>=(reverse_iterator<IterL, Container> const& l_iter,
				reverse_iterator<IterR, Container> const& r_iter) {
	return l_iter.base() >= r_iter.base();
};

template <typename Iter, typename Container>
bool operator>=(reverse_iterator<Iter, Container> const& l_iter,
				reverse_iterator<Iter, Container> const& r_iter) {
	return l_iter.base() >= r_iter.base();
};














#endif //CONTAINERS_ITERATOR_HPP
