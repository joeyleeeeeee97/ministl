#pragma once
#ifndef _ALGORITHM_H
#define _ALGORITHM_H
#include "utility.h"
#include "iterator.h"
#include "functional.h"
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
	template<class InputIterator, class OutputIterator, class Size = size_t>
	void copy_n(InputIterator first, Size cnt, OutputIterator result)
	{
		for (Size i = 0; i < cnt; first++, result++, i++)
			*result = *first;
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


	template< class ForwardIterator1,class ForwardIterator2 >
	void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
		swap(*a, *b);
	}

	template < class InputIterator, class OutputIterator, class UnaryOperator >
	OutputIterator transform(InputIterator first1, InputIterator last1,
		OutputIterator result, UnaryOperator op)
	{
		for (; first1 != last1; first1++, result++)
		{
			*result = op(*first1);
		}
		return result;
	}

	template < class InputIterator1, class InputIterator2,class OutputIterator, class BinaryOperator >
	OutputIterator transform(InputIterator1 first1, InputIterator1 last1,InputIterator2 first2, OutputIterator result,BinaryOperator binary_op)
	{
		for (; first1 != last1; first1++, first2++, result++)
		{
			*result = binary_op(*first1, *first2);
		}
		return result;
	}

	template < class ForwardIterator, class T >
	void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
	{
		for (; first != last; first++)
		{
			if (*first == old_value) *first = new_value;
		}
	}

	template < class ForwardIterator, class Predicate, class T >
	void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value)
	{
		for (; first != last; first++)
		{
			if (pred(*first)) *first = new_value;
		}
	}

	template < class InputIterator, class OutputIterator, class T >
	OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_val, const T& new_val)
	{
		for (; first != last; first++, result++)
		{
			*result = *first == old_val ? new_val : *first;
		}
		return result;
	}

	template< class InputIterator, class OutputIterator, class Predicate, class T>
	OutputIterator reaplace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred, const T& new_val)
	{
		for (; first != last; first++, result++)
		{
			*result = pred(*first) ? new_val : *first;
		}
		return result;
	}


	template< class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val)
	{
		for (; first != last; first++)
		{
			*first = val;
		}
	}

	template < class OutputIterator, class Size, class T >
	void fill_n(OutputIterator first, Size n, const T& value)
	{
		while (n-- > 0) *(first++) = value;
	}

	template <class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		for (; first != last; first++)
			*first = gen();
	}

	template <class OutputIterator, class Size, class Generator>
	void generate_n(OutputIterator first, Size n, Generator gen)
	{
		while (n > 0) *first++ = gen();
	}

	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val)
	{
		ForwardIterator result = first;
		for (; first != last; first++)
		{
			if (*first != val)
				*result++ = *first;
		}
		return result;
	}

	template < class ForwardIterator, class Predicate >
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
	{
		ForwardIterator result = first;
		for (; first != last; first++)
		{
			if (!pred(*first))
				*result++ = *first;
		}
		return result;
	}

	template < class InputIterator, class OutputIterator, class T>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value)
	{
		for (; first != last; ++first)
			if (!(*first == value)) *result++ = *first;
		return result;
	}

	//并不是所有迭代器都支持随机存取....
	/*template< class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last)
	{
		if (first == last) return first;
		ForwardIterator result = first++;
		for (; first != last; first++)
		{
			if (*first != *(first - 1)) *result++ = *first;
		}
		return result;
	}*/
	template <class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last)
	{
		ForwardIterator result = first;
		while (++first != last)
		{
			if (!(*result == *first))  // or: if (!pred(*result,*first)) for the pred version
				*(++result) = *first;
		}
		return ++result;
	}


	template<class ForwardIterator>
	void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
	{
		ForwardIterator next = tmp;
		while (first != next)
		{
			swap(*first++, *next++);
			if (next == last) next = middle;
			else if (first == middle) middle = next;
		}
	}

	template<class BidirectionalIterator, class Predicate>
	BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		while (1)
		{
			while (first != last && pred(*first)) first++;
			if (first == last--) break;
			while (first != last && !pred(*last)) last--;
			if (first == last) break;
			swap(*first, *last);
		}

		return first;
	}
	//Heap
	/**********[Make_heap]:O[N]***********/
	template<class RandomAccessIterator, class Comparator>
	void up(RandomAccessIterator begin_of_heap, RandomAccessIterator first, RandomAccessIterator last, Comparator comp)
	{
		if (first == last) return;
		size_t index = last - begin_of_heap;
		size_t parent_index = (index - 1) / 2;
		for (auto cur = last; parent_index >= 0 && cur != first; parent_index = (index - 1) / 2)
		{
			auto parent = begin_of_heap + parent_index;
			if (comp(*parent, *cur))
			{
				ministl::swap(*parent, *cur);
			}
			cur = parent;
			index = cur - begin_of_heap;
		}
	}

	template<class RandomAccessIterator, class Comparator>
	void down(RandomAccessIterator begin_of_heap, RandomAccessIterator first, RandomAccessIterator last, Comparator comp)
	{
		if (first == last) return;
		size_t index = first - begin_of_heap;
		size_t child_index = index * 2 + 1;
		for (auto cur = first; child_index <= last - begin_of_heap&&cur < last; child_index = index * 2 + 1)
		{
			auto child = begin_of_heap + child_index;
			if (comp(*cur, *child))
			{
				ministl::swap(*cur, *child);
			}
			cur = child;
			index = cur - begin_of_heap;
		}
	}
	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		ministl::make_heap(first, last, ministl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
	}

	template<class RandomAccessIterator, class Comparator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Comparator comp)
	{
		const size_t cnt = last - first;
		for (auto cur = first + cnt / 2; cur >= first; cur--)
		{
			ministl::down(first, cur, last, comp);
		}
	}
	/**********[Push_Heap]:O[lgN]***********/
	template<class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		ministl::up(first, first, last - 1, ministl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
	}

	template<class RandomAccessIterator, class Comparator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Comparator cmp)
	{
		ministl::up(first, first, last - 1, cmp);
	}
	/**********[Pop_Heap]:O[lgN]***********/

	template<class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		ministl::pop_heap(first, first, last - 1, ministl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
	}

	template<class RandomAccessIterator, class Comparator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Comparator cmp)
	{
		swap(*first, *(last - 1));
		if (last - first > 2)
			ministl::up(first, first, last - 2, cmp);
	}

	/**********[Sort_Heap]:O[NlgN]***********/

	template<class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		ministl::sort_heap(first, last, ministl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
	}

	template<class RandomAccessIterator, class Comparator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last,Comparator comp)
	{
		for (auto cur = last; cur != first; cur--)
			pop_heap(first, cur, comp);
	}

	/**********[Is_Heap]:O[N]***********/

	template<class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		return ministl::is_heap(first,last, ministl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
	}

	template<class RandomAccessIterator, class Comparator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Comparator comp)
	{
		size_t index = (last - first) / 2;
		for (auto cur = first + index; cur >= first; cur--, index--)
		{
			if (*cur < *(first + index * 2 + 1) || (first + index * 2 + 2 < last && *cur < *(first + index * 2 + 2)))
			{
				return false;
			}
		}
		return true;
	}


}



#endif