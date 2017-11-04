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
}

#endif