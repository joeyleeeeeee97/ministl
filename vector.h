#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H
#include<memory>
#include"construct.h"
#include<algorithm>
namespace ministl
{
	template<class T, class Alloc = std::allocator<T> >
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
				std::cerr << "out of memory" << std::endl;
				std::exit(1);
			}
			tmp = std::uninitialized_copy(start, End, pos);
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
		vector()
		{
			start = data_allocator.allocate(1);
			End = end_of_storage = start;
		}
		vector(int n, value_type val = value_type())
		{
			if (n <= 0)
			{
				std::cerr << "不能是负数哦！" << std::endl;
				std::exit(1);
			}
			start = data_allocator.allocate(n);
			End = end_of_storage = start + n;
			std::uninitialized_fill_n(start, n, val);
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
			//data_allocator.deallocate(start, end_of_storage - start);
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
		value_type& operator [](size_type n)
		{
			if (n >= size())
			{
				std::cerr << "越界！" << std::endl;
				std::exit(1);
			}
			return *(start + n);
		}
		value_type& front()
		{
			if (empty())
			{
				std::cerr << "空的！" << std::endl;
				std::exit(1);
			}
			return *(start);
		}
		value_type& back()
		{
			if (empty())
			{
				std::cerr << "空的！" << std::endl;
				std::exit(1);
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
				End = end_of_storage = std::uninitialized_copy_n(start, n, pos);
				start = pos;
			}
			else
			{
				End = std::uninitialized_copy(start, End, pos);
				end_of_storage = std::uninitialized_fill_n(End, n - sz, val);
				start = pos;
				End = pos + n;
			}
		}
		void reserve(size_type n)
		{
			if (n > size())
			{
				iterator pos = data_allocator.allocate(n);
				for (auto it = start; it != End; it++)
					destroy(it);
				End = std::uninitialized_copy(start, End, pos);
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
				std::cerr << "空的!" << std::endl;
				std::exit(1);
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
			if (empty())
			{
				push_back(v);
				return begin();
			}
			iterator new_end = End + 1;
			construct(End, *(End - 2));
			std::copy_backward(pos, End, new_end);
			*pos = v;
			End = new_end;
			end_of_storage++;
			return pos;
		}
		iterator insert(iterator pos, const size_type &n, const value_type &val)
		{
			size_type index = pos - start;
			check(n);
			pos = start + index;
			iterator new_end = End + n;
			size_type after_num = End - pos;
			if (after_num > n)
			{
				std::uninitialized_copy(End - n, End, End);
				End += n;
				std::copy_backward(pos, End - n, End);
				std::fill(pos, pos + n, val);
				return pos;
			}
			else
			{
				/*std::uninitialized_fill_n(End, n - after_num, val);
				std::uninitialized_copy(pos, End, End + n - after_num);
				std::fill(pos, End, val);
				End += n;*/
				iterator old_end = End;
				std::uninitialized_fill_n(End, n - after_num, val);
				End += n - after_num;
				std::uninitialized_copy(pos, old_end, End);
				End += after_num;
				std::fill(pos, old_end, val);
			}
		}
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)//还是先只写 前向迭代器
		{
			size_type add_num = last - first, index = pos - start,after_num = End - pos;
			check(add_num);
			pos = start + index;
			if (pos > End) pos = End;
			if (pos <= End - add_num)
			{
				std::uninitialized_copy(End - add_num, End, End);
				std::copy_backward(pos, End - add_num, End);
				std::copy(first, last, pos);
				End += add_num;
			}
			else
			{
				iterator new_end = End + add_num;
				std::uninitialized_copy(pos, End, new_end - after_num);
				std::copy_n(first, after_num, pos);
				std::uninitialized_copy_n(first + after_num, add_num - after_num, End);
				End += add_num;
			}
		}
		iterator erase(iterator pos)
		{
			std::copy(pos + 1, End, pos);
			destroy(End - 1);
			End--;
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			std::copy(last, End, first);
			for (auto it = End - (last - first); it != End; it++)
				destroy(it);
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
		bool operator==( vector<T,Alloc>& rhs)
		{
			if (size() != rhs.size())
				return false;
			else
			{
				auto it = begin();
				auto j = rhs.begin();
				for (; it != end(); )
				{
					if (*it != *j)
						return false;
					else
						it++, j++;
				}
				return true;
			}
		}
		bool operator!=( vector<T,Alloc>& rhs)
		{
			return !(*this == rhs);
		}
	};
		
}
#endif
