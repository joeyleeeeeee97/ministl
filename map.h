#pragma once
#ifndef _MAP_H
#define _MAP_H
#include"Tree.h"
#include "utility.h"
namespace ministl
{

	template<typename K, typename T>
	class map
	{
	private:
		typedef map_pair<K, T> key_value;
		typedef size_t size_type;
		BStree<key_value> sequence;
	public:
		typedef BStree_iterator<key_value> iterator;
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
		iterator find(const K& x)
		{
			return sequence.find(map_pair<K, T>(x, T()));
		}
		size_type count(const K& x)
		{
			if (sequence.find(map_pair<K, T>(x, T())).p.node == NULL)
				return 0;
			else
				return 1;
		}
		auto insert(const key_value& key)
		{
			return sequence.insert(map_pair<K,T>(key,T()));
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (auto it = first; it != last; it++)
				insert(*first);
		}
		void erase(const K& key)
		{
			return sequence.erase(map_pair<K, T>(key, T()));
		}
		iterator upper_bound(const K& key)
		{
			return sequence.upper_bound(map_pair<K, T>(key, T()));
		}
		iterator lower_bound(const K& key)
		{
			return sequence.lower_bound(map_pair<K, T>(key, T()));
		}


		T& operator [](const K& x)
		{
			pair<iterator,bool> res = sequence.insert(map_pair<K,T>(x,T()));
			return (*res.first).second;
		}

	};
}


#endif