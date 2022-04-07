//
// Created by Frey Tinkerer on 9/24/21.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

#include <iostream>

namespace ft {

	template <bool, typename T = void>
		struct enable_if {};
	template <typename T>
		struct enable_if<true, T> { typedef T type; };


	template <typename T, T v>
		struct integral_constant {
			static const T				value = v;
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


	template<typename T> struct remove_cv { typedef T type; };

	template<typename T> struct remove_cv<const T> { typedef T type; };

	template<typename T> struct remove_cv<volatile T> { typedef T type; };

	template<typename T> struct remove_cv<const volatile T> { typedef T type; };


	template<bool Is, typename IfNon, typename IfIs> struct choose {};
	template<typename IfNon, typename IfIs> struct choose<false, IfNon, IfIs> {
		typedef IfNon	type;
	};
	template<typename IfNon, typename IfIs> struct choose<true, IfNon, IfIs> {
		typedef IfIs	type;
	};

	//------------------------------------------------------------------------------------------

	template <typename Iter>
	struct iterator_traits {
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::ptrdiff_t 						difference_type;
	};
	template <typename T>
	struct iterator_traits<T const*> {
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::ptrdiff_t 						difference_type;
	};


	// Normal iterator
	template <typename Base>
	class base_iterator {
	public:
		typedef typename remove_cv<Base>::type						base_type;
		typedef std::random_access_iterator_tag						iterator_category;
		typedef typename iterator_traits<Base*>::value_type 		value_type;
		typedef typename iterator_traits<Base*>::difference_type 	difference_type;
		typedef typename iterator_traits<Base*>::pointer 			pointer;
		typedef typename iterator_traits<Base*>::reference 			reference;
//		typedef base_iterator										this_type;

	protected:
		pointer _current;

	public:
		base_iterator(const pointer current = 0) : _current(current) {};
		base_iterator(base_iterator<base_type> const& other) : _current(&(*other)) {};
		virtual ~base_iterator() {};

		base_iterator<value_type>& operator=(base_iterator<base_type> const& other) {
			if (&other != this) {
				_current = &(*other);
			}
			return *this;
		};

//		operator base_iterator<const base_type>() const {
//			return base_iterator<const base_type>(_current);
//		}

//		operator pointer() const {
//			return _current;
//		}

		pointer base() const { return _current; };

		// input, forward iterator required

		reference operator*() const { return *_current; };

		pointer operator->() const { return _current; };

		base_iterator& operator++() {
			++_current;
			return *this;
		};

		base_iterator operator++(int) {
			base_iterator ret(_current);
			++_current;
			return ret;
		};

		// bidirectional iterator required

		base_iterator& operator--() {
			--_current;
			return *this;
		};

		base_iterator operator--(int) {
			base_iterator ret(_current);
			--_current;
			return ret;
		};

		// random access iterator required

		reference operator[](difference_type const& n) const { return _current[n]; };

		base_iterator& operator+=(difference_type const& n) {
			_current += n;
			return *this;
		};

		base_iterator& operator-=(difference_type const& n) {
			_current -= n;
			return *this;
		};

		base_iterator<Base> operator+(difference_type const& n) const { return base_iterator(_current + n); };
		base_iterator<Base> operator-(difference_type const& n) const { return base_iterator(_current - n); };

		friend base_iterator<Base> operator+(difference_type const& n, base_iterator<Base> const& it) { return it + n; };
//		friend base_iterator<Base> operator-(difference_type const& n, base_iterator<Base> const& it) { return base_iterator<base_type>(it.base() - n); };

		difference_type operator-(base_iterator<base_type> const& other) const { return (_current - other.base()); };
		difference_type operator-(base_iterator<const base_type> const& other) const { return (_current - other.base()); };

