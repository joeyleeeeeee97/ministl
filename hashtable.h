#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include"vector.h"
#include"list.h"
#include"utility.h"
namespace ministl
{
	vector<size_t> prime_list = 
	{
		53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
		786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611,
		402653189, 805306457, 1610612741, 3221225473, 4294967291,
	};
	template<class T>
	struct default_hash
	{
		size_t operator()(T data, size_t bucket_size)
		{
			return data % bucket_size;
		}
	};
	template<typename K,typename T,typename Hash = default_hash<T>>
	class hashtable
	{
	public:
		typedef K key_type;
		typedef T value_type;
		typedef Hash hash_type;
		typedef pair<K, T> obj;
		typedef vector<list<obj>> table;
		typedef list_iterator<obj> iterator;
	private:
		size_t bucket_size;
		size_t data_num;
		hash_type hash;
		table data;
		void rehash(size_t new_size = 0)
		{
			new_size = new_size == 0 ? bucket_size * 2 : new_size;
			table new_table(new_size);
			for (auto& i : data)
			{
				for (auto& j : i)
				{
					size_t pos = hash(j.first, new_size);
					new_table[pos].push_back(j);
				}
			}
			swap(new_table, data);
			bucket_size = new_size;
		}
	public:
		/*void debug()
		{
			for (auto& it : data)
			{
				std::cout << &*it.begin();
				for (auto i = it.begin(); i != it.end(); i++)
				{
					std::cout << *i << ' ';
				}
				std::cout << std::endl;
			}
		}*/
		hashtable() :data(*prime_list.begin()),data_num(0), bucket_size(*prime_list.begin())
		{
		}
		hashtable(size_t size) :data(size), data_num(0), bucket_size(size)
		{

		}
		pair<iterator, bool> insert(key_type key, value_type val)
		{
			//rehash();
			size_t pos = hash(key, bucket_size);
			for (auto it = data[pos].begin(); it != data[pos].end(); it++)
			{
				if (it->second == val)
				{
					return make_pair<iterator, bool>(data[pos].end(), false);
				}
			}
			data[pos].push_back(make_pair<key_type,value_type>(key,val));
			return make_pair<iterator, bool>(--data[pos].end(), true);
		}

		pair<iterator, bool> find(key_type key)
		{
			size_t pos = hash(key, bucket_size);
			if (!data[pos].empty())
			{
				for (auto it = data[pos].begin();it!=data[pos].end();it++)
				{
					if(it->first == key)
						return make_pair<iterator, bool>(it, true);
				}
			}
			return make_pair<iterator, bool>(data[pos].end(), false);
		}

	};
}

#endif