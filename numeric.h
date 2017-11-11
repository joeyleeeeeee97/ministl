#pragma once
#ifndef _NUMERIC_H
#define _NUMERIC_H
namespace stl
{
	template<class InputIterator,class T>
	T accumulate(InputIterator first, InputIterator last, T init)
	{
		for (; first != last; first++)
		{
			init += *first;
		}
		return init;
	}
	
	template<class InputIterator,class BinaryFunc,class T>
	T accumulate(InputIterator first, InputIterator last, T init, BinaryFunc fuc)
	{
		for (; first != last; first++)
		{
			init = fuc(init, *first);
		}
		return init;
	}

	template<class InputIterator,class OutputIterator>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last) return result;
		auto pre = *first;
		first++;
		while (first != last)
		{
			auto cur = *first;
			*(result++) = cur - pre;
			pre = cur;
		}
		return result;
	}

	template<class InputIterator,class OutputIterator,class BinaryFuction>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryFuction func)
	{
		if (first == last) return result;
		auto pre = *(first++);
		while (first != last)
		{
			auto cur = *first;
			*(result++) = func(cur, pre);
			pre = cur;
		}
		return result;
	}

	template<class InputIterator1,class InputIterator2,class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, T init)
	{
		for (; first1 != last1&&first2 != last2; first1++, first2++)
		{
			init += (*first1)*(*first2);
		}
		return init;
	}

	template<class InputIterator1, class InputIterator2, class T, class BinaryFunction>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryFunction func,T init)
	{
		for (; first1 != last1&&first2 != last2; first1++, first2++)
		{
			init += func((*first1), (*first2));
		}
		return init;
	}

	template<class InputIterator,class OutputIterator>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last) return result;
		auto sum = *(first++);
		*(result++) = sum;
		while (first != last)
		{
			sum += *(first++);
			*(result++) = sum;
		}
		return result;
	}

	template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation func)
	{
		if (first == last) return result;
		T value = *first;
		while (++first != last)
		{
			value = func(value, *first);
			++result = value;
		}
		return value;
	}
}





#endif