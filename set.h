#pragma once
#ifndef _SET_H
#define _SET_H
//先暂时用二分搜索树来写，RB-Tree不太好写。。。。
#include"Tree.h"
#include<utility>
namespace ministl
{
	//用小于号比较
	template<typename T>
	class set
	{
	public:
		typedef T key_type;
		typedef BStree_iterator<T, T> iterator;
	private:
		BStree<T, T> sequence;
	public:
		set() :sequence() {}
		iterator begin()
		{
			return sequence.begin();
		}
		iterator end()
		{
			return sequence.end();
		}
		void erase(iterator pos)
		{
			if (pos.p.node == NULL)
				return;
			sequence.erase(pos);
		}
		iterator find(const key_type& key)
		{
			return sequence.find(key);
		}
		size_t count(const key_type& x)
		{
			iterator pos = sequence.find(x);
			if (pos.p.node == NULL)
				return 0;
			else
				return 1;
		}
		size_t erase(const key_type& x)
		{
			iterator pos = sequence.find(x);
			if (pos.p.node == NULL)
				return 0;
			else
			{
				erase(pos);
				return 1;
			}
		}

		bool empty()
		{
			return sequence.empty();
		}
		size_t size()
		{
			return sequence.size();
		}
		iterator insert(const T& val)
		{
			iterator f = sequence.find(val);
			if (f == NULL)
				return sequence.insert(val,val);
			else
				return f;
		}
		iterator lower_bound(const key_type& x)
		{
			return sequence.lower_bound(x);
		}
		iterator upper_bound(const key_type& x)
		{
			return sequence.upper_bound(x);
		}
	};
}



#endif