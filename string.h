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
		string(size_type n, char c)
		{
			start = data_allocator.allocate(n);
			std::uninitialized_fill_n(start, n, c);
			End = finish = start + n;
		}
		string(const char* s, size_t n)
		{
			start = data_allocator.allocate(n);
			std::uninitialized_copy_n(s, n, start);
			finish = End = start + n;
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
		const size_type length() const
		{
			return size();
		}
		const size_type capacity() const
		{
			return End - start;
		}
		void resize(size_type n)
		{
			resize(n, value_type());
		}
		void resize(size_type n, const value_type &val)
		{
			if (n <= size())
			{
				finish = start + n;
			}
			else
			{
				append(string(n - size(), val));
			}
		}
		void reserve(size_type res_arg = 0)
		{
			if (res_arg > capacity())
			{
				iterator new_start = data_allocator.allocate(size() + res_arg);
				std::uninitialized_copy(start, finish, new_start);
				finish = new_start + size();
				End = finish + res_arg;
				if(start)
					data_allocator.deallocate(start, size());			
				start = new_start;
			}
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
		value_type& front()
		{
			return *start;
		}
		value_type& back()
		{
			auto tmp = End;
			tmp--;
			return *tmp;
		}
		void push_back(const value_type& val)
		{
			if (size() == capacity())
				reallocate();
			*finish = val;
			finish++;
		}
		void pop_back()
		{
			finish--;
		}
		void swap(string& rhs)
		{
			std::swap(start, rhs.start);
			std::swap(End, rhs.End);
			std::swap(finish, rhs.finish);
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
		void append(const char* s)
		{
			append(string(s));
		}
		void append(const char* s, size_t l, size_t r)
		{
			append(string(s + l, r - l));
		}
		string& operator+=(const char c)
		{
			(*this).push_back(c);
			return *this;
		}
		string& operator+=(const string& rhs)
		{
			(*this).append(rhs);
			return *this;
		}
		string operator+(const string& rhs)
		{
			string tmp(*this);
			tmp += rhs;
			return tmp;
		}
		string& operator=(const string& str)
		{
			return assign(str);
		}
		string& operator=(const char* s)
		{
			return assign(string(s));
		}
		string& operator=(char c)
		{
			return assign(string((size_type)1, c));
		}
		string& assign(const string& str)
		{
			clear();
			append(str);
			return (*this);
		}
		string& assign(const char* s)
		{
			return assign(string(s));
		}
		string& assign(size_type n, char c)
		{
			return assign(string(n, c));
		}
		string& insert(size_type pos, const string& rhs)
		{
			pos = std::min(size(), pos);
			size_type new_size = size() + rhs.size();
			iterator new_start = data_allocator.allocate(new_size);
			std::uninitialized_copy(start, start + pos, new_start);
			std::uninitialized_copy(rhs.start, rhs.finish, new_start + pos);
			std::uninitialized_copy(start + pos, finish, new_start + pos + rhs.size());
			start = new_start;
			End = finish = new_size + new_start;
			return *this;
		}
		string& insert(size_type pos, const char* s, size_type n)
		{
			return insert(pos, string(s, n));
		}
		string& insert(size_type pos, const char* s)
		{
			return insert(pos, string(s));
		}
		iterator insert(iterator pos, const value_type& val)
		{
			size_type index = pos - start;
			if (size() == capacity())
				reallocate();
			pos = start + index;
			if (pos > end()) pos = end();
			std::copy(pos, finish, pos + 1);
			(*pos) = val;
			finish++;
			return pos;
		}
		string& insert(size_type pos, size_type num, const value_type& val)
		{
			return insert(pos , string(num, val));
		}
		string& insert(iterator pos, size_type num, const value_type& val)
		{
			return insert(pos - start, string(num, val));
		}
		string& erase(size_type pos, size_type n)
		{
			std::copy(pos + n + start, finish, start + pos);
			finish = finish - n;
			return *this;
		}
		iterator erase(iterator pos)
		{
			std::copy(pos + 1, finish, pos);
			finish--;
			return pos;
		}
		iterator erase(iterator first, iterator last)
		{
			std::copy(last, finish, first);
			finish = finish - (last - first);
			return first;
		}
		string& replace(size_t pos, size_t n, const string& str)
		{
			erase(pos, n);
			insert(pos, str);
			return *this;
		}
		string& replace(iterator i1, iterator i2, const string& str)
		{
			insert(erase(i1, i2) - start,str);
			return *this;
		}
		const char* c_str() const
		{
			return start;
		}
		bool operator == (const string& rhs)
		{
			if (size() != rhs.size())
				return false;
			else
			{
				for (auto i = start, j = rhs.start; i != finish; i++, j++)
				{
					if ((*i) != (*j))
						return false;
				}
				return true;
			}
		}
		int compare(const string& rhs)
		{
			iterator i = start, j = rhs.start;
			while (i != finish && j!=rhs.finish)
			{
				if ((*i) > (*j))
					return 1;
				else if ((*i) < (*j))
					return -1;
				else
					i++, j++;
			}
			if (i == finish&&j == rhs.finish)
				return 0;
			else if (i == finish)
				return -1;
			else
				return 1;
		}
		size_type copy(char* s, size_type n, size_type pos = 0) const
		{
			if (pos + n >= size())
			{
				std::cerr << "out of range" << std::endl;
				std::exit(1);
			}
			std::uninitialized_copy_n(start + pos, n, s);
			return n;
		}
		size_t find(const string& str, size_t pos = 0) const
		{
			if (size() - pos < str.size())
				return (size_type)(-1);
			for (auto it = start + pos; it != finish; it++)
			{
				auto i = it, j = str.start;
				while (j<str.finish && *i == *j)
					i++, j++;
				if (j == str.finish )
					return it - start;
			}
			return (size_type)(-1);
		}
		size_t find(const char* s, size_t pos, size_t n) const
		{
			return find(string(s, n), pos);
		}
		size_t find(const char* s, size_t pos = 0) const
		{
			return find(string(s), pos);
		}
		size_t find(char c, size_t pos = 0) const
		{
			if (empty())
				return size_type(-1);
			else
			{
				for (auto it = start; it != finish; it++)
					if (*it == c)
						return it - start;
				return size_type(-1);
			}
		}
		string substr(size_t pos = 0, size_t n = 0)
		{
			return string(start + pos, n);
		}
		size_t rfind(string& rhs, size_t pos = 0)
		{
			if (pos == 0) pos = size();
			for (auto it = std::min(start + pos, finish - 1); it != start -1 ; it--)
			{
				size_t i;
				for (i = 0; i < rhs.size();)
					if (rhs[i] == *(it + i))
						i++;
					else
						break;
				if (i == rhs.size())
					return it - start;
			}
			return size_t(-1);
		}
		size_t rfind(const char& c, size_t pos = 0)
		{
			if (pos == 0) pos = size();
			for (auto it = std::min(finish - 1,start+pos); it != start; it--)
			{
				if (*it == c)
					return it - start;
			}
			return size_t(-1);
		}
		size_t rfind(const char* str)
		{
			return rfind(string(str));
		}
		size_t find_first_of(const string& rhs, size_t pos = 0)
		{
			for (auto it = start + pos; it != finish; it++)
			{
				auto i = rhs.start;
				while (i != rhs.finish)
				{
					if (*i == *it)
						break;
					i++;
				}
				if (i != rhs.finish)
					return it - start;
			}
			return (size_t)-1;
		}
		size_t find_first_of(const char& c, size_t pos = 0)
		{
			for (auto it = start + pos; it != finish; it++)
			{
				if (*it == c)
					return it - start;
			}
			return (size_t)-1;
		}
		size_t find_last_of(const char &c, size_t pos = 0)
		{
			if (pos == 0) pos = size();
			for (auto it = pos + start; it != start - 1; it--)
				if (*it == c)
					return it - start;
			return (size_t)-1;
		}
		size_t find_last_of(const char* str, size_t pos, size_t len)
		{
			size_t l = 0;
			for (size_t i = 0; str[i] != '\0'; i++)
				l++;
			for (auto it = start + pos; it != start + pos - len; it--)
			{
				size_t i;
				for (i = 0; str[i] != '\0'; i++)
					if (str[i] == *it)
						break;
				if (str[i] != '\0') return it - start;
			}
			return size_t(-1);
		}
		size_t find_last_of(const string& rhs, size_t pos)
		{
			for (auto it = start + pos; it != start - 1; it--)
			{
				size_t i = 0;
				while (rhs.start + i != rhs.finish)
					if (*it == *(start + i))
						break;
					else
						i++;
				if (rhs.size() != i)	return it - start;
			}
			return size_t(-1);
		}
		size_t find_first_not_of(const string& rhs)
		{
			for (auto it = start; it != finish; it++)
			{
				size_t i = 0;
				while (i < rhs.size())
					if (*(rhs.start + i) == *it)
						break;
					else
						i++;
				if (i == rhs.size()) return it - start;
			}
			return size_t(-1);
		}
		size_t find_last_not_of(const string& rhs,size_t pos)
		{
			for (auto it = start + pos; it != start - 1; it--)
			{
				size_t i = 0;
				while (i < rhs.size())
					if (*(rhs.start + i) == *it)
						break;
					else
						i++;
				if (i == rhs.size()) return it - start;
			}
			return size_t(-1);
		}
		bool operator!=(const string& rhs)
		{
			return !(*this == rhs);
		}
		bool operator>(const string& rhs)
		{
			return compare(rhs) > 0;
		}
		bool operator>=(const string& rhs)
		{
			return compare(rhs) >= 0;
		}
		bool operator<(const string& rhs)
		{
			return compare(rhs) < 0;
		}
		bool operator<=(const string& rhs)
		{
			return compare(rhs) <= 0;
		}
	};

}

#endif