#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H
#include<memory>
#include"construct.h"
#include<algorithm>
namespace ministl
{
	template<class T, class Alloc = alloc>
	class vector
	{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		typedef Alloc Data_allocator;
		Data_allocator data_allocator;
	protected:
		iterator start, End, end_of_storage;
		//检查是否够空间
		void check()
		{
			if (max_size() == size())
				reallocate();
		}
		void check(size_t num)
		{
			if (capacity() < num)
				reserve(size() + num);
		}
		void reallocate()
		{
			int new_size = size() == 0 ? 1 : 2 * size();
			iterator pos = data_allocator.allocate(new_size),tmp;
			if (pos == nullptr)
			{
				cerr << "out of memory" << endl;
				exit(1);
			}
			tmp = uninitialized_copy(start, End, pos);
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
			start = pos;
			End = tmp;
			end_of_storage = start + new_size;
		}
		void Print()
		{
			for (iterator it = start; it != End; it++)
				cout << *it << endl;
			cout << endl << endl;
		}
	public:
		//construct
		vector() :start(NULL), End(NULL), end_of_storage(NULL) {}
		vector(int n, value_type val = value_type())
		{
			if (n <= 0)
			{
				cerr << "不能是负数哦！" << endl;
				exit(1);
			}
			start = data_allocator.allocate(n);
			End = end_of_storage = start + n;
			uninitialized_fill_n(start, n, val);
		}
		vector(iterator first, iterator last)
		{
			start = data_allocator.allocate(last - first);
			End = end_of_storage = uninitialized_copy(first, last, start);
		}
		vector(vector<T, Alloc> &rhs)
		{
			*this = rhs;
		}
		//Destructor
		~vector()
		{
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
		}
		//Iterator
		iterator begin()
		{
			return start;
		}
		iterator end()
		{
			return End;
		}
		//Elemnt access
		value_type operator [](size_type n)
		{
			if (n >= size())
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			return *(start + n);
		}
		value_type front()
		{
			if (empty())
			{
				cerr << "空的！" << endl;
				exit(1);
			}
			return *(start);
		}
		value_type back()
		{
			if (empty())
			{
				cerr << "空的！" << endl;
				exit(1);
			}
			return *(End - 1);
		}
		//Capacity
		size_type size()
		{
			return End - start;
		}
		size_type max_size()
		{
			return end_of_storage - start;
		}
		size_type capacity()
		{
			return end_of_storage - End;
		}
		void resize(size_type n, value_type val = value_type())
		{
			iterator pos = data_allocator.allocate(n);
			size_type sz = size();
			if (n <= sz)
			{
				End = end_of_storage = uninitialized_copy_n(start, n, pos);
				start = pos;
			}
			else
			{
				End = uninitialized_copy(start, End, pos);
				end_of_storage = uninitialized_fill_n(End, n - sz, val);
				start = pos;
			}
		}
		void reserve(size_type n)
		{
			if (n > size())
			{
				iterator pos = data_allocator.allocate(n);
				End = uninitialized_copy(start, End, pos);
				start = pos;
				end_of_storage = start + n;
			}
		}
		bool empty()
		{
			return start == End;
		}
		//Modifiers
		void push_back(value_type data)
		{
			check();
			construct(End++, data);
		}
		void pop_back()
		{
			if (empty())
			{
				cerr << "空的!" << endl;
				exit(1);
			}
			End--;
			destroy(End);
		}
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last)//先只设计指针的
		{
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
			start = data_allocator.allocate(last - first);
			End = end_of_storage = uninitialized_copy(first, last, start);
		}
		void assign(size_type n, const value_type &v)
		{
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
			start = data_allocator.allocate(n);
			End = end_of_storage = start + n;
			uninitialized_fill_n(start, n, v);
		}
		iterator insert(iterator pos, const value_type &v)
		{
			if (pos - start < 0 || pos >= End)
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			size_type pp = pos - start;
			check();
			pos = start + pp;
			uninitialized_copy(pos, End, pos + 1);
			construct(pos, v);
			End++;
			return pos;
		}
		iterator insert(iterator pos, const size_type &n, const value_type &val)
		{
			if (pos - start < 0 || pos >= End)
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			size_type pp = pos - start;
			check(n);
			pos = start + pp;
			uninitialized_copy(pos, End, pos + n);
			uninitialized_fill_n(pos, n, val);
			End = End + n;
			return pos + n - 1;
		}
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)//还是先只写 前向迭代器
		{
			if (pos - start < 0 || pos >= End)
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			size_type pp = pos - start;
			check(last-first);
			pos = start + pp;
			uninitialized_copy(pos, End, pos + (last - first));
			uninitialized_copy(first, last, pos);
			End = End + (last - first);
		}
		iterator erase(iterator pos)
		{
			if (pos - start < 0 || pos >= End)
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			destroy(pos);
			uninitialized_copy(pos + 1, End, pos);
			End--;
			return pos;
		}
		
		iterator erase(iterator first, iterator last)
		{
			if (first >= last)
			{
				cerr << "左端点小于右端点！" << endl;
				exit(1);
			}
			if (first - start < 0 || last > End)
			{
				cerr << "越界！" << endl;
				exit(1);
			}
			for (iterator it = first; it != last; it++)
			{
				destroy(it);
			}
			uninitialized_copy(last, End, first);
			End = End - (last - first);
			return last;
		}
		void clear()
		{
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
			End = start;
		}
		void swap(vector<T, Alloc> &rhs)
		{
			iterator tmp;
			tmp = start, start = rhs.start, rhs.start = tmp;
			tmp = End, End = rhs.End, rhs.End = tmp;
			tmp = end_of_storage, end_of_storage = rhs.end_of_storage, rhs.end_of_storage = tmp;
		}
	};
		
}
#endif