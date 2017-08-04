#pragma once
#ifndef _STACK_H
#define _STACK_H
#include"list.h"

namespace ministl
{
	template<class T,class Sequence = list<T>>
	class stack
	{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef size_t size_type;
	protected:
		Sequence c;
	public:
		stack() :c() {}
		bool empty()  
		{ 
			return c.empty(); 
		}
		size_type size()  
		{ 
			return  c.size(); 
		}
		value_type& top()
		{
			if(!empty())
				return *(c.begin());
			else
			{
				cerr << "Top on empty Stack!" << endl;
				exit(1);
			}
		}
		void pop()
		{
			if(!empty())
				c.pop_front();
			else
			{
				cerr << "pop on empty Stack!" << endl;
				exit(1);
			}
		}
		void push(const value_type& x)
		{
			c.push_front(x);
		}
	};
}

#endif