#pragma once
#ifndef _TREE_H
#define _TREE_H
#include "functional.h"
#include "Memory/allocator.h"
#include "utility.h"
#include "iterator.h"
#include "Container/queue.h"
namespace ministl
{
	//Binary search Tree
	template<typename T>
	struct BSnode
	{
		BSnode():left(nullptr),parent(nullptr),right(nullptr){}
		T data;
		struct BSnode* parent;
		struct BSnode* left;
		struct BSnode* right;
	};
	template<typename T>
	class BStree_base_iterator : public bidirectional_iterator<T>
	{
	public:
		typedef BSnode<T>* ptr;
		ptr node;
		BStree_base_iterator()
		{
			node = nullptr;
		}
		BStree_base_iterator(ptr p)
		{
			node = p;
		}
		void increment()
		{
			if (node->right == nullptr)
			{
				ptr pre = node->parent;
				while (pre != nullptr&&node == pre->right)
				{
					node = pre;
					pre = node->parent;
				}
				if (pre == nullptr)
					node = nullptr;
				else
					node = pre;
			}
			else
			{
				node = node->right;
				while (node->left)
					node = node->left;
			}
		}
		void decrement()
		{
			if (node->left == nullptr)
			{
				ptr pre = node->parent;
				while (pre != nullptr&&node == pre->left)
				{
					node = pre;
					pre = node->parent;
				}
				if (pre == nullptr)
					node = nullptr;
				else
					node = pre;
			}
			else
			{
				node = node->left;
				while (node->right)
					node = node->right;
				//return node;
			}
		}
	};
	template<typename T>
	class BStree_iterator 
	{
	public:
		typedef BSnode<T>* ptr;
		typedef  BStree_iterator<T> self;
		BStree_base_iterator<T> p;
		BStree_iterator()
		{
			p.node = nullptr;
		}
		BStree_iterator(ptr _p)
		{
			p.node = _p;
		}
		self& operator++(int)
		{
			p.increment();
			return *this;
		}
		self& operator--(int)
		{
			p.decrement();
			return *this;
		}
		bool operator!=(const  BStree_iterator<T>& rhs)
		{
			return !(*this == rhs);
		}
		bool operator==(const  BStree_iterator<T>& rhs)
		{
			return this->p.node == rhs.p.node;
		}
		T& operator*()
		{
			return p.node->data;
		}
		T& operator->()
		{
			return &(*this);
		}
	};
	template<typename T >
	class BStree
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef size_t size_type;
		typedef BSnode<T>* node_ptr;
		typedef BStree<T> self;
		typedef BStree_iterator<T> iterator;
	private:
	//	Compare comparator;
		node_ptr node;
		size_t data_cnt;
		std::allocator<BSnode<T>> data_allocator;
		node_ptr new_node(const value_type& val,node_ptr pre)
		{
			node_ptr p = data_allocator.allocate(1);
			new(&p->data) value_type(val);
			p->left = nullptr;
			p->right = nullptr;
			p->parent = pre;
			return p;
		}
		node_ptr insert_aux(node_ptr p, node_ptr pre,const value_type& val, node_ptr& ret)
		{
			while (p)
			{
				if (p->data == val) return p;
				pre = p;
				p = p->data > val ? p->left : p->right;
			}
			return new_node(val, pre);

			/* 递归版本
			if(!p)
			{
				return ret = new_node(val, pre);
			}
			if (p->data > val)
				p->left = insert_aux(p->left, p, val, ret);
			else if (p->data < val)
				p->right = insert_aux(p->right, p, val, ret);
			else
				ret = p;
			return p;*/
		}
		iterator find_aux(node_ptr p, const value_type& val)
		{
			while (p && p->data != val)
			{
				p = p->data > val ? p->left : p->right;
			}
			return iterator(p);
		}
		void del()
		{
			ministl::queue<node_ptr> q;
			q.push(node);
			while (!q.empty())
			{
				node_ptr p = q.front();
				q.pop();
				if (p->left)
				{
					q.push(p->left);
				}
				if (p->right)
				{
					q.push(p->right);
				}
				delete p;
			}
			node = nullptr;
		}
		void erase_aux(node_ptr p)
		{
			if (p->left == nullptr&&p->right == nullptr)
			{
				if (p->parent == nullptr)
				{
					node = nullptr;
				}
				else if (p->parent->left!=nullptr && p->parent->left->data == p->data)
					p->parent->left = nullptr;
				else if (p->parent->right!=nullptr && p->parent->right->data == p->data)
					p->parent->right = nullptr;
				delete(p);
			}
			else if (p->left == nullptr&&p->right != nullptr)
			{
				if (p->parent == nullptr)
				{
					node = p->right,node->parent = nullptr;
				}
				else if (p->parent->left!=nullptr && p->parent->left->data == p->data)
					p->parent->left = p->right, p->right->parent = p->parent;
				else if (p->parent->right!=nullptr && p->parent->right->data == p->data)
					p->parent->right = p->right, p->right->parent = p->parent;
				delete(p);
			}
			else if (p->left != nullptr&&p->right == nullptr)
			{
				if (p->parent == nullptr)
				{
					node = p->left, node->parent = nullptr;
				}
				else if (p->parent->left!=nullptr && p->parent->left->data == p->data)
					p->parent->left = p->left, p->left->parent = p->parent;
				else if (p->parent->right!=nullptr && p->parent->right->data == p->data)
					p->parent->right = p->left, p->left->parent = p->parent;
				delete(p);
			}
			else
			{
				node_ptr it = p->left;
				node_ptr tmp = p;
				while (it->right != nullptr)
				{
					tmp = it, it = it->right;
				}
				p->data = it->data;
				if (tmp != p)
				{
					tmp->right = it->left;
				}
				else
				{
					tmp->left = it->left;
				}
				if (it->left != nullptr)
					it->left->parent = tmp;
				delete(it);
			}
		}
		iterator lower_bound_aux(node_ptr p, const value_type& x)
		{
			if (!p)
				return iterator(nullptr);
			if (p->data >= x)
			{
				auto tmp = lower_bound_aux(p->left, x);
				if (tmp.p.node != nullptr)
					return tmp;
				else
					return iterator(p);
			}
			else
				return lower_bound_aux(p->right, x);
		}
		iterator upper_bound_aux(node_ptr p, const value_type& x)
		{
			if (!p)
				return iterator(nullptr);
			if (p->data > x)
			{
				auto tmp = upper_bound_aux(p->left, x);
				if (tmp.p.node != nullptr)
					return tmp;
				else
					return iterator(p);
			}
			else
				return upper_bound_aux(p->right, x);
		}
		void erase_val_aux(node_ptr p,const value_type& key)
		{
			if (p == nullptr)
				return;
			if (p->data == key)
				erase_aux(p);
			else if (p->data < key)
				erase_val_aux(p->right, key);
			else if (p->data > key)
				erase_val_aux(p->left, key);
		}
	public:
		BStree() :node(nullptr),data_cnt(0) {}
		bool empty()
		{
			return node == nullptr;
		}
		size_type size()
		{
			return data_cnt;
		}
		iterator begin()
		{
			if (node == nullptr)
			{
				iterator t(nullptr);
				return t;
			}
			iterator it(node);
			while (it.p.node->left != nullptr)
				it.p.node = it.p.node->left;
			return it;
		}
		iterator end()
		{
			iterator it(nullptr);		
			return  (it);
		}
		iterator find_max()
		{
			node_ptr p = node;
			if (p == nullptr)
				return iterator(nullptr);
			while (p->right != nullptr)
				p = p->right;
			return iterator(p);
		}
		node_ptr root()
		{
			return node;
		}
		pair<iterator,bool> insert(const value_type& val)
		{
			node_ptr ret = nullptr;
			node = insert_aux(node, nullptr, val, ret);
			data_cnt++;
			return make_pair<iterator, bool>(ret , ret == nullptr);
		}
		iterator find(const value_type& key)
		{
			return find_aux(node, key);
		}
		iterator lower_bound(const value_type& x)
		{
			return lower_bound_aux(node, x);
		}
		iterator upper_bound(const value_type& x)
		{
			return upper_bound_aux(node, x);
		}
		void erase(iterator pos)
		{
			erase_aux(pos.p.node);
			data_cnt--;
		}
		void erase(const value_type& x)
		{
			erase_val_aux(node, x);
			data_cnt--;
		}
		void clear()
		{
			del();
			data_cnt = 0;
		}
	};
	//Trie Tree
	struct Trienode
	{
		size_t cnt;
		struct Trienode* next[26];
	};
	class Trietree
	{
		typedef Trienode* node_ptr;
	private:
		node_ptr new_node()
		{
			node_ptr p = Data_allocator.allocate(1);
			p->cnt = 0;
			for (int i = 0; i < 26; i++)
				p->next[i] = nullptr;
		}
		std::allocator<Trienode> Data_allocator;
		node_ptr node;
	public:
		Trietree()
		{
			node = new_node();
		}
		void insert_aux(node_ptr pos, const char* str)
		{
			size_t p = 0;
			while (str[p] != '\0')
			{
				size_t k = str[p] - 'a';
				if (!pos->next[k])
					pos->next[k] = new_node();
				pos = pos->next[k];
				p++;
			}
			pos->cnt++;
		}

	};

}
#endif