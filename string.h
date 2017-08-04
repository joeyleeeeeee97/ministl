#pragma once
#ifndef _STRING_H
#define _STRING_H
#include"allocator.h"
namespace ministl
{
	class string
	{
	public:
		typedef size_t size_type;
		typedef char* iterator;
		typedef char value_type;
	private:
		char *start, *End, *finish;
		allocator<char> data_allocator;
		void reallocate()
		{
			int old_size = size();
			int new_size = size() ? 2 * size() : 1;
			char* new_start = data_allocator.allocate(new_size);
			std::uninitialized_copy(start, start + size(), new_start);
			start = new_start;
			finish = new_start + old_size;
			End = new_start + new_size;
		}
	public:
		//Construct
		string()
		{
			start = End = finish = nullptr;
		}
		string(const char* s)
		{
			if (s == nullptr)
				string();
			else
			{
				int cnt = 0;
				for(;s[cnt]!='\0';cnt++){}
				start = data_allocator.allocate(cnt);
				std::uninitialized_copy_n(s, cnt, start);
				End = finish = start + cnt;
			}
		}
		//Iterator
		iterator begin()
		{
			return start;
		}
		iterator end()
		{
			return finish;
		}
		//Capacity
		void clear()
		{
			finish = start;
		}
		bool empty()const
		{
			return (start == finish);
		}
		const size_type size() const
		{
			return finish - start;
		}
		const size_type capacity() const
		{
			return End - start;
		}
		//Modifiers
		value_type& operator[](size_type index)
		{
			if (index < 0 || index >= size())
			{
				std::cerr << "index out of range!" << std::endl;
				std::exit(1);
			}
			else
			{
				return *(start + index);
			}
		}
		void push_back(const value_type& val)
		{
			if (size() == capacity())
				reallocate();
			*finish = val;
			finish++;
		}
		void append(const string& rhs)
		{
			size_type old_sz = size(), add_num = rhs.size();
			size_type nsz = rhs.size() + size();
			iterator new_start = data_allocator.allocate(nsz);
			std::uninitialized_copy_n(start, old_sz, new_start);
			std::uninitialized_copy_n(rhs.start, add_num, new_start + old_sz);
			start = new_start;
			End = finish = new_start + nsz;
		}
		void operator+=(const string& rhs)
		{
			(*this).append(rhs);
		}
		string operator+(const string& rhs)
		{
			string tmp(*this);
			tmp += rhs;
			return tmp;
		}
	
	};
}

#endif