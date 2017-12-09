#pragma once
#ifndef _TEST_VECTOR_H
#define _TEST_VECTOR_H
#include"vector.h"
#include"allocator.h"
#include<vector>
#include<assert.h>
#include<string>
#include<memory>

namespace ministl
{
	template<class C1,class C2>
	bool Equal(C1& a,C2& b)
	{
		if (a.size() != b.size())
			return false;
		else
		{
			auto i = a.begin();
			auto j = b.begin();
			while (i != a.end() && j != b.end())
			{
				if (*i == *j)
					i++, j++;
				else
					return false;
			}
			return true;	
		}
	}
	void testCase1() 
	{
		std::vector<std::string> v1(10, "zxh");
		ministl::vector<std::string> v2(10, "zxh");
		assert(Equal(v1, v2));

		std::vector<std::string> v3(10);
		ministl::vector<std::string> v4(10);
		assert(Equal(v3, v4));

		
	}
	void testCase2() {
		std::vector<int> temp1(10, 0);
		ministl::vector<int> temp2(10, 0);

		assert(Equal(temp1, temp2));
		auto v1(temp1);
		auto v2(temp2);
		assert(Equal(v1, v2));

		auto v3(std::move(temp1));
		auto v4(std::move(temp2));
		assert(Equal(v3, v4));

		auto v5 = v1;
		auto v6 = v2;
		assert(Equal(v5, v6));

		auto v7 = std::move(v3);
		auto v8 = std::move(v4);
		assert(Equal(v7, v8));

		
	}
	void testCase3() {
		ministl::vector<int> v1, v2;
		for (int i = 0; i != 100; ++i) {
			v1.push_back(i);
			v2.push_back(i);
		}
		assert(v1 == v2);
		assert(!(v1 != v2));
	
	}
	void testCase6() {
		ministl::vector<int> v(11, 0);
		assert(v.size() == 11);

		v.resize(5);
		assert(v.size() == 5);

		v.resize(20);
		assert(v.size() == 20);
	}
	void testCase7() {
		ministl::vector<int> v;
		v.reserve(20);
		assert(v.capacity() == 20);
	}
	void testCase8() {
		std::vector<int> v1(10);
		ministl::vector<int> v2(10);
		for (unsigned i = 0; i < 10; i++) {
			v1[i] = i;
			v2[i] = i;
		}
		assert(Equal(v1, v2));

		v1.front() = 99;
		v2.front() = 99;
		v1.back() = 100;
		v2.back() = 100;

		assert(Equal(v1, v2));
	}
	void testCase10() {
		ministl::vector<int> foo(3, 100);   // three ints with a value of 100
		ministl::vector<int> bar(2, 200);   // five ints with a value of 200
		//std::cout << foo[0] << ' ' << foo[1];
		assert(Equal(foo, std::vector < int > { 100, 100, 100 }));
		assert(Equal(bar, std::vector < int > {200, 200}));

		foo.swap(bar);
		assert(Equal(bar, std::vector < int > { 100, 100, 100 }));
		assert(Equal(foo, std::vector < int > {200, 200}));
	}
	void testCase11() {
		std::vector<std::string> v1;
		ministl::vector<std::string> v2;

		v1.push_back("hello "); v1.push_back("world");
		v2.push_back("hello "); v2.push_back("world");
		assert(Equal(v1, v2));

		v1.pop_back();
		v2.pop_back();
		assert(Equal(v1, v2));
	}
	void testCase12() {
		std::vector<int> v1;
		ministl::vector<int> v2;

		v1.insert(v1.begin(), 0);
		v2.insert(v2.begin(), 0);
		
		assert(Equal(v1, v2));

		v1.insert(v1.end(), 1);
		v2.insert(v2.end(), 1); //是因为插入一个元素的操作写挫了！
		assert(Equal(v1, v2));
		
		v1.insert(v1.begin() + v1.size() / 2, (size_t)10, 0);
		v2.insert(v2.begin() + v2.size() / 2, (size_t)10, 0);
		
		assert(Equal(v1, v2));
	
		int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		v1.insert(v1.end(), std::begin(arr), std::end(arr));
		v2.insert(v2.end(), std::begin(arr), std::end(arr));
	
		assert(Equal(v1, v2));
		
	}
	void testCase13() {
		std::vector<int> v1;
		ministl::vector<int> v2;
		for (int i = 1; i <= 10; i++) {
			v1.push_back(i);
			v2.push_back(i);
		}
		v1.erase(v1.begin() + 5);
		v2.erase(v2.begin() + 5);
		assert(Equal(v1, v2));

		v1.erase(v1.begin(), v1.begin() + 3);
		v2.erase(v2.begin(), v2.begin() + 3);
		assert(Equal(v1, v2));
	}
	void testCase14() {
		ministl::vector<int> foo(3, 100);
		ministl::vector<int> bar(2, 200);

		assert(!(foo == bar));
		assert(foo != bar);
	}
	class TestItem
	{
	public:
		TestItem()
		{
			++count;
		}
		TestItem(const TestItem & other)
		{
		
			++count;
		}

		virtual ~TestItem()
		{
	
			--count;
		}

		static int getCount()
		{
			return count;
		}
	private:
		static int count;
	};
	int TestItem::count = 0;

	void testCase15()
	{
		assert(TestItem::getCount() == 0);
		{
			typedef ministl::vector<TestItem> TVector;
			TVector t(10);
			t.push_back(TestItem());
			
			t.push_back(TestItem());
			std::cout << TestItem::getCount() << std::endl;
			t.push_back(TestItem());
			t.insert(t.begin()+1 ,2500, TestItem());
		
		//	t.erase(t.be;
		}

		assert(TestItem::getCount() == 0);

	}
	
	void testAllCases() {
	
		testCase1();
		std::cout << "Test 1 ok" << std::endl;
		testCase2();
		std::cout << "Test 2 ok" << std::endl;
		testCase3();
		std::cout << "Test 3 ok" << std::endl;
		testCase6();
		std::cout << "Test 6 ok" << std::endl;
		testCase7();
		std::cout << "Test 7 ok" << std::endl;
		testCase8();
		std::cout << "Test 8 ok" << std::endl;
	
		testCase10();
		std::cout << "Test 10 ok" << std::endl;
		testCase11();
		std::cout << "Test 11 ok" << std::endl;
		testCase12();
		std::cout << "Test 12 ok" << std::endl;
	
		testCase13();
		std::cout << "Test 13 ok" << std::endl;
		testCase14();
		std::cout << "Test 14 ok" << std::endl;
		testCase15();
		std::cout << "Test 15 ok" << std::endl;
	}
}

#endif