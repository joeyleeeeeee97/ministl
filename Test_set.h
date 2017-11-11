#pragma once
#ifndef _TEST_SET_H
#define _TEST_SET_H
#include"set.h"
#include<assert.h>
#include<set>
#include<random>
namespace ministl
{
	template <class A, class B>
	bool equal(A c1, B c2)
	{
		//std::cout << c1.size() << ' ' << c2.size() << "\n";
		if (c1.size() != c2.size())
			return false;
		auto i = c1.begin();
		auto j = c2.begin();
		while (i != c1.end() && j != c2.end() && (*i == *j))
			i++, j++;
		if (i != c1.end())
			return false;
		return true;
	}

	void test1()
	{
		ministl::set<int> s;
		std::set<int> s1;
		std::random_device rd;
		for (int i = 0; i < 10000; i++)
		{
			int tmp = rd() % 65536;
			s.insert(tmp);
			s1.insert(tmp);
		}
		assert(equal(s1, s));
		for (auto i = s.begin(); i != s.end(); i++)
		{
			assert(s1.count(*i) == 1);
		}
		for (auto i = s1.begin(); i != s1.end(); i++)
		{
			if (s.find(*i).p.node == NULL)
				std::cout << "!!!!!!!!";
		}
		for (int i = 0; i < 10000; i++)
		{
			int tmp = rd() % 65536;
			s.insert(tmp);
			s1.insert(tmp);
		}
		for (int i = 0; i < 10000; i++)
		{
			int tmp = rd() % 65536;
			auto t1 = s.lower_bound(tmp);
			auto t2 = s1.lower_bound(tmp);
			if (t1 == s.end())
				assert(t2 == s1.end());
			else
				assert(*t1 == *t2);
		}
	}
}

#endif