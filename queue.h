#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include"list.h"
namespace ministl
{
	template<class T,class Sequence = list<T>>
	class queue
	{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef size_t size_type;
	protected:
		Sequence c;
		void check()
		{
			if (empty())
			{
				std::cerr << "Empty !" << std::endl;
				std::exit(1);
			}
		}
	public:
		queue():c(){}
		bool empty()
		{
			return c.empty();
		}
		size_type size()
		{
			return c.size();
		}
		value_type& front()
		{
			check();
			return *(c.begin());
		}
		value_type& back()
		{
			check();
			auto tmp = c.end();
			tmp--;
			return *(tmp);
		}
		const value_type& front() const
		{
			check();
			return *(c.begin());
		}
		const value_type& back() const
		{
			check();
			return *(c.end() - 1);
		}
		void push(const value_type& x)
		{
			c.push_back(x);
		}
		void pop()
		{
			check();
			c.pop_front();
		}
		bool operator==( queue<T>& rhs)
		{
			return c == rhs.c;
		}
		bool operator!=( queue<T>& rhs)
		{
			return !(*this == rhs);
		}
		queue<T>& swap(queue<T>& rhs)
		{
			c.swap(rhs.c);
			return *this;
		}
		
	};
	template<typename T>
	void swap(queue<T> &a, queue<T> &b)
	{
		a.swap(b);
	}
}
#endif