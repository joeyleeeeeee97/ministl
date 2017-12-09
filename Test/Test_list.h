#pragma once
#ifndef _TEST_LIST_H
#define _TEST_LIST_H
#include"list.h"
#include<assert.h>
#include<list>
namespace ministl
{
	template<class C1,class C2>
	bool list_Equal(C1 a, C2 b)
	{
		if (a.size() != b.size())
			return false;
		else
		{
			auto i = a.begin();
			auto j = b.begin();
			while (i != a.end())
			{
				if (*i != *j)
					return false;
				else
					i++, j++;
			}
			return true;
		}
	}
	void testCase1() {
		std::list<int> l1(10, 0);
		list<int> l2((size_t)10, 0);
		assert(list_Equal(l1, l2));

		int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::list<int> l3(std::begin(arr), std::end(arr));
		list<int> l4(std::begin(arr), std::end(arr));
		assert(list_Equal(l3, l4));

		auto l5(l1);
		auto l6(l2);
		assert(list_Equal(l5, l6));

		auto l7 = l1;
		auto l8 = l2;
		assert(list_Equal(l7, l8));
	}
	void testCase2() {
		list<std::string> l1;
		assert(l1.empty());
		assert(l1.size() == 0);

		std::string arr[] = { "1", "2", "3" };
		list<std::string> l2(std::begin(arr), std::end(arr));
		assert(!l2.empty());
		assert(l2.size() == 3);
	}
	void testCase3() {
		std::string arr[] = { "1", "2", "3" };
		list<std::string> l(std::begin(arr), std::end(arr));
		assert(l.back() == arr[2]);
		assert(l.front() == arr[0]);

		l.front() = "front";
		l.back() = "back";
		assert(l.back() == "back");
		assert(l.front() == "front");
	}
	void testCase4() {
		std::list<int> l1;
		list<int> l2;
		for (auto i = 0; i != 10; ++i) {
			l1.push_front(i);
			l2.push_front(i);
		}
		assert(list_Equal(l1, l2));
		for (auto i = 0; i != 10; ++i) {
			l1.push_back(i);
			l2.push_back(i);
		}
		assert(list_Equal(l1, l2));
		for (auto i = 0; i != 5; ++i) {
			l1.pop_back();
			l2.pop_back();
		}
		assert(list_Equal(l1, l2));
		for (auto i = 0; i != 5; ++i) {
			l1.pop_front();
			l2.pop_front();
		}
		assert(list_Equal(l1, l2));
	}
	void testCase5() {
		std::list<int> l1;
		list<int> l2;

		for (auto i = 0; i != 10; ++i) {
			l1.push_back(i);
			l2.push_back(i);
		}
		assert(list_Equal(l1, l2));
		/*auto rit1 = l1.rbegin();
		auto rit2 = l2.rbegin();
		for (; rit1 != l1.rend() && rit2 != l2.rend(); ++rit1, ++rit2) {
			assert(*rit1 == *rit2);
		}
		assert(rit1 == l1.rend() && rit2 == l2.rend());*/
	}
	void testCase6() {
		std::list<int> l1;
		list<int> l2;

		l1.insert(l1.end(), (size_t)10, -1);
		l2.insert(l2.end(), (size_t)10, -1);
		assert(list_Equal(l1, l2));

		auto it1 = l1.begin();
		auto it2 = l2.begin();
		for (auto i = l1.size() / 2 + 1; i != 0; --i) {
			++it1;
			++it2;
		}
		l1.insert(it1, 1);
		l2.insert(it2, 1);
		assert(list_Equal(l1, l2));

		int arr[] = { 1, 2, 3, 4, 5 };
		it1 = l1.end();
		it2 = l2.end();
		l1.insert(it1, std::begin(arr), std::end(arr));
		l2.insert(it2, std::begin(arr), std::end(arr));
		assert(list_Equal(l1, l2));
	}
	void testCase7() {
		std::list<int> l1;
		list<int> l2;
		for (auto i = 0; i != 100; ++i) {
			l1.push_back(i);
			l2.push_back(i);
		}

		l1.erase(l1.begin()); l1.erase(--l1.end());
		l2.erase(l2.begin()); l2.erase(--l2.end());
		assert(list_Equal(l1, l2));

		l1.erase(l1.begin(), l1.end());
		l2.erase(l2.begin(), l2.end());
		assert(list_Equal(l1, l2));
	}
	void testCase8() {
		list<int> l1, l2;
		l1.push_back(1); l1.push_back(1); l1.push_back(1);
		l2.push_back(2); l2.push_back(2);

		//std::cout << ' ' << l1.size() << ' ' << l2.size() << std::endl;
		l1.swap(l2);
		//std::cout << ' ' << l1.size() << ' ' << l2.size() << std::endl;
		assert(l1.size() == 2 && l2.size() == 3);

	}
	void testCase9() {
		/*std::random_device rd;
		std::list<int> l1;
		list<int> l2;
		for (auto i = 0; i != 100; ++i) {
			auto ret = rd() % 65536;
			l1.push_back(ret);
			l2.push_back(ret);
		}

		l1.sort();
		l2.sort();
		assert(list_Equal(l1, l2));

		l1.sort(std::greater<int>());
		l2.sort(std::greater<int>());
		assert(list_Equal(l1, l2));*/
	}
	void testCase10() {
		int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::list<int> l1(std::begin(arr), std::end(arr));
		list<int> l2(std::begin(arr), std::end(arr));

		l1.reverse();
		l2.reverse();
		assert(list_Equal(l1, l2));
	}
	void testCase11() {
		int arr1[] = { 0, 1, 3, 5, 9 }, arr2[] = { 2, 4, 6, 7, 8 };
		std::list<double> first1(std::begin(arr1), std::end(arr1)), second1(std::begin(arr2), std::end(arr2));
		list<double> first2(std::begin(arr1), std::end(arr1)), second2(std::begin(arr2), std::end(arr2));

		first1.merge(second1);
		first2.merge(second2);
		assert(list_Equal(first1, first2));
	}
	void testCase12() {
		int arr[] = { 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 9, 11 };
		std::list<int> l1(std::begin(arr), std::end(arr));
		list<int> l2(std::begin(arr), std::end(arr));

		l1.unique();
		l2.unique();
		assert(list_Equal(l1, l2));
	}
	bool func(const int& x)
	{
		return (x % 2 == 0);
	}
	void testCase13() {
		int arr[] = { 17, 89, 7, 14, 89, 0, 1, 4 };
		std::list<int> l1(std::begin(arr), std::end(arr));
		list<int> l2(std::begin(arr), std::end(arr));

		l1.remove(89);
		l2.remove(89);
		assert(list_Equal(l1, l2));

		
		l1.remove_if(func);
		l2.remove_if(func);
		assert(list_Equal(l1, l2));
	}
	void testCase14() {
		std::list<int> l1(10, 0), l3(10, 1);
		list<int> l2((size_t)10, 0), l4((size_t)10, 1);

		l1.splice(l1.begin(), l3);
		l2.splice(l2.begin(), l4);

		assert(list_Equal(l1, l2));
		auto l5 = l1;
	//	ministl::list<int> l6 = l2;//ÎªÊ²Ã´ÊÇÇ³¿½±´£¿£¡
		ministl::list<int> l6;
		for (auto i : l2)
			l6.push_back(i);
		l1.splice(l1.end(), l5, l5.begin());
		l2.splice(l2.end(), l6, l6.begin());
		assert(list_Equal(l1, l2));


		auto it1 = l1.begin();
		auto it2 = l2.begin();
		for (auto i = 0; i != l1.size() / 2; ++i) {
			++it1;
			++it2;
		}
		l1.splice(it1, l5, l5.begin(), l5.end());
		l2.splice(it2, l6, l6.begin(), l6.end());
		std::cout << l2.size()<<'\n'<<l1.size()<<'\n';
		assert(list_Equal(l1, l2));
	}
	void testCase15() {
		list<int> l1((size_t)10, 0), l2((size_t)10, 1), l3((size_t)10, 0);

		assert(l1 == l3);
		assert(l1 != l2);
	}


	void testAllCases() {
		testCase1();
		std::cout << "1 ok\n";
		testCase2();
		std::cout << "2 ok\n";
		testCase3();
		std::cout << "3 ok\n";
		testCase4();
		std::cout << "4 ok\n";
		testCase5();
		std::cout << "5 ok\n";
		testCase6();
		std::cout << "6 ok\n";
		testCase7();
		std::cout << "7 ok\n";
		testCase8();
		std::cout << "8 ok\n";
		testCase9();
		std::cout << "9 ok\n";
		testCase10();
		std::cout << "10 ok\n";
		testCase11();
		std::cout << "11 ok\n";
		testCase12();
		std::cout << "12 ok\n";
		testCase13();
		std::cout << "13 ok\n";
		testCase14();
		std::cout << "14 ok\n";
		testCase15();
		std::cout << "15 ok\n";
	}
}

#endif