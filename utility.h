#pragma once
#ifndef _UTILITY_H
#define _UTILITY_H
namespace ministl
{
	template<typename T1,typename T2>
	class pair
	{
		friend pair<T1, T2> make_pair(T1 x, T2 y);
	public:
		T1 first;
		T2 second;
		pair() = default;
		pair(const T1& x, const T2& y) :first(x), second(y) {}
		template<typename U,typename V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) {}

		bool operator <(const pair<T1, T2>& rhs)
		{
			if (first == rhs.first)
				return second < rhs.second;
			return first < rhs.first;
		}
		bool operator>(const pair<T1, T2>& rhs)
		{
			if (first == rhs.first)
				return second > rhs.second;
			return first > rhs.first;
		}
		bool operator == (const pair<T1, T2>& rhs)
		{
			return first == rhs.first && second == rhs.second;
		}

		bool operator <=(const pair<T1, T2>& rhs)
		{
			return !(*this > rhs);
		}

		bool operator >=(const pair<T1, T2>& rhs)
		{
			return !(*this < rhs);
		}
	};
	template<typename T1,typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}

	//在一个pair的子类map_pair中重新定义 运算符 
	template<typename K, typename T>
	struct map_pair
	{
		typedef map_pair<K, T> self;
		K first;
		T second;
		operator pair<K, T>()
		{
			return ministl::make_pair<K, T>(first, second);
		}
		map_pair(const pair<K, T>& rhs)
		{
			first = rhs.first;
			second = rhs.second;
		}
		map_pair(const K& key, const T& val)
		{
			first = key, second = val;
		}
		bool operator==(const self& rhs) const
		{
			return first == rhs.first;
		}
		bool operator!=(const self& rhs) const
		{
			return !(*this == rhs);
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

	
}

#endif