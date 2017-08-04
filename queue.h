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
				cerr << "Empty !" << endl;
				exit(1);
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
			return *(c.end() - 1);
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
	};
}
#endif