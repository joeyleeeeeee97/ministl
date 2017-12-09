#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include"list.h"
#include"vector.h"
#include"functional.h"
#include"algorithm.h"
namespace ministl
{
	template<class T,class Sequence = list<T>>
	class queue
	{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef size_t size_type;
		typedef typename Sequence::iterator iterator;
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
		
		iterator begin()
		{
			return c.begin();
		}
		
		iterator end()
		{
			return c.end();
		}

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

	template<class T,class Sequence = ministl::vector<T>,class Comparator = ministl::less<T>>
	class priority_queue
	{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef typename Sequence::iterator iterator;
		typedef size_t size_type;
	private:
		Sequence seq;
		Comparator cmp;
	public:
	//	priority_queue() :seq(), cmp() {}
		
		explicit priority_queue(const Comparator& comp = Comparator(),const Sequence& ctnr = Sequence())
			: seq(ctnr), cmp(comp) {}
		
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Comparator& comp = less<T>(), const Sequence& ctnr = vector<T>()):seq(ctnr),cmp(comp)
		{
			seq.insert(seq.end(), first, last);
			make_heap(seq.begin(), seq.end(),cmp);
		}

		bool empty() const 
		{
			return seq.empty();
		}

		size_type size() const
		{
			return seq.size();
		}

		reference top() 
		{
			return seq.front();
		}

		void push_back(const value_type& val)
		{
			seq.push_back(val);
			push_heap(seq.begin(), seq.end(),cmp);
		}

		void pop_back()
		{
			seq.pop_back();
			pop_heap(seq.begin(), seq.end(),cmp);
		}

		void swap(priority_queue<T, Sequence, Comparator>& rhs)
		{
			ministl::swap(seq, rhs.seq);
			ministl::swap(cmp,rhs.cmp)
		}


	};

	template<class T, class Sequence, class Comparator>
	void swap(priority_queue<T, Sequence, Comparator>& lhs, priority_queue<T, Sequence, Comparator>& rhs)
	{
		lhs.swap(rhs);
	}
}
#endif