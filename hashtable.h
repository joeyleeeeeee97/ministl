#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include"list.h"
#include"vector.h"
#include"utility.h"
#include"xhash.h"
#include"algorithm.h"
namespace ministl
{
	static const int _stl_num_primes = 28;
	template<typename T, typename Hash = xhash<T>>
	class hashtable;

	vector<size_t> prime_list = 
	{
		53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
		786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611,
		402653189, 805306457, 1610612741, 3221225473, 4294967291,
	};

	template<typename T>
	class hash_iterator : public bidirectional_iterator<T>
	{
	public:
		hashtable<T>* hash_ptr;
		list_iterator<T> node_ptr;
		list<T>* bucket_ptr;
		hash_iterator(hashtable<T>* hp, list<T>* bp, list_iterator<T> np) :hash_ptr(hp), bucket_ptr(bp), node_ptr(np) {}
		
		hash_iterator& operator++()
		{
			if (++node_ptr == bucket_ptr->end())
			{
				auto tmp = node_ptr;
				--tmp;
				size_t cur = hash_ptr->hash(*tmp, hash_ptr->bucket_size()) + 1;
				while (cur < hash_ptr->bucket_size() && (*hash_ptr).data[cur].empty())
					cur++;
				bucket_ptr = cur < hash_ptr->bucket_size() ? &(hash_ptr->data[cur]) : hash_ptr->data.end();
				node_ptr = (bucket_ptr == hash_ptr->data.end() ? nullptr : bucket_ptr->begin());
			}
			return *this;
		}

		hash_iterator operator++(int)
		{
			hash_iterator tmp = *this;
			++*this;
			return tmp;
		}

		hash_iterator& operator--()
		{
			if (node_ptr-- = bucket_ptr->begin())
			{
				size_t cur = hash_ptr->hash(*node_ptr, hash_ptr->bucket_size()) - 1;
				if (cur < 0) cur = 0;
				else
				{
					while (cur >= 0 && (*hash_ptr).data[cur].empty())
						cur--;
				}
				bucket_ptr = &(hash_ptr->data[cur]);
				node_ptr =  bucket_ptr->begin();
			}
			return *this;
		}

		hash_iterator operator--(int)
		{
			hash_iterator tmp = *this;
			--*this;
			return tmp;
		}

		T& operator* ()
		{
			return *node_ptr;
		}

		bool operator==(const hash_iterator& rhs)
		{
			return hash_ptr == rhs.hash_ptr && node_ptr == rhs.node_ptr && bucket_ptr == rhs.bucket_ptr;
		}

		bool operator!=(const hash_iterator& rhs)
		{
			return !(*this == rhs);
		}
	};

	template<typename T,typename Hash = xhash<T> >
	class hashtable
	{
		friend class hash_iterator<T>;
	public:
		typedef T value_type;
		typedef Hash hash_type;
		typedef vector<list<T>> table;
		typedef hash_iterator<T> iterator;
	private:
		Hash hash;
		table data;
		size_t elem_num;//the sum of all elements
		pair<iterator, bool> _insert_unique_noresize(T val)
		{
			size_t index = hash(val, data.size());

			for (auto it = data[index].begin(); it != data[index].end(); it++)
			{
				if (*it == val)
					return make_pair<iterator, bool >(iterator(this, &data[index], it), false);
			}
			
			data[index].push_front(val);
			elem_num++;
			return make_pair<iterator, bool>(iterator(this, &data[index], data[index].begin()), true);
		}
		
		iterator _insert_equal_noresize(T val)
		{
			size_t index = hash(val, data.size());
			for (auto it = data[index].begin(); it != data[index].end(); it++)
			{
				if (*it == val)
				{
					return iterator(this, &data[index], data[index].insert(it, val));
				}
			}
			data[index].push_front(val);
			elem_num++;
			return iterator(this, &data[index], data[index].begin());
		}

		void initialize_buckets(size_t n) 
		{
			data.resize(n);
			elem_num = 0;
		}

	public:
		hashtable()
		{
			initialize_buckets(53);
		}
		hashtable(size_t n)
		{
			initialize_buckets(next_prime(n));
		}