		bool operator==(base_iterator<base_type> const& other) const { return _current == other.base(); }
		bool operator==(base_iterator<const base_type> const& other) const { return _current == other.base(); }
		bool operator!=(base_iterator<base_type> const& other) const { return _current != other.base(); }
		bool operator!=(base_iterator<const base_type> const& other) const { return _current != other.base(); }
		bool operator<(base_iterator<base_type> const& other) const { return _current < other.base(); }
		bool operator<(base_iterator<const base_type> const& other) const { return _current < other.base(); }
		bool operator>(base_iterator<base_type> const& other) const { return _current > other.base(); }
		bool operator>(base_iterator<const base_type> const& other) const { return _current > other.base(); }
		bool operator<=(base_iterator<base_type> const& other) const { return _current <= other.base(); }
		bool operator<=(base_iterator<const base_type> const& other) const { return _current <= other.base(); }
		bool operator>=(base_iterator<base_type> const& other) const { return _current >= other.base(); }
		bool operator>=(base_iterator<const base_type> const& other) const { return _current >= other.base(); }
	};


//	// Reverse iterator
//	template <typename Base, bool IsConst>
//	class reverse_base_iterator {
//	public:
//		typedef remove_cv<Base>*									base_type;
//		typedef std::random_access_iterator_tag						iterator_category;
//		typedef Base												value_type;
//		typedef std::size_t 										difference_type;
//		typedef typename choose<IsConst, Base*, const Base*>::type	pointer;
//		typedef typename choose<IsConst, Base&, const Base&>::type	reference;
//		typedef reverse_base_iterator								this_type;
//
//	protected:
//		pointer _current;
//
//	public:
//
//		reverse_base_iterator(pointer current = 0)										: _current(current) {};
//		explicit reverse_base_iterator(base_iterator<base_type> const& other)			: _current(other.base() - 1) {};
//		explicit reverse_base_iterator(base_iterator<Base, true> const& other)			: _current(other.base() - 1) {};
//		explicit reverse_base_iterator(reverse_base_iterator<base_type> const& other)	: _current(other.base()) {};
//		explicit reverse_base_iterator(reverse_base_iterator<Base, true> const& other)	: _current(other.base()) {};
//		virtual ~reverse_base_iterator() {};
//
//		reverse_base_iterator& operator=(reverse_base_iterator<base_type> const& other) {
//			if (&other != this) {
//				_current = other.base();
//			}
//			return *this;
//		};
//		reverse_base_iterator& operator=(reverse_base_iterator<Base, true> const& other) {
//			if (&other != this) {
//				_current = other.base();
//			}
//			return *this;
//		};
//
//		operator reverse_base_iterator<Base, true>() {
//			return reverse_base_iterator<Base, true>(_current);
//		};
//
//		operator pointer() {
//			return _current;
//		}
//
//		pointer base() const { return _current; };
//
//		// input, forward iterator required
//
//		reference operator*() const { return *_current; };
//
//		pointer operator->() const { return _current; };
//
//		this_type& operator++() {
//			--_current;
//			return *this;
//		};
//
//		this_type operator++(int) {
//			this_type ret(_current);
//			--_current;
//			return ret;
//		};
//
//		// bidirectional iterator required
//
//		this_type& operator--() {
//			++_current;
//			return *this;
//		};
//
//		this_type operator--(int) {
//			this_type ret(_current);
//			++_current;
//			return ret;
//		};
//
//		// random access iterator required
//
//		reference operator[](difference_type const& n) const { return _current[n]; };
//
//		this_type& operator+=(difference_type const& n) {
//			_current += n;
//			return *this;
//		};
//
//		this_type& operator-=(difference_type const& n) {
//			_current -= n;
//			return *this;
//		};
//
//		this_type operator+(difference_type const& n) const { return this_type(_current + n); };
//		this_type operator-(difference_type const& n) const { return this_type(_current - n); };
//
//		friend this_type operator+(difference_type const& n, this_type const& it) { return this_type(it.base() + n); };
//		friend this_type operator-(difference_type const& n, this_type const& it) { return this_type(it.base() - n); };
//
//		difference_type operator-(reverse_base_iterator<base_type> const& other) const { return (other.base() - _current); };
//		difference_type operator-(reverse_base_iterator<Base, true> const& other) const { return (other.base() - _current); };
//
//		bool operator==(reverse_base_iterator<base_type> const& other) const { return _current == other.base(); }
//		bool operator==(reverse_base_iterator<Base, true> const& other) const { return _current == other.base(); }
//		bool operator!=(reverse_base_iterator<base_type> const& other) const { return _current != other.base(); }
//		bool operator!=(reverse_base_iterator<Base, true> const& other) const { return _current != other.base(); }
//		bool operator<(reverse_base_iterator<base_type> const& other) const { return _current < other.base(); }
//		bool operator<(reverse_base_iterator<Base, true> const& other) const { return _current < other.base(); }
//		bool operator>(reverse_base_iterator<base_type> const& other) const { return _current > other.base(); }
//		bool operator>(reverse_base_iterator<Base, true> const& other) const { return _current > other.base(); }
//		bool operator<=(reverse_base_iterator<base_type> const& other) const { return _current <= other.base(); }
//		bool operator<=(reverse_base_iterator<Base, true> const& other) const { return _current <= other.base(); }
//		bool operator>=(reverse_base_iterator<base_type> const& other) const { return _current >= other.base(); }
//		bool operator>=(reverse_base_iterator<Base, true> const& other) const { return _current >= other.base(); }
//	};

}

#endif //CONTAINERS_ITERATOR_HPP

