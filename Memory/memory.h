#pragma once
#ifndef _MEMORY_H
#define _MEMORY_H
#include"type_traits.h"
#include"iterator.h"
#include"algorithm.h"
namespace ministl
{
	template<class InputIterator, class OutputIterator>
	inline OutputIterator uninitialized_copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		typedef _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_pod;
		return aux_uninitialized_copy(first, last, result, is_pod());

	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator aux_uninitialized_copy(InputIterator first, InputIterator last, OutputIterator result, _true_type)
	{
		copy(first, last, result);
		return result + (last - first);
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator aux_uninitialized_copy(InputIterator first, InputIterator last, OutputIterator result, _false_type)
	{
		for (; first != last; result++, first++)
		{
			construct(result, *first);
		}
		return result;
	}

	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type, class OutputIterator>
	inline OutputIterator uninitialized_copy_n(InputIterator first, Size n, OutputIterator result)
	{
		typedef _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_pod;
		return aux_uninitialized_copy_n(first, n, result, is_pod());
	}

	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type, class OutputIterator>
	inline OutputIterator aux_uninitialized_copy_n(InputIterator first, Size n, OutputIterator result, _true_type)
	{
		copy_n(first, n, result);
		return result + n;
	}

	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type, class OutputIterator>
	inline OutputIterator aux_uninitialized_copy_n(InputIterator first, Size n, OutputIterator result, _false_type)
	{
		for (Size cnt = 0; cnt < n; cnt++, result++, first++)
		{
			construct(result, *first);
		}
		return result;
	}

	template<class InputIterator, class T>
	inline void uninitialized_fill(InputIterator first, InputIterator last, const T& val)
	{
		typedef _type_traits<T>::is_POD_type is_pod;
		aux_uninitialized_fill(first, last, val, is_pod());
	}

	template<class InputIterator, class T>
	inline void aux_uninitialized_fill(InputIterator first, InputIterator last, const T& val, _true_type)
	{
		fill(first, last, val);
	}

	template<class InputIterator, class T>
	inline void aux_uninitialized_fill(InputIterator first, InputIterator last, const T& val, _false_type)
	{
		for (; first != last; first++)
			construct(first, val);
	}

	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type ,class T>
	inline void uninitialized_fill_n(InputIterator first, Size n, const T& val)
	{
		typedef _type_traits<T>::is_POD_type is_pod;
		aux_uninitialized_fill_n(first, n, val, is_pod());
	}
	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type, class T>
	inline void aux_uninitialized_fill_n(InputIterator first, Size n, const T& val, _true_type)
	{
		fill_n(first, n, val);
	}

	template<class InputIterator, class Size = iterator_traits<InputIterator>::difference_type, class T>
	inline void aux_uninitialized_fill_n(InputIterator first, Size n, const T& val, _false_type)
	{
		for (Size cnt = 0; cnt < n; first++, cnt++)
			construct(first, val);
	}

}

#endif