		void clear()
		{
			for (auto& it : data) 
			{
				it.clear();
			}
			elem_num = 0;
		}

		bool empty()
		{
			return elem_num == 0;
		}

		pair<iterator, bool>find(const T& val)
		{
			size_t index = hash(val, data.size());

			for (auto it = data[index].begin(); it != data[index].end(); it++)
			{
				if (*it == val)
					return ministl::make_pair<iterator, bool >(iterator(this, &data[index], it), true);
			}

			return ministl::make_pair<iterator, bool >(end(), false);
		}


		iterator begin() const
		{
			auto it = data.begin();
			while (it != data.end() && it->empty())
				it++;
			return iterator(const_cast<hashtable<T>*>(this), it, it == data.end() ? nullptr : it->begin());
		}

		iterator begin()
		{
			auto it = data.begin();
			while (it != data.end() && it->empty())
				it++;
			return iterator(this, it, it == data.end() ? nullptr : it->begin());
		}

		iterator end() const
		{
			return iterator(const_cast<hashtable<T>*>(this), data.end(), nullptr);
		}

		iterator end()
		{
			return iterator(this, data.end(), nullptr);
		}


		inline unsigned long next_prime(unsigned long n)
		{
			for (auto it : prime_list)
			{
				if (it >= n)
					return n;
			}
			return prime_list[_stl_num_primes - 1];
		}

		size_t bucket_size() 
		{
			return data.size();
		}

		size_t bucket_size() const
		{
			return data.size();
		}

		size_t size()
		{
			return elem_num;
		}
		size_t hash_val(const T& val)
		{
			return hash(val, data.size());
		}
		pair<iterator, bool> insert_unique(T val)
		{
			rehash(elem_num + 1);
			return _insert_unique_noresize(val);
		}

		iterator insert_equal(T val)
		{
			rehash(elem_num + 1);
			return _insert_equal_noresize(val);
		}

		iterator erase_iter(iterator pos)
		{
			iterator ret = pos;
			ret++;
			pos.bucket_ptr->erase(pos.node_ptr);
			return ret;
		}

		void erase_val(const T& val)
		{
			size_t index = hash(val, data.size());
			for (auto it = data[index].begin(); it != data[index].end();)
			{
				if (*it == val)
					it = data[index].erase(it);
				else
					it++;

			}
		}

		void rehash(size_t n)
		{
			if (n > bucket_size())
			{
				elem_num = elem_num ? elem_num:1;
				while (n > elem_num) elem_num *= 2;
				size_t new_size = next_prime(elem_num);
				hashtable new_table(new_size);
				if (!empty())
				{
					iterator it = begin();
					for (; it != end(); it++)
					{
						//std::cout << *it << std::endl;
						new_table.insert_equal(*it);
					}
				}
				swap(*this, new_table);
			}
		}

		hashtable& operator=(const hashtable& rhs)
		{
			clear();
			for (auto it = rhs.begin(); it != rhs.end(); it++)
			{
				insert_equal(*it);
			}
			return *this;
		}
	};

	template<typename T>
	void swap(const hashtable<T>& lhs, const hashtable<T>& rhs)
	{
		using ministl::swap;
		swap(lhs.data, rhs.data);
		swap(lhs.elem_num, rhs.elem_num);
		swap(lhs.hash, rhs.hash);
	}


	template<typename T, typename Hash = xhash<T> >
	class unordered_set
	{
	public:
		typedef T value_type;
		typedef Hash hash_type;
		typedef vector<list<T>> table;
		typedef hash_iterator<T> iterator;
		typedef hashtable<T> seq;
	private:
		seq con;
	public:
		unordered_set() :con() {}
		unordered_set(std::initializer_list<T> l)
		{
			unordered_set();
			insert(l.begin(), l.end());
		}
		iterator begin()
		{
			return con.begin();
		}

		iterator end()
		{
			return con.end();
		}

		iterator find(const value_type& key)
		{
			return con.find(key).first;
		}

