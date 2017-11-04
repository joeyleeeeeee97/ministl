#pragma once
#ifndef _TREE_H
#define _TREE_H
#include "functional.h"
#include"allocator.h"
namespace ministl
{
	//Binary search Tree
	template<typename T>
	struct BSnode
	{
		BSnode():left(NULL),parent(NULL),right(NULL){}
		T data;
		struct BSnode* parent;
		struct BSnode* left;
		struct BSnode* right;
	};
	template<typename T>
	class BStree_base_iterator
	{
	public:
		typedef BSnode<T>* ptr;
		ptr node;
		BStree_base_iterator()
		{
			node = NULL;
		}
		BStree_base_iterator(ptr p)
		{
			node = p;
		}
		void increment()
		{
			if (node->right == NULL)
			{
				ptr pre = node->parent;
				while (pre != NULL&&node == pre->right)
				{
					node = pre;
					pre = node->parent;
				}
				if (pre == NULL)
					node = NULL;
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
			if (node->left == NULL)
			{
				ptr pre = node->parent;
				while (pre != NULL&&node == pre->left)
				{
					node = pre;
					pre = node->parent;
				}
				if (pre == NULL)
					node = NULL;
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
			p.node = NULL;
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
			p->left = NULL;
			p->right = NULL;
			p->parent = pre;
			return p;
		}
		node_ptr insert_aux(node_ptr p, node_ptr pre,const value_type& val)
		{
			if (!p)
			{
				return new_node(val, pre);
			}
			if (p->data > val)
				p->left = insert_aux(p->left, p, val);
			else if (p->data < val)
				p->right = insert_aux(p->right, p, val);
			return p;
		}
		iterator find_aux(node_ptr p, const value_type& val)
		{
			if (!p)
			{
				//std::cerr << "cant find it!\n";
				return NULL;
			}
			if (p->data == val)
				return iterator(p);
			else if (p->data > val)
				return find_aux(p->left, val);
			else
				return find_aux(p->right, val);
		}
		void del(node_ptr link)
		{
			if (link->left)
				del(link->left);
			if (link->right)
				del(link->right);
			delete(link);
			node = NULL;
		}
		void erase_aux(node_ptr p)
		{
			if (p->left == NULL&&p->right == NULL)
			{
				if (p->parent == NULL)
				{
					node = NULL;
				}
				else if (p->parent->left!=NULL && p->parent->left->data == p->data)
					p->parent->left = NULL;
				else if (p->parent->right!=NULL && p->parent->right->data == p->data)
					p->parent->right = NULL;
				delete(p);
			}
			else if (p->left == NULL&&p->right != NULL)
			{
				if (p->parent == NULL)
				{
					node = p->right,node->parent = NULL;
				}
				else if (p->parent->left!=NULL && p->parent->left->data == p->data)
					p->parent->left = p->right, p->right->parent = p->parent;
				else if (p->parent->right!=NULL && p->parent->right->data == p->data)
					p->parent->right = p->right, p->right->parent = p->parent;
				delete(p);
			}
			else if (p->left != NULL&&p->right == NULL)
			{
				if (p->parent == NULL)
				{
					node = p->left, node->parent = NULL;
				}
				else if (p->parent->left!=NULL && p->parent->left->data == p->data)
					p->parent->left = p->left, p->left->parent = p->parent;
				else if (p->parent->right!=NULL && p->parent->right->data == p->data)
					p->parent->right = p->left, p->left->parent = p->parent;
				delete(p);
			}
			else
			{
				node_ptr it = p->left;
				node_ptr tmp = p;
				while (it->right != NULL)
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
				if (it->left != NULL)
					it->left->parent = tmp;
				delete(it);
			}
		}
		iterator lower_bound_aux(node_ptr p, const value_type& x)
		{
			if (!p)
				return iterator(NULL);
			if (p->data >= x)
			{
				auto tmp = lower_bound_aux(p->left, x);
				if (tmp.p.node != NULL)
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
				return iterator(NULL);
			if (p->data > x)
			{
				auto tmp = upper_bound_aux(p->left, x);
				if (tmp.p.node != NULL)
					return tmp;
				else
					return iterator(p);
			}
			else
				return upper_bound_aux(p->right, x);
		}
		void erase_val_aux(node_ptr p,const value_type& key)
		{
			if (p == NULL)
				return;
			if (p->data == key)
				erase_aux(p);
			else if (p->data < key)
				erase_val_aux(p->right, key);
			else if (p->data > key)
				erase_val_aux(p->left, key);
		}
	public:
		BStree() :node(NULL),data_cnt(0) {}
		bool empty()
		{
			return node == NULL;
		}
		size_type size()
		{
			if (empty()) return 0;
			size_t cnt = 0;
			for (auto it = begin(); it != end(); it++)
				cnt++;
			return cnt;
		}
		iterator begin()
		{
			if (node == NULL)
			{
				iterator t(NULL);
				return t;
			}
			iterator it(node);
			while (it.p.node->left != NULL)
				it.p.node = it.p.node->left;
			return it;
		}
		iterator end()
		{
			iterator it(NULL);		
			return  (it);
		}
		iterator find_max()
		{
			node_ptr p = node;
			if (p == NULL)
				return iterator(NULL);
			while (p->right != NULL)
				p = p->right;
			return iterator(p);
		}
		node_ptr root()
		{
			return node;
		}
		iterator insert(const value_type& val)
		{
			node = insert_aux(node, NULL, val);
			//return *this;
			return iterator(node);
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
		}
		void erase(const value_type& x)
		{
			erase_val_aux(node, x);
		}
		void clear()
		{
			del(node);
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
				p->next[i] = NULL;
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