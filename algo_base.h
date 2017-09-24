#pragma once
#ifndef _ALGO_BASE_H
#define _ALGO_BASE_H
#include<utility>
namespace ministl
{
//	Non - modifying sequence operations :
	template<class ForwardIterator,class Function>
	Function for_each(ForwardIterator first, ForwardIterator last, Function f)
	{
		for (; first != last; first++)
		{
			f(*first);
		}
		return f;
	}
	template<class InputIterator,class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; first++)
		{
			if (*first == val)
				break;
		}
		return first;
	}
	template<class InputIterator,class Function>
	InputIterator find_if(InputIterator first, InputIterator last, Function f)
	{
		for (; first != last; first++)
		{
			if (f(*first))
				break;
		}
		return first;
	}
	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		if (last1 == first1 || last2 == first2 || last1 - first1 < last2 - first2)
			return last1;
		int size = last2 - first2;
		ForwardIterator1 tmp = last1;
		for (int i = 0; i < size; i++)
			tmp--;
		while (1)
		{
			int i;
			ForwardIterator1 pos = tmp;
			for (i = 0; i < size; i++)
			{
				if (*pos != *first2)
					break;
				pos++, first2++;
			}
			if (i == size)
				return tmp;
			if (tmp == first1)
				break;
			tmp--;
		}
		return last1;
	}
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		for (; first1 != last; first1++)
		{
			auto i = first1;
			auto j = first2;
			while (j != last2 && *i == *j)
				i++, j++;
			if (j == last2)
				break;
		}
		return first1;
	}
	template <class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		auto p = first++;
		while (first != last)
		{
			if (*p == *first)
				break;
			first++;
			p++;
		}
		if (first == last)
			return last;
		else
			return p;
	}
	template <class ForwardIterator, class Function>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, Function f)
	{
		auto p = first++;
		while (first != last)
		{
			if (f(*p,*first))
				break;
			first++;
			p++;
		}
		if (first == last)
			return last;
		else
			return p;
	}
	template <class ForwardIterator, class T>
	size_t count(ForwardIterator first, ForwardIterator last, const T& value)
	{
		auto cnt = 0;
		for (; first != last; first++)
		{
			if (*first == value)
				cnt++;
		}
		return cnt;
	}
	template <class InputIterator, class Predicate>
	ptrdiff_t count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		ptrdiff_t ret = 0;
		while (first != last) if (pred(*first++)) ++ret;
		return ret;
	}
	template <class InputIterator1, class InputIterator2>
	std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && (*first1 == *first2))
		{
			first1++, first2++;
		}
		return std::pair<InputIterator1, InputIterator2>({ first1,first2 });
	}
}



#endif