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
		typedef typename iterator_traits<ForwardIterator1>::value_type value_type;
		find_if(first, last, equal_to<value_type>());
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

	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred)
	{
		if (last1 == first1 || last2 == first2)
			return last1;
		auto pos = last1;
		while (pos != first1)
		{
			auto pos1 = pos;
			auto pos2 = first2;
			while (pos1 < last1 && pos2 < last2 && pred(*pos1, *pos2))
			{
				pos1++, pos2++;
			}
			if (pos2 == last2)
				return pos;
			pos--;
		}
		return last1;
	}

	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		typedef typename iterator_traits<ForwardIterator1>::value_type value_type;
		return ministl::find_end(first1, last1, first2, last2, equal_to<value_type>());
	}
	

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		typedef typename iterator_traits<ForwardIterator1>::value_type value_type;
		return ministl::find_first_of(first1, last1, first2, last2, equal_to<value_type>());
	}
	template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2,
		BinaryPredicate pred)
	{
		for (; first1 != last; first1++)
		{
			auto i = first1;
			auto j = first2;
			while (j != last2 && pred(*i,*j))
				i++, j++;
			if (j == last2)
				break;
		}
		return first1;
	}
	

	template <class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		typedef typename iterator_traits<ForwardIterator>::value_type value_type;
		adjacent_find(first, last, equal_to<value_type>());
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
		typename typedef iterator_traits<ForwardIterator>::value_type value_type;
		return count_if(first, last, equal_to<value_type>());
	}

	template <class InputIterator, class Predicate>
	size_t count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		size_t ret = 0;
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

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2)
	{
		typedef typename iterator_traits<InputIterator1>::value_type value_type;
		return equal(first1, last1, first2, equal_to<value_type>());
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
			while (j != last2&&i != last1&& pred(*j,*i))
				i++, j++;
			if (j == last2)
				return first1;
		}
		return last1;
	}

	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2)
	{
		typename typedef iterator_traits<ForwardIterator1>::value_type value_type;
		return search(first1, last1, first2, last2, equal_to<value_type>());
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
		while (n-- > 0) *first++ = gen();
	}

	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val)
	{
		typedef typename iterator_traits<ForwardIterator>::value_type value_type;
		return remove_if(first, last, equal_to<value_type>());
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

	template <class ForwardIterator, class BinaryPredicate>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last,
		BinaryPredicate pred)
	{
		ForwardIterator result = first;
		while (++first != last)
		{
			if (!pred(*first, *result))
			{
				*(++result) = *first;
			}
		}
		return ++result;
	}

	template <class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last)
	{
		typedef typename iterator_traits<ForwardIterator>::value_type value_type;
		return unique(first, last, equal_to<value_to>());
	}


	template<class ForwardIterator>
	void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
	{
		ForwardIterator next = middle;
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
		while (true)
		{
			while (first != last && pred(*first)) ++first;
			if (first == last--) break;
			while (first != last && !pred(*last)) --last;
			if (first == last) break;
			swap(*first++, *last);
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
		for (auto cur = last; parent_index >= 0 && cur != begin_of_heap; parent_index = (index - 1) / 2)
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
		for (auto cur = first; child_index <= last - begin_of_heap && cur < last; child_index = index * 2 + 1)
		{
			auto child = begin_of_heap + child_index;
			if (child + 1 <= last &&  comp(*child,*(child + 1)))
			{
				child = child + 1;
			}
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
		for (auto cur = first + cnt / 2 - 1; cur >= first; cur--)
		{
			ministl::down(first, cur, last - 1, comp);
			if (cur == first) return;
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
		if (last - first > 1)
			ministl::down(first, first, last - 2, cmp);
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
			ministl::pop_heap(first, cur, comp);
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

	template <class RandomAccessIterator>
	void sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
		return ministl::sort(first, last, less<value_type>());
	}
	template<class RandomAccessIterator, class Compare>
	RandomAccessIterator comp_partition(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		auto l = first, r = last - 1;
		auto val = *first;
		while (l < r)
		{
			while (l < r && !comp(*r, val))
			{
				r--;
			}
			if (l < r)
			{
				*l++ = *r;
			}
			while (l < r && comp(*l, val))
			{
				l++;
			}
			if (l < r)
			{
				*r-- = *l;
			}
		}
		*l = val;
		return l;
	}
	template <class RandomAccessIterator, class Compare>
	void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		if (first >= last) return;
		auto l = comp_partition(first, last, comp);
		if (l == first || l == last) return;
		ministl::sort(first, l, comp);
		ministl::sort(l + 1, last, comp);
	}

	template <class RandomAccessIterator>
	void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
		RandomAccessIterator last)
	{
		typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
		return ministl::partial_sort(first, middle, last, less<value_type>());
	}

	template <class RandomAccessIterator, class Compare>
	void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
		RandomAccessIterator last, Compare comp)
	{
		ministl::make_heap(first, middle, comp);
		for (auto pos = middle; pos != last; pos++)
		{
			if (!comp(*first,*pos))
			{
				swap(*first, *pos);
				ministl::down(first, first, middle - 1, comp);
			}
		}
		ministl::sort(first, middle, comp);
	}

	template <class RandomAccessIterator, class Compare>
	void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
		RandomAccessIterator last, Compare comp)
	{
		if (first >= last) return;
		auto val = median(*first, *(last - 1), *(first + (last - first - 1) / 2));
		auto pos = comp_partition(first, last, comp);
		if (pos < nth)
		{
			ministl::nth_element(pos + 1, nth, last, comp);
		}
		else
		{
			ministl::nth_element(first, nth, pos, comp);
		}
	}

	template <class RandomAccessIterator, class Compare>
	void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
		RandomAccessIterator last)
	{
		typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
		return ministl::nth_element(first, nth, last, less<value_type>());
	}

	template <class T>
	T median(T a, T b, T c)
	{
		if ((a <= b && a >= c) || (a <= c && a >= b))
		{
			return a;
		}
		else if ((b <= a && b >= c) || (b <= c && b >= a))
		{
			return b;
		}
		else if ((c <= a && c >= b) || (c <= b && c >= a))
		{
			return c;
		}
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result);

	template <class InputIterator1, class InputIterator2,
		class OutputIterator, class Compare>
		OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			*result++ = (comp(*first1, *first2)) ? *first1++ : *first2++;
		}
		if (first2 == last2)
		{
			ministl::copy(first1, last1, result);
		}
		if (first1 == last1)
		{
			ministl::copy(first2, last2, result);
		}
	}



}



#endif