#pragma once
#ifndef _MEMORY_H
#define _MEMORY_H
#include"type_traits.h"
namespace ministl
{
	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& val)
	{
		return _uninitialized_fill_n(first, n, val, value_type(first));//利用value_type萃取出迭代器first指向元素的类型信息
	}

	template<class ForwardIterator, class Size, class T, class T1>
	inline  ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& val, T1*)
	{
		typedef typename _type_traits<T1>::is_POD_type is_POD;
		return _uninitialized_fill_n_aux(first, n, x, is_POD());
	}

	template<class ForwardIterator class Size, class T>
	inline  ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type)
	{
		return std::fill_n(first, n, x);
	}

	template<class ForwardIterator class Size, class T>
	inline  ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type)
	{
		ForwardIterator pos = first;
		for (; n > 0; --n, ++cur)
			construct(&*cur, x);
		return cur;
	}



}

#endif