#pragma once
#ifndef _XHASH_H
#define _XHASH_H
#include"vector.h"
#include"list.h"
#include"string.h"
namespace ministl
{
	const size_t HASH_SEED = 0xdeadbeef;

	template<class T> inline
		size_t hash_seq(const T& val)
	{
		const size_t _FNV_offset_basis = 2166136261U;
		const size_t _FNV_prime = 16777619U;
		size_t ans = _FNV_offset_basis;
		for (auto it = val.begin(); it != val.end(); it++)
		{
			ans ^= *it;
			ans *= _FNV_prime;
		}
		return ans;
	}

	template<class T> inline
		size_t hash_value(const T& val)
	{
		return ((size_t)val ^HASH_SEED);
	}

	template<class T> inline
		size_t hash_value(const vector<T>& val)
	{
		return hash_seq(val);
	}
	
	template<class T> inline
		size_t hash_value(const list<T>& val)
	{
		return hash_seq(val);
	}
	


	template<typename T>
	struct xhash
	{
		size_t operator() (const T& data, size_t bucket_size)
		{
			return hash_value(data) % bucket_size;
		}
	};

}
#endif