		iterator insert(const value_type& key)
		{
			return con.insert_unique(key).first;
		}

		iterator insert(value_type& key)
		{
			return con.insert_unique(key);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (auto it = first; it != last; it++)
				insert(*it);
		}

		size_t erase(const value_type& key)
		{
			size_t num = count(key);
			if(num)
				con.erase_val(key);
			return num;
		}

		iterator erase(const iterator it)
		{
			return con.erase_iter(it);
		}

		iterator erase(const iterator first, const iterator last)
		{
			iterator it = first;
			for (; it != last;)
				it = con.erase_iter(it);
			return it;
		}

		size_t count(const value_type& val)
		{
			return (con.find(val).second == true) ? 1 : 0;
		}

		bool empty()
		{
			return con.empty();
		}

		size_t size()
		{
			return con.size();
		}

		void clear()
		{
			con.clear();
		}

		void swap(unordered_set<T>& rhs)
		{
			using ministl::swap;
			swap(con, rhs.con);
		}

		size_t bucket_count()
		{
			return con.bucket_size();
		}

		void rehash()
		{
			con.rehash(con.elem_num + 1);
		}

		double load_factor()
		{
			return 1.0 * con.elem_num / bucket_count();
		}

	};

	//Todo: map_pair的hashval
	//模板特化无法匹配？
	template<typename K , typename T, typename Hash = xhash<map_pair<K,T>> >
	class unordered_map
	{
	public:
		typedef K key_type;
		typedef T value_type;
		typedef Hash hash_type;
		typedef vector<list<map_pair<K,T>>> table;
		typedef hash_iterator<map_pair<K,T>> iterator;
		typedef hashtable<map_pair<K, T>, xhash<map_pair<K, T>> > seq;
	private:
		seq con;
	public:
		unordered_map() :con() {}
		
		iterator begin()
		{
			return con.begin();
		}
		iterator begin() const
		{
			return con.begin();
		}

		iterator end()
		{
			return con.end();
		}
		iterator end() const
		{
			return con.end();
		}

		value_type& operator[](const key_type& key)
		{
			map_pair<K, T> p(key, T());
			auto tmp = con.find(p);
			iterator it = tmp.first;
			if (tmp.second == false)
			{
				it = con.insert_equal(p);
			}
			return (*it).second;

		}

		value_type& at(const key_type& key)
		{
			auto tmp = con.find(key);
			if (tmp.second == false)
			{
				std::cerr << "unordered_map out of range \n";
				std::exit(1);
			}
			return (*it).second;
		}

		const value_type& at(const key_type& key) const
		{
			auto tmp = con.find(key);
			if (tmp.second == false)
			{
				std::cerr << "unordered_map out of range \n";
				std::exit(1);
			}
			return (*it).second;
		}

		iterator find(const key_type& key)
		{
			return con.find(key).first;
		}

		pair<iterator, iterator>
			equal_range(const key_type& k)
		{
			auto first = con.find(k).first;
			if (first == con.end())
				return make_pair<iterator, iterator>(first, first);
			else
			{
				iterator last = ++first;
				while (last != con.end() && (*last == *first))
				{
					last++;
				}
				return make_pair<iterator, iterator>(first, last);
			}
		}

		size_t count(const key_type& k)
		{
			auto first = con.find(k).first;
			if (first == con.end())
				return 0;
			else
			{
				iterator last = ++first;
				size_t cnt = 1;
				while (last != con.end() && (*last == *first))
				{
					last++, cnt++;
				}
				return cnt;
			}
		}

		auto insert(const map_pair<K, T> p)
		{
			return con.insert_unique(p);
		}

		size_t erase(const value_type& key)
		{
			size_t num = count(key);
			if (num)
				con.erase_val(key);
			return num;
		}

		iterator erase(const iterator it)
		{
			return con.erase_iter(it);
		}

		iterator erase(const iterator first, const iterator last)
		{
			iterator it = first;
			for (; it != last;)
				it = con.erase_iter(it);
			return it;
		}

		void rehash(size_t n)
		{
			con.rehash(n);
		}

	};
}

#endif