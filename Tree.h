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
				if (node->parent->key > node->key)
					node = node->parent;
				else
				{
					std::cerr << "out of range" << std::endl;
					return;
				}
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
				if (node->parent->key < node->key)
					node = node->parent;
				else
				{
					std::cerr << "out of range" << std::endl;
					return;
				}
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
	public:
		BStree() :node(NULL) {}
		/*~BStree()
		{
			del(node);
		}*/
		node_ptr root()
		{
			return node;
		}
		self& insert(const key_value& key, const value_type& val)
		{
			node = insert_aux(node, NULL, key, val);
			return *this;
		}
		node_ptr insert_aux(node_ptr p, node_ptr pre, const key_value& key, const value_type& val)
		{
			if (!p)
			{
				return new_node(key, val,pre);
			}
			if (p->key > key)
				p->left = insert_aux(p->left, p, key, val);
			else if (p->key < key)
				p->right = insert_aux(p->right, p, key, val);
			return p;
		}
		value_type find(node_ptr p, const key_value& key)
		{
			if (!p)
			{
				std::cerr << "cant find it!\n";
				return value_type();
			}
			if (p->key == key)
				return p->data;
			else if (p->key > key)
				return find(p->left, key);
			else
				return find(p->right, key);
		}
		void del(node_ptr link)
		{
			if (link->left)
				del(link->left);
			if (link->right)
				del(link->right);
			delete(link);
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