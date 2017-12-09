#pragma once
#ifndef  _ITERATOR_H
#define _ITERATOR_H
namespace ministl
{
#include<cstddef>
	struct forward_iterator_tag {};
	struct reverse_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category Iiteraotr_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct forward_iterator
	{
		typedef  forward_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

		pointer p;
	};

	template<class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct reverse_iterator
	{
		typedef reverse_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct bidirectional_iterator
	{
		typedef  bidirectional_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct random_access_iterator
	{
		typedef  random_access_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};


	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};


	template<class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag Iiteraotr_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&)
	{
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}



	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	void advance(InputIterator p, Distance n)
	{
		assert(n != 0);
		_advance(p, n, iterator_category(p));
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	void advance(InputIterator p, Distance n, forward_iterator_tag)
	{
		while (n--)p++;
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	void advance(InputIterator p, Distance n, random_access_iterator_tag)
	{
		p = p + n;
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	void advance(InputIterator p, Distance n, bidirectional_iterator_tag)
	{
		if (n > 0)
		{
			while (n != 0)
				n--, p++;
		}
		else
		{
			while (n != 0)
				n++, p--;
		}
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	Distance distance(InputIterator a, InputIterator b)
	{
		return _distance(a, b, iterator_category(a));
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>

	Distance _distance(InputIterator a, InputIterator b, random_access_iterator_tag)
	{
		return b - a;
	}

	template<class InputIterator, class Distance = iterator_traits<InputIterator>::difference_type>
	Distance _distance(InputIterator a, InputIterator b, forward_iterator_tag)
	{
		Distance cnt = 0;
		while (a < b)
			a++, cnt++;
		return cnt;
	}
}

#endif // ! _ITERATOR_H
