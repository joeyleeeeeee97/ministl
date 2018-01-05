#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H
#include"memory.h"
#include"algorithm.h"
#include"Memory/construct.h"
#include"Memory/allocator.h"
#include"iterator.h"
namespace ministl
{
	template<class T, class Alloc = ministl::allocator<T> >
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
		void DestroyAndDeallocateAll()
		{
			//	Print();
			if (capacity() == 0) return;
			for (iterator it = start; it != End; it++)
				destroy(it);
			data_allocator.deallocate(start, end_of_storage - start);
		}
	protected:
		iterator start, End, end_of_storage;
		void reallocate(size_t new_size = 0)
		{
			if (new_size == 0)
				new_size = size() == 0 ? 1 : 2 * size();
			iterator new_start = data_allocator.allocate(new_size);
			if (new_start == nullptr)
			{
				std::cerr << "out of memory" << std::endl;
				std::exit(1);
			}
			iterator new_End = ministl::uninitialized_copy(start, End, new_start);
			DestroyAndDeallocateAll();
			start = new_start;
			End = new_End;
			end_of_storage = start + new_size;
		}
	public:
		//for Debug
		void Print()
		{
			/*	cout << "size() is " << size() << endl;
				cout << " capacity() is " << capacity() << endl;*/
			for (iterator it = start; it != End; it++)
				std::cout << *it << std::endl;
		}
		//Constructor
		vector()
		{
			End = end_of_storage = start = nullptr;
		}
		vector(size_t n, value_type val = value_type())
		{
			start = data_allocator.allocate(n);
			End = end_of_storage = start + n;
			ministl::uninitialized_fill_n(start, n, val);
		}
		vector(iterator first, iterator last)
		{
			start = data_allocator.allocate(last - first);
			End = end_of_storage = uninitialized_copy(first, last, start);
		}
		vector(const vector<T, Alloc> &rhs)
		{
			assign(rhs.start, rhs.End);
		}
		vector(vector<T, Alloc> &&rhs)
		{
			if (this != &rhs)
			{
				DestroyAndDeallocateAll();
				start = rhs.start, End = rhs.End, end_of_storage = rhs.end_of_storage;
				rhs.start = rhs.end_of_storage = rhs.End = nullptr;//可析构的状态
			}
		}
		vector(const std::initializer_list<T>& l)
		{
			start = data_allocator.allocate(l.size());
			End = end_of_storage = uninitialized_copy(l.begin(), l.end(), begin());
		}
		//Destructor
		~vector() { DestroyAndDeallocateAll(); }
		//Iterator
		//为什么这个不能 vector<int>::iterator = v.end()--;
		const iterator begin() const { return start; }
		const iterator end() const { return End; }
		iterator begin() { return start; }
		iterator end() { return End; }
		//Elemnt access
		value_type& operator [](size_type n)
		{
			if (n >= size())
			{
				std::cerr << "Out of range" << std::endl;
				std::exit(1);
			}
			return *(start + n);
		}
		value_type& front()
		{
			if (empty())
			{
				std::cerr << "front on empty vector" << std::endl;
				std::exit(1);
			}
			return *(start);
		}
		value_type& back()
		{
			if (empty())
			{
				std::cerr << "back on empty vector" << std::endl;
				std::exit(1);
			}
			return *(End - 1);
		}
		//Capacity
		size_type size()
		{
			return End - start;
		}
		size_type size() const
		{
			return End - start;
		}
		size_type capacity()
		{
			return end_of_storage - start;
		}
		//没有必要每次都重新分配空间 可以分为 小于size的情况 小于cap的情况 大于cap的情况
		void resize(size_type new_size, value_type val = value_type())
		{	
			if (new_size < size())
			{
				for (iterator it = start + new_size; it != End; it++)
				{
					destroy(it);
				}
				End = start + new_size;
			}
			else if (new_size < capacity())
			{
				uninitialized_fill_n(End, new_size - size(), val);
				End = start + new_size;
			}
			else
			{
				reallocate(new_size);
				uninitialized_fill_n(End, new_size - size(), val);
				End = start + new_size;
			}
		}
		void reserve(size_type n)
		{
			if (n <= capacity()) return;
				reallocate(n);
		}
		bool empty()
		{
			return start == End;
		}
		//Modifiers
		void push_back(value_type data)
		{
			if (capacity() == size())
				reallocate();
			construct(End++, data);
		}
		void pop_back()
		{
			if (empty())
			{
				std::cerr << "pop on empty" << std::endl;
				std::exit(1);
			}
			End--;
			destroy(End);
		}
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last)//��ֻ���ָ���
		{
			DestroyAndDeallocateAll();
			start = data_allocator.allocate(last - first);
			End = end_of_storage = uninitialized_copy(first, last, start);
		}
		void assign(size_type n, const value_type &v)
		{
			DestroyAndDeallocateAll();
			start = data_allocator.allocate(n);
			End = end_of_storage = start + n;
			uninitialized_fill_n(start, n, v);
		}
		iterator insert(iterator pos, const value_type &v)
		{
			if (pos == end())
			{
				push_back(v);
				return &back();
			}
			if (size() == capacity())
				reallocate();
			iterator new_end = End + 1;
			data_allocator.construct(new_end, v);
			copy_backward(pos, End, new_end);
			*pos = v;
			End = new_end;
			end_of_storage++;
			return pos;
		}
		iterator insert(iterator pos, const size_type &n, const value_type &val)
		{
			size_type index = pos - start;
			if (n + size() > capacity())
				reserve(n + size());
			pos = start + index;
			iterator new_end = End + n;
			size_type after_num = End - pos;
			if (after_num > n)
			{
				uninitialized_copy(End - n, End, End);
				End += n;
				copy_backward(pos, End - n, End);
				fill(pos, pos + n, val);
				return pos + n;
			}
			else
			{
				iterator old_end = End;
				uninitialized_fill_n(End, n - after_num, val);
				End += n - after_num;
				uninitialized_copy(pos, old_end, End);
				End += after_num;
				fill(pos, old_end, val);
				return pos + n;
			}
		}
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)//������ֻд ǰ�������
		{

			size_type add_num = last - first, index = pos - start, after_num = End - pos;
			if (add_num + size() > capacity())
				reserve(add_num + size());
			pos = start + index;
			if (pos > End) pos = End;
			if (pos <= End - add_num)
			{
				uninitialized_copy(End - add_num, End, End);
				copy_backward(pos, End - add_num, End);
				copy(first, last, pos);
				End += add_num;
			}
			else
			{
				iterator new_end = End + add_num;
				uninitialized_copy(pos, End, new_end - after_num);
				copy_n(first, after_num, pos);
				uninitialized_copy_n(first + after_num, add_num - after_num, End);
				End += add_num;
			}
		}
		iterator erase(iterator pos)
		{
			copy(pos + 1, End, pos);
			destroy(End - 1);
			End--;
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			copy(last, End, first);
			for (auto it = End - (last - first); it != End; it++)
				destroy(it);
			End = End - (last - first);
			return last;
		}
		void clear()
		{
			DestroyAndDeallocateAll();
			End = start;
		}
		void swap(vector<T, Alloc> &rhs)
		{
			iterator tmp;
			tmp = start, start = rhs.start, rhs.start = tmp;
			tmp = End, End = rhs.End, rhs.End = tmp;
			tmp = end_of_storage, end_of_storage = rhs.end_of_storage, rhs.end_of_storage = tmp;
		}
		bool operator==(vector<T, Alloc>& rhs)
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
		bool operator!=(vector<T, Alloc>& rhs)
		{
			return !(*this == rhs);
		}
		void operator=(const vector<T, Alloc>& rhs)
		{
			if (this != &rhs)
			{
				assign(rhs.begin(), rhs.end());
				/*vector<T, Alloc> tmp(rhs.begin(), rhs.end());
				ministl::swap(*this, rhs);*/
			}
		}
	};
	
	template<class T>
	void swap(vector<T>& a, vector<T>& b)
	{
		a.swap(b);
	}
}
#endif