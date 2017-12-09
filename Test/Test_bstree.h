#pragma once
#include"Tree.h"
#include<assert.h>
#include<random>
#include<vector>
namespace ministl
{
	template <class A,class B>
	bool equal(A c1, B c2)
	{
		std::cout << c1.size() << ' ' << c2.size() << "\n";
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
	void test1()//检测迭代器 遍历方法是否正确
	{
		std::random_device rd; 
		std::vector<int> v;
		ministl::BStree<int> t;
		for (int i = 0; i < 1000; i++)
		{
			int tmp = rd() % 65536;
			t.insert(tmp);
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
		//std::cout << t.size();
		assert(equal(v, t));
		assert(*t.begin() == v[0]);
		assert(*t.find_max() == v[v.size() - 1]);
	}
	void test2()
	{
		std::random_device rd;
		std::vector<int> v;
		ministl::BStree<int> t;
		for (int i = 0; i < 1000; i++)
		{
			int tmp = rd() % 65536;
			t.insert(tmp);
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		v.erase(std::unique(v.begin(), v.end()), v.end());
		for (int i = 0; i < v.size(); i += 2)
		{
			/*std::cout << "beg";
			std::cout << t.size() << ' ' << v.size() << std::endl;*/
			int tmp = rd() % 65536;
			int sb = tmp % 20;
			auto it = t.begin();
			for (int m = 0; m < sb; m++)
				it++;
			//std::cout << it.p.node->left << "         "<< it.p.node->right << std::endl;
			t.erase(it);
			v.erase(v.begin() + sb);
		}
		assert(equal(v, t));
		for(int i = 0;i<v.size();i++)
		{
		//	std::cout << *t.find(v[i]) << std::endl;
			assert(*(t.find(v[i])) == v[i]);
		}

	}
}