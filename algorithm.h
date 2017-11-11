#pragma once
#ifndef _ALGORITHM_H
#define _ALGORITHM_H
#include<utility>

namespace ministl
{
	//	Non - modifying sequence operations :
	template<class ForwardIterator, class Function>
	Function for_each(ForwardIterator first, ForwardIterator last, Function f)
	{
		for (; first != last; first++)
		{
			f(*first);
		}
		return f;
	}
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		for (; first != last; first++)
		{
			if (*first == val)
				break;
		}
		return first;
	}
	template<class InputIterator, class Function>
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
			if (f(*p, *first))
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
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate pred)
	{
		auto it = first2;
		for (; first1 != last1; first1++)
		{
			if (pred(*first1, *it))
				it++;
		}
		return first1 == last1;
	}
	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred)
	{
		for (; first1 != last1; first1++)
		{
			auto i = first1;
			auto j = first2;
			while (j != last2&&i != last1&&*i == *j)
				i++, j++;
			if (j == last2)
				return first1;
		}
		return last1;
	}
	template <class ForwardIterator, class Size, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
		Size count, const T& value)
	{
		for (; first != last; first++)
		{
			Size cnt = 0;
			auto i = first;
			while (cnt < count && i != last &&*i == value)
				i++, cnt++;
			if (cnt == count)
				return first;
		}
		return last;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		for (; first != last; first++)
		{
			*(result++) = *first;
		}
		return result;
	}

	template<class InputIterator, class OutputIterator, class Predicate>
	OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate func)
	{
		for (; first != last; first++)
		{
			if (func(*first))
			{
				*(result++) = *first;
			}
		}
		return result;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result)
	{
		for (; first != last; last--)
		{
			*(result--) = *last;
		}
		return result;
	}

	template<class T>
	void swap(T& a, T& b)
	{
		T t(a);
		a = b;
		b = t;
	}

	template < class ForwardIterator1, class ForwardIterator2 >
	ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2)
	{
		for (; first1 != last1; first1++, first2++)
		{
			swap(*first1, *first2);
		}
		return first2;
	}



}



#endif