#pragma once
#ifndef _LIST_H
#define _LIST_H
#include"iterator.h"
#include"construct.h"
namespace ministl
{
	template <class T>
	struct list_node
	{
		struct list_node<T>* next;
		struct list_node<T>* pre;
		T data;
	};
	template<class T>
	struct list_iterator
	{
		typedef T value_type;
		typedef T& reference;
		typedef list_iterator<T> iterator;
		typedef T* pointer;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef list_node<T> node_type;
		typedef node_type* node_ptr;
		typedef std::allocator<list_node<T>> Data_allocator;
		Data_allocator	data_allocator;
		node_ptr ptr;
		//Construct
		list_iterator()
		{
			ptr = data_allocator.allocate(1);
		}
		list_iterator(node_type p) :ptr(&p) {}
		list_iterator(node_ptr p) :ptr(p) {}

		void operator=(const list_iterator p)
		{
			ptr = p.ptr;
		}
		void operator=(const node_ptr p)
		{
			ptr = p;
		}

		bool operator==(const iterator& x)
		{
			return ptr == x.ptr;
		}
		bool operator!=(const iterator& x)
		{
			return !(*this == x);
		}

		reference operator*() const { return (*ptr).data; }
		pointer operator->()const { return &(operator*()); }

		iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++*this;
			return tmp;
		}

		iterator& operator--()
		{
			ptr = ptr->pre;
			return *this;
		}

		iterator operator--(int)
		{
			iterator tmp = *this;
			--*this;
			return tmp;
		}
	};
	//环状链表 node表示链表尾部的一个空白结点, 其next指向list头结点
	template<class T>
	class list
	{
	public:
		typedef list_node<T>* node_ptr;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef size_t size_type;
	private:
		typedef  std::allocator<list_node<T>> Data_allocator;
		Data_allocator data_allocator;
	protected:
		typedef list_node<T> list_node;
		typedef list_iterator<T> iterator;
		iterator node;//最后一个迭代器
		node_ptr get_node()
		{
			return data_allocator.allocate(1);
		}
		node_ptr new_node(const T& x)
		{
			node_ptr p = get_node();
			p->data = x;
			p->next = p->pre = nullptr;
			return p;
		}
	public:
		//Construct
		list():node()
		{
			node.ptr->next = node.ptr->pre = node.ptr;
		}
		//Iterators
		iterator begin()
		{
			return iterator(node.ptr->next);
		}
		iterator end()
		{
			return iterator(node.ptr);
		}
		//Capacity
		bool empty()
		{
			return begin() == end();
		}
		size_type size()
		{
			size_t cnt = 0;
			for (auto it = begin(); it != end(); it++)
				cnt++;
			return cnt;
		}
		//Modifiers
		void push_front(const T& x)
		{
			node_ptr p = new_node(x);
			node.ptr->next->pre = p;
			p->next = node.ptr->next;
			node.ptr->next = p;
			p->pre = node.ptr;
		}
		void push_back(const T& x)
		{
			node_ptr p = new_node(x);
			node.ptr->pre->next = p;
			p->pre = node.ptr->pre;
			p->next = node.ptr;
			node.ptr->pre = p;
		}
		void pop_front()
		{
			node_ptr tmp = node.ptr->next;
			node.ptr->next = node.ptr->next->next;
			node.ptr->next->pre = node.ptr;
			data_allocator.deallocate(tmp,sizeof(list_node));
		}
		void pop_back()
		{
			node_ptr tmp = node.ptr->pre;
			node.ptr->pre = tmp->pre;
			tmp->pre->next = node.ptr;
			data_allocator.deallocate(tmp, sizeof(list_node));
		}
		void clear()
		{
			for (auto it = begin(); it != end(); it++)
				destroy(it.ptr);
			node.ptr->next = node.ptr->pre = node.ptr;
		}
		iterator erase(iterator pos)
		{
			pos.ptr->pre->next = pos.ptr->next;
			pos.ptr->next->pre = pos.ptr->pre;
			return iterator(pos.ptr->next);
		}
		//The list container is extended by inserting new elements before the element at position.
		iterator insert(iterator pos, const T& x)
		{
			node_ptr p = new_node(x);
			pos.ptr->pre->next = p;
			p->pre = pos.ptr->pre;
			p->next = pos.ptr;
			pos.ptr->pre = p;
			return pos;
		}

		void insert(iterator pos, size_type sz, const T& x)
		{
			while (sz--)
				insert(pos, x);
		}
		/*template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)
		{
			for (auto it = first; it != last; it++)
				insert(pos, (value_type)(*it));
		}*/
		void swap(list<T> rhs)
		{
			node_ptr tmp = node.ptr;
			node.ptr = rhs.node.ptr;
			rhs.node.ptr = tmp;
		}
		void assign(size_type n, const T& x)
		{
			clear();
			insert(begin(), n, x);
		}
	};
}


#endif
