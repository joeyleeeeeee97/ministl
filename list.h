#pragma once
#ifndef _LIST_H
#define _LIST_H
#include"iterator.h"
#include"construct.h"
#include"allocator.h"
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
		typedef ministl::allocator<list_node<T>> Data_allocator;
		Data_allocator	data_allocator;
		node_ptr ptr;
		//Construct
		list_iterator()
		{
			ptr = nullptr;
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
		bool operator==(const iterator& x) const
		{
			return ptr == x.ptr;
		}
		bool operator!=(const iterator& x) const
		{
			return !(*this == x);
		}

		reference operator*() const { return (*ptr).data; }
		pointer operator->()const { return &(operator*()); }
		//++i
		iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		//i++
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
		typedef list<T> self;
		typedef list_iterator<T> iterator;
	private:
		typedef  std::allocator<list_node<T>> Data_allocator;
		Data_allocator data_allocator;
	protected:
		typedef list_node<T> list_node;
		iterator node;//最后一个迭代器
		node_ptr get_node()
		{
			return data_allocator.allocate(1);
		}
		node_ptr new_node(const T& x)
		{
			node_ptr p = get_node();
			construct(&p->data, x);
			p->next = p->pre = nullptr;
			return p;
		}
	public:
		//Construct
		list()
		{
			node.ptr = data_allocator.allocate(1);
			node.ptr->next = node.ptr->pre = node.ptr;
		}
		list(const self& rhs) :list(rhs.begin(), rhs.end())
		{
	
		}
		list(std::initializer_list<T> li):list(li.begin(),li.end())
		{

		}
		template<class c>
		list(const c l,const c r)
		{
			node.ptr = data_allocator.allocate(1);
			node.ptr->next = node.ptr->pre = node.ptr;
			for (auto it = l; it != r; it++)
			{
				push_back((*it));
			}
		}
		list(size_type n, const T& val)
		{
			node.ptr = data_allocator.allocate(1);
			node.ptr->next = node.ptr->pre = node.ptr;
			while (n--)
				push_back(val);
		}
		//Destructor
		~list()
		{
			if (!empty())
			{
				for (iterator it = begin(); it != end(); )
				{
					data_allocator.destroy(&it.ptr->data);
					it++;
				}
			}
		}
		//Iterators
		const iterator begin() const
		{
			return iterator(node.ptr->next);
		}
		const iterator end() const
		{
			return iterator(node.ptr);
		}
		iterator begin()
		{
			return iterator(node.ptr->next);
		}
		iterator end()
		{
			return iterator(node.ptr);
		}
		value_type& front()
		{
			return node.ptr->next->data;
		}
		value_type& back()
		{
			return node.ptr->pre->data;
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
			node_ptr tmp = pos.ptr->next;
			destroy(&pos.ptr->data);
			data_allocator.deallocate(pos.ptr,sizeof(list_node));
			return iterator(tmp);
		}
		iterator erase(iterator first, iterator last)
		{
			first.ptr->pre->next = last.ptr;
			last.ptr->pre = first.ptr->pre;
			for (auto it = first; it != last; it++)
				destroy(&it.ptr->data);
			return first;
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
		//this will loop forever when first-last is in list's range
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)
		{
			for (auto it = first; it != last; it++)
				insert(pos, (value_type)(*it));
		}
		void swap(list<T>& rhs)
		{
			iterator tmp = node;
			node = rhs.node;
			rhs.node = tmp;
		}
		void assign(size_type n, const T& x)
		{
			clear();
			insert(begin(), n, x);
		}

		void merge(list<T> &other)
		{
			auto p1 = begin(), p2 = other.begin();
			while (p1 != end() && p2 != other.end())
			{
				if (*p1 < *p2)
					p1++;
				else if (*p1 >= *p2)
				{
					insert(p1, *p2);
					p2++;
				}
			}
			while (p2 != other.end())
				insert(end(), *(p2++));
		}

		void remove(const T& x)
		{
			for (auto it = begin(); it != end(); )
			{
				if (*it == x)
					it = erase(it);
				else
					it++;
				
			}
		}

		
		template<typename fun>
		void remove_if(fun f)
		{
			for (auto it = begin(); it != end();)
			{
				//std::cout << "#" << *it << ' ';
				if (f(*it))
					it = erase(it);
				else
					it++;
			}
		}

		void reverse()
		{
			auto it = begin();
			for (; it != end();it--)
			{
				std::swap(it.ptr->next, it.ptr->pre);
			}
			std::swap(it.ptr->next, it.ptr->pre);
		}

		void unique()
		{
			for (auto it = begin(); it != end(); )
			{
				if ((it.ptr->data) == (it.ptr->next->data))
					erase(it.ptr->next);
				else
					it++;
			}
		}
		//void transfer(iterator position, iterator first, iterator last)
		//{
		//	if (position != last)   // 如果last == position, 则相当于链表不变化, 不进行操作  
		//	{
		//		(*(link_type((*last.node).prev))).next = position.node;  //（1）
		//		(*(link_type((*first.node).prev))).next = last.node;  //（2）
		//		(*(link_type((*position.node).prev))).next = first.node;  //（3）
		//		link_type tmp = link_type((*position.node).prev);  //（4）
		//		(*position.node).prev = (*last.node).prev;  //（5）
		//		(*last.node).prev = (*first.node).prev;  //（6）
		//		(*first.node).prev = tmp;  //（7）
		//	}
		//}
		void transfer(iterator pos, iterator first, iterator last)
		{
			if (pos != last)
			{
				last.ptr->pre->next = pos.ptr;
				first.ptr->pre->next = last.ptr;
				pos.ptr->pre->next = first.ptr;
				auto tmp = pos.ptr->pre;
				pos.ptr->pre = last.ptr->pre;
				last.ptr->pre = first.ptr->pre;
				first.ptr->pre = tmp;
			}
		}
		void splice(iterator pos, list<T>& rhs)
		{
			if (*this != rhs)
				transfer(pos, rhs.begin(), rhs.end());
		}
		void splice(iterator pos, list<T>& rhs, iterator first, iterator last)
		{
			if (*this != rhs)
				transfer(pos, first, last);
		}
		void splice(iterator pos, list<T>& rhs, iterator it)
		{
			T tmp = *it;
			insert(pos, tmp);
			rhs.erase(it);
		}
		bool operator == (list<T>& rhs)
		{
			if (size() != rhs.size())
				return false;
			auto i = begin();
			auto j = rhs.begin();
			while (i != end())
				if (*i != *j)
					return false;
				else
					i++, j++;
			return true;
		}
		bool operator !=(list<T>& rhs)
		{
			return !(*this == rhs);
		}
		list<T>& operator=(list<T>& rhs)
		{
			clear();
			node.ptr = data_allocator.allocate(1);
			node.ptr->next = node.ptr->pre = node.ptr;
			for (auto it = rhs.begin(); it != rhs.end(); i++)
				insert(begin(),*it);
			return *this;
		}
	};

	template<class T>
	void swap(list<T>& a, list<T>& b)
	{
		a.swap(b);
	}
}


#endif