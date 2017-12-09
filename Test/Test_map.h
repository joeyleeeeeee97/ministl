#pragma once
#ifndef _TEST_MAP
#define _TEST_MAP
#include<map>
#include"Test_map.h"
#include"map.h"
#include"string.h"
#include<assert.h>
#include<random>
//TestCase À´×ÔÓÚcppreference
namespace ministl
{
	void TestCase1()
	{
		ministl::map<char, int> mymap;
		std::map<char, int > mymap1;
		char c;

		mymap['a'] = mymap1['a'] =  101;
		mymap['c'] = mymap1['c'] = 202;
		mymap['f'] = mymap1['f'] =  303;

		for (c = 'a'; c<'h'; c++)
		{
			assert( mymap1.count(c) == mymap.count(c) );
		}
		auto i = mymap.begin();
		auto j = mymap1.begin();
		while (i != mymap.end())
		{
			std::cout << (*i).first << (*j).first << std::endl;
			assert((*i).first == (*j).first);
			std::cout << (*i).second << (*j).second << std::endl;
			assert((*i).second == (*j).second);
			i++, j++;
		}
	}

	void TestCase2()
	{
		ministl::map<int, string> mymap;
		std::map<int, string > mymap1;
		std::random_device rd;
		for (int i = 0; i < 100; i++)
		{
			int tmp = rd() % 65536;
			mymap1[tmp] = string(tmp,'a' + tmp % 26);
			mymap[tmp] = string(tmp,'a' + tmp % 26);
		}


		auto i = mymap.begin();
		auto j = mymap1.begin();
		while (i != mymap.end())
		{
		//	std::cout << (*i).first << (*j).first << std::endl;
			assert((*i).first == (*j).first);
		//	std::cout << (*i).second << (*j).second << std::endl;
			assert((*i).second == (*j).second);
			i++, j++;
		}
	}
	void TestAllcases()
	{
		TestCase1();
		TestCase2();
	}
}




#endif