#pragma once
#ifndef _MAP_H
#define _MAP_H
#include"Tree.h"
#include "utility.h"
namespace ministl
{
	//在一个pair的子类map_pair中重新定义 运算符 
	template<typename K,typename T>
	struct map_pair
	{
		typedef map_pair<K, T> self;
		K first;
		T second;
		operator pair<K, T>()
		{
			return ministl::make_pair<K,T>(first,second);
		}
		map_pair(const pair<K, T>& rhs)
		{
			fist = rhs.first;
			second = rhs.second;
		}
		map_pair(const K& key, const T& val)
		{
			first = key, second = val;
		}
		map_pair(const K& key)
		{
			first = key, second = T();
		}
		bool operator==(const self& rhs) const
		{
			return first == rhs.first;
		}
		bool operator<(const self& rhs) const
		{
			return first < rhs.first;
		}
		bool operator>(const self& rhs) const
		{
			return first > rhs.first;
		}
		bool operator>=(const self& rhs) const
		{
			return !(first < rhs.first);
		}
		bool operator<=(const self& rhs) const
		{
			return !(first > rhs.first);
		}
	};

	template<typename K, typename T>
	class map
	{
	private:
		typedef map_pair<K, T> key_value;
		typedef size_t size_type;
		typedef BStree_iterator<key_value> iterator;
		BStree<key_value> sequence;
	public:
		map() :sequence() {}
		iterator begin()
		{
			return sequence.begin();
		}
		iterator end()
		{
			return sequence.end();
		}
		bool empty()
		{
			return sequence.empty();
		}
		size_type size()
		{
			return sequence.size();
		}
		iterator find(const key_value& x)
		{
			return sequence.find(x);
		}
		size_type count(const key_value& x)
		{
			if (sequence.find(x).p.node == NULL)
				return 0;
			else
				return 1;
		}
		iterator insert(const key_value& key)
		{
			return sequence.insert(key);
		}
		void erase(const key_value& key)
		{
			return sequence.erase(key);
		}
		iterator upper_bound(const key_value& key)
		{
			return sequence.upper_bound(key);
		}
		iterator lower_bound(const key_value& key)
		{
			return sequence.lower_bound(key);
		}

		auto& operator [](const key_value& x)
		{
			iterator it = find(x);
			if (it.p.node == NULL)
			{
				insert(x);
				return sequence.find(x).p.node->data.second;
			}
			else
				return it.p.node->data.second;
		}

	};
}


#endif