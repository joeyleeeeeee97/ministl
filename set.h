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
	};
}



#endif