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
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};


	template<class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag iterator_category;
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
	//Itertor adaptors - inserter

	template<class Container>
	class back_inserter_iterator
	{
	private:
		typedef back_inserter_iterator<Container> self;
	public:
		back_inserter_iterator(Container& rhs) :ptr(&rhs)
		{

		}
		self& operator=(const typename Container::value_type& value)
		{
			ptr->push_back(value);
			return *this;
		}

		self& operator++()
		{
			return *this;
		}
		self& operator++(int)
		{
			return *this;
		}
		self& operator*()
		{
			return *this;
		}
	private:
		Container* ptr;
	};

	template<class Container>
	back_inserter_iterator<Container> back_inserter(const Container& rhs)
	{
		return back_inserter_iterator<Container>(rhs);
	}

	template<class Container>
	class inserter_iterator
	{
	private:
		typedef inserter_iterator<Container> self;
		typedef typename Container::iterator itername;
	public:
		inserter_iterator(Container& rhs1,itername& rhs2) :ptr(&rhs1),iter(rhs2)
		{

		}
		self& operator=(const typename Container::value_type& value)
		{
			iter = ptr->insert(iter, value);
			iter++;
			return *this;
		}

		self& operator++()
		{
			return *this;
		}
		self& operator++(int)
		{
			return *this;
		}
		self& operator*()
		{
			return *this;
		}
	private:
		Container* ptr;
		itername iter;
	};

	//- stream iterator
	/*
	流迭代器可以把迭代器绑定到一个数据流对象上，在内部维护这个对象，
	*/
	template<class T>
	class ostream_iterator
	{
	private:
		typedef forward_iterator_tag iterator_category;
		typedef void value_type;
		typedef void difference_type;
		typedef void pointer;
		typedef void reference;
		typedef ostream_iterator<T> self;
	public:
		ostream_iterator(std::ostream& ss, const char* str) :stream(&ss), delim(str)
		{

		}
		self& operator=(const T& value)
		{
			*stream << value;
			if (delim != nullptr)
			{
				*stream << delim;
			}
			return *this;
		}
		self& operator++(int) { return *this; }
		self& operator++() { return *this; }
		self& operator*() { return *this; }
	private:
		std::ostream* stream;
		const char* delim;

	};
}

#endif 
