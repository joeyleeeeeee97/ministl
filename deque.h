#pragma once

#ifndef _DEQUE_H
#define _DEQUE_H
namespace ministl
{
	inline size_t _deque_buf_size(size_t n, size_t sz)
	{
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	}
	template<class T, size_t Bufsize = 0>
	struct _deque_iterator
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
	deque 除了维护一个先前说过的指向map的指针外，也维护start finish 两个迭代器，分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素，同时管理当前map的大小，在节点不足时重新分配内存
	*/
	template<class T,class Alloc = allocator<T>,size_t Buf_size = 0>
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
					uninitialized_fill(*cur, *cur + buffer_size(), val);
				uninitialized_fill(finish.first, finish.last, val);
			}
			catch (...)
			{

			}
		}
	public:
		//Construct
		deque() :start(), finish(), map(0), map_size(0) {}
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

	};
}

#endif