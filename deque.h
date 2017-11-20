#pragma once

#ifndef _DEQUE_H
#define _DEQUE_H
#include<memory>
#include"iterator.h"
namespace ministl
{
	inline size_t _deque_buf_size(size_t n, size_t sz)
	{
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	}
	template<class T, size_t Bufsize = 0>
	struct _deque_iterator :  public random_access_iterator<T>
	{
		typedef _deque_iterator<T> iterator;

		static size_t buffer_size()
		{
			return _deque_buf_size(Bufsize, sizeof(T));
		}

		//typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T** map_pointer;

		typedef _deque_iterator self;


		_deque_iterator()
		{
			cur = first = last = NULL;
			node = NULL;
		}
		T* cur;//此迭代器所指缓冲区中的元素
		T* first;//缓冲区开头元素
		T* last;//缓冲区尾部元素
		map_pointer node;//缓冲区控制器

		void set_node(map_pointer new_node)
		{
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_size());
		}

		reference operator*() const
		{
			return *cur;
		}
		pointer operator->() const
		{
			return &(operator*());
		}
		difference_type operator-(const self& x)const
		{
			return difference_type(buffer_size())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
		}
		self& operator++()
		{
			++cur;
			if (cur == last)
			{
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}
		self operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		}
		self& operator--()
		{
			--cur;
			if (cur == first)
			{
				set_node(node - 1);
				cur = last;
			}
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			--*this;
			return tmp;
		}
		//随机存取
		self& operator+=(difference_type n)
		{
			difference_type offset = n + (cur - first);
			if (offset >= 0 && offset < (difference_type)(buffer_size()))
				cur += n;//在当前的缓冲块内部
			else
			{
				difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size())
					: -difference_type((-offset - 1) / buffer_size()) - 1;
				set_node(node + node_offset);
				cur = first + (offset - node_offset*difference_type(buffer_size()));
			}
			return *this;
		}
		self operator+(difference_type n) const
		{
			self tmp = *this;
			return tmp += n;
		}

		self& operator-=(difference_type n)
		{
			return *this += -n;
		}
		self operator-(difference_type n)const
		{
			self tmp = *this;
			return tmp -= n;
		}
		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		bool operator==(const self &x) { return x.cur == cur; }
		bool operator!=(const self &x)
		{
			return !(*this==x);
		}
		bool operator<(const self& x)
		{
			return (node == x.node) ? (cur < x.cur) : (node < x.node);//优先比较缓冲区！
		}
	};

	/*
	deque 除了维护一个先前说过的指向map的指针外，也维护start finish 两个迭代器，
	分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素，
	同时管理当前map的大小，在节点不足时重新分配内存
	*/
	template<class T,size_t Buf_size = 0>
	class deque
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
		typedef _deque_iterator<T> iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		static size_t buffer_size()
		{
			return _deque_buf_size(Buf_size, sizeof(T));
		}
	protected:
		typedef pointer* map_pointer;
		iterator start, finish;
		map_pointer map;
		size_type map_size;
		std::allocator<T> data_allocator;
		std::allocator<pointer> map_allocator;
		void create_map_and_nodes(size_type num_elements)
		{
			size_type num_nodes = num_elements / buffer_size() + 1;
			map_size = std::max((size_t)8, num_nodes + 2);
			map = map_allocator.allocate(map_size);
			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;
			map_pointer cur;
			try
			{
				for (cur = nstart; cur <= nfinish; cur++)
					*cur = data_allocator.allocate(buffer_size());
			}
			catch (...)
			{

			}
			start.set_node(nstart);
			finish.set_node(nfinish);
			start.cur = start.first;
			finish.cur = finish.first + num_elements%buffer_size();
		}
		void fill_initialize(size_t n,const value_type& val)
		{
			create_map_and_nodes(n);
			map_pointer cur;
			try
			{
				for (cur = start.node; cur < finish.node; cur++)
					std::uninitialized_fill(*cur, *cur + buffer_size(), val);
				std::uninitialized_fill(finish.first, finish.last, val);
			}
			catch (...)
			{

			}
		}
		void reallocate_map(size_type nodes_to_add, bool add_at_front)
		{
			size_type old_num_nodes = finish.node - start.node + 1;
			size_type new_num_nodes = old_num_nodes + nodes_to_add;

			map_pointer new_start;
			if (map_size > 2 * new_num_nodes)
			{
				new_start = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
				if (new_start < start.node)
					std::copy(start.node, finish.node + 1, new_start);
				else
					std::copy_backward(start.node, finish.node + 1, new_start + old_num_nodes);
			}
			else
			{
				size_type new_map_size = map_size + std::max(map_size, nodes_to_add) + 2;
				map_pointer new_map = map_allocator.allocate(new_map_size);
				new_start = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
				std::copy(start.node, finish.node + 1, new_start);
				map = new_map;
				map_size = new_map_size;
			}
		}
		void push_front_aux(const value_type& val)
		{
			if (start.node - map < 1)
				reallocate_map(1, true);
			*(start.node - 1) = data_allocator.allocate(buffer_size());
			try
			{
				start.set_node(start.node - 1);
				start.cur = start.last - 1;
				data_allocator.construct(start.cur, val);
			}
			catch (...)
			{
				start.set_node(start.node + 1);
				start.cur = start.first;
				data_allocator.deallocate(*(start.node - 1),buffer_size());
				throw;
			}
		}
		void push_back_aux(const value_type& val)
		{
			if (map_size - (finish.node - map) < 2)
				reallocate_map(1, false);
			*(finish.node + 1) = data_allocator.allocate(buffer_size());
			try
			{
				data_allocator.construct(finish.cur, val);
				finish.set_node(finish.node + 1);
				finish.cur = finish.first;
			}
			catch (...)
			{
				data_allocator.deallocate(*(finish.node + 1),buffer_size());
			}
		}
	public:
		//Construct
		deque() :start(), finish(), map(), map_size(0) 
		{
			fill_initialize(0, value_type());
		}
		deque(int n, const value_type& val)
		{
			deque();
			fill_initialize(n, val);
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
		reference operator[](size_type n)
		{
			return start[(difference_type)n];
		}
		reference front()
		{
			return *start;
		}
		reference back()
		{
			return *(finish - 1);
		}
		size_type size()
		{
			return finish - start;
		}
		size_type max_size() { return size_type(-1); }
		bool empty() { return finish == start; }
		//Modifiers
		void push_back(const value_type& val)
		{
			if (finish.cur != finish.last - 1)
			{
				data_allocator.construct(finish.cur, val);
				++finish.cur;
			}
			else
				push_back_aux(val);
		}
		void push_front(const value_type& val)
		{
			if (start.cur != start.first)
			{
				data_allocator.construct(start.cur - 1, val);
				--start.cur;
			}
			else
				push_front_aux(val);
		}
		void clear()
		{
			for (auto it = start.cur + 1; it < finish.cur; it++)
				data_allocator.destroy(it);
			for (auto it = start.node + 1; it <= finish.node; it++)
				map_allocator.destroy(it),map_allocator.deallocate(it,1);
			finish = start;
		}
		void pop_back()
		{
			if (finish.cur != finish.first)
			{
				--finish.cur;
				data_allocator.destroy(finish.cur);
			}
			else
			{
				data_allocator.deallocate(finish.first,buffer_size());
				finish.set_node(finish.node - 1);
				finish.cur = finish.last - 1;
				data_allocator.destroy(finish.cur);
			}
		}
		void pop_front()
		{
			if (start.cur != start.last - 1)
			{
				data_allocator.destroy(start.cur);
				start.cur++;
			}
			else
			{
				destroy(start.cur);
				set_node(start.node + 1);
				start.cur = start.first;
			}
		}

		iterator erase(iterator pos)
		{
			iterator next = pos++;
			difference_type index = pos - start;
			if (index < size() / 2)
			{
				copy_backward(start, pos, next);
				pop_front();
			}
			else
			{
				copy(next, finish, pos);
				pop_back();
			}
			return start + index;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == start&&last == finish)
			{
				clear();
				return finish;
			}
			else
			{
				difference_type n = last - first;
				difference_type elems_before = first - start;
				if (elems_before < (size() - n) / 2)//如果前方的元素较少
				{
					copy_backward(start, first, last);
					iterator new_start = start + n;
					for (auto it = start; it < new_start; it++)
						data_allocator.destroy(it);
					for (auto it = start; it < new_start; it++)
						data_allocator.deallocate(it, buffer_size());
					start = new_start;
				}
				else
				{
					copy(last, finish, first);
					iterator new_finish = finish - n;
					for (auto it = new_finish; it < finish; it++)
						data_allocator.destroy(it);
					for (auto it = new_finish; it < finish; it++)
						data_allocator.deallocate(it, buffer_size());
					finish = new_finish;
				}
				return start + elems_before;
				
			}
		}

		iterator insert(iterator pos, const value_type& x)
		{
			if (pos.cur == start.cur)
			{
				push_front(x);
				return start;
			}
			else if (pos.cur == finish.cur)
			{
				push_back(x);
				return finish - 1;
			}
			else
			{
				difference_type index = pos - start;
				value_type x_copy = x;
				if (index < size() / 2)
				{
					push_front(front());
					iterator front1 = start;
					++front1;
					iterator front2 = front1;
					++front2;
					pos = start + index;
					iterator pos1 = pos;
					++pos1;
					copy(front2, pos1, front1);

				}
				else
				{
					push_back(back());
					iterator back1 = finish;
					--back1;
					iterator back2 = back1;
					--back2;
					pos = start + index;
					copy_backward(pos, back2, back1);
				}
				*pos = x_copy;
				return pos;
			}
		}
	};
}

#endif