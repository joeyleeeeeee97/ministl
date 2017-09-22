#pragma once
#ifndef _TREE_H
#define _TREE_H
#include"allocator.h"
namespace ministl
{
	//Binary search Tree
	template<typename K, typename T>
	struct BSnode
	{
		BSnode():left(NULL),parent(NULL),right(NULL){}
		K key;
		T data;
		struct BSnode* parent;
		struct BSnode* left;
		struct BSnode* right;
	};
	template<typename K,typename T>
	class BStree_base_iterator
	{
	public:
		typedef BSnode<K, T>* ptr;
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
			//	return node;
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
	template<typename K,typename T>
	class BStree_iterator 
	{
	public:
		typedef BSnode<K, T>* ptr;
		typedef  BStree_iterator<K, T> self;
		BStree_base_iterator<K,T> p;
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
		bool operator!=(const  BStree_iterator<K, T>& rhs)
		{
			return !(*this == rhs);
		}
		bool operator==(const  BStree_iterator<K, T>& rhs)
		{
			return this->p.node == rhs.p.node;
		}
		T operator*()
		{
			return p.node->data;
		}
		T& operator->()
		{
			return &(*this);
		}
	};
	template<typename K, typename T>
	class BStree
	{
	public:
		typedef K key_value;
		typedef T value_type;
		typedef T* pointer;
		typedef size_t size_type;
		typedef BSnode<K,T>* node_ptr;
		typedef BStree<K, T> self;
		typedef BStree_iterator<K,T> iterator;
		//static iterator end(NULL);

	private:
		node_ptr node;
		std::allocator<BSnode<K,T>> data_allocator;
		node_ptr new_node(const key_value& key, const value_type& val,node_ptr pre)
		{
			node_ptr p = data_allocator.allocate(1);
			new(&p->key) key_value(key);
			new(&p->data) value_type(val);
			p->left = NULL;
			p->right = NULL;
			p->parent = pre;
			return p;
		}
		node_ptr insert_aux(node_ptr p, node_ptr pre, const key_value& key, const value_type& val)
		{
			if (!p)
			{
				return new_node(key, val, pre);
			}
			if (p->key > key)
				p->left = insert_aux(p->left, p, key, val);
			else if (p->key < key)
				p->right = insert_aux(p->right, p, key, val);
			return p;
		}
		iterator find_aux(node_ptr p, const key_value& key)
		{
			if (!p)
			{
				//std::cerr << "cant find it!\n";
				return NULL;
			}
			if (p->key == key)
				return iterator(p);
			else if (p->key > key)
				return find_aux(p->left, key);
			else
				return find_aux(p->right, key);
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
				else if (p->parent->left!=NULL && p->parent->left->key == p->key)
					p->parent->left = NULL;
				else if (p->parent->right!=NULL && p->parent->right->key == p->key)
					p->parent->right = NULL;
				delete(p);
			}
			else if (p->left == NULL&&p->right != NULL)
			{
				if (p->parent == NULL)
				{
					node = p->right,node->parent = NULL;
				}
				else if (p->parent->left!=NULL && p->parent->left->key == p->key)
					p->parent->left = p->right, p->right->parent = p->parent;
				else if (p->parent->right!=NULL && p->parent->right->key == p->key)
					p->parent->right = p->right, p->right->parent = p->parent;
				delete(p);
			}
			else if (p->left != NULL&&p->right == NULL)
			{
				if (p->parent == NULL)
				{
					node = p->left, node->parent = NULL;
				}
				else if (p->parent->left!=NULL && p->parent->left->key == p->key)
					p->parent->left = p->left, p->left->parent = p->parent;
				else if (p->parent->right!=NULL && p->parent->right->key == p->key)
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
				p->key = it->key, p->data = it->data;
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
		iterator lower_bound_aux(node_ptr p, const key_value& x)
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
		iterator upper_bound_aux(node_ptr p, const key_value& x)
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
		void erase_val_aux(node_ptr p,const key_value& key)
		{
			if (p == NULL)
				return;
			if (p->key == key)
				erase_aux(p);
			else if (p->key < key)
				erase_val_aux(p->right, key);
			else if (p->key > key)
				erase_val_aux(p->left, key);
		}
	public:
		BStree() :node(NULL) {}
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
		iterator insert(const key_value& key, const value_type& val)
		{
			node = insert_aux(node, NULL, key, val);
			//return *this;
			return iterator(node);
		}
		iterator find(const key_value& key)
		{
			return find_aux(node, key);
		}
		iterator lower_bound(const key_value& x)
		{
			return lower_bound_aux(node, x);
		}
		iterator upper_bound(const key_value& x)
		{
			return upper_bound_aux(node, x);
		}
		void erase(iterator pos)
		{
			erase_aux(pos.p.node);
		}
		void erase(const key_value& x)
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
