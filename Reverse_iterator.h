#pragma once
#ifndef _REVERSE_ITERATOR
#define _REVERSE_ITERATOR
#include"iterator.h"
namespace ministl
{
	template<class iterator>
	class Reverse_iterator
	{
	public:
		typedef iterator iterator_type;
		typedef typename iterator_traits<iterator>::value_type value_type;
		typedef typename iterator_traits<iterator>::reference reference;
		typedef typename iterator_traits<iterator>::pointer pointer;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef Reverse_iterator<iterator> self;
	private:
		iterator pos;
	public:
		Reverse_iterator() :pos() {}
		Reverse_iterator(iterator iter) :pos(iter) {}
		Reverse_iterator(const self& rhs) :pos(rhs.pos) {}

		bool operator==(const self& rhs)
		{
			return pos == rhs.pos;
		}

		bool operator!=(const self& rhs)
		{
			return !(*this == rhs);
		}

		self& operator++()
		{
			pos--;
			return *this;
		}

		self operator++(int)
		{
			auto tmp = *this;
			pos--;
			return tmp;
		}

		self& operator--()
		{
			pos++;
			return *this;
		}

		self operator--(int)
		{
			auto tmp = *this;
			pos++;
			return tmp;
		}

		self& operator=(const self& rhs)
		{
			pos = rhs.pos;
			return *this;
		}

		self& operator+(difference_type n)
		{
			ministl::advance(pos, -n);
			return *this;
		}

		self& operator-(difference_type n)
		{
			ministl::advance(pos, n);
			return *this;
		}

		value_type operator*()
		{
			iterator tmp = pos;
			return *(--tmp);
		}
	};
}



#endif