#pragma once
#ifndef _TEST_STACK_H
#define _TEST_STACK_H
#include"stack.h"
#include<stack>
#include<assert.h>
namespace ministl {
	void testCase1() {
		std::stack<int> st1;
		stack<int> st2;

		for (auto i = 0; i != 10; ++i) {
			st1.push(i);
			st2.push(i);
		}
		for (auto i = 0; i != 10; ++i) {
			assert(st1.top() == st2.top());
			st1.pop();
			st2.pop();
		}
	}
	void testCase2() {
		stack<std::string> st;
		assert(st.empty());
		assert(st.size() == 0);

		st.push("one");
		st.push("two");
		assert(!st.empty());
		assert(st.size() == 2);
	}
	void testCase3() {
		stack<int> st1;
		for (auto i = 0; i != 5; ++i)
			st1.push(i);
		auto st2(st1);
		assert(st1 == st2);
		assert(!(st1 != st2));
	}
	void testCase4() {
		stack<int> st1, st2;
		st1.push(1); st1.push(2); st1.push(3);
		st2.push(1); st2.push(2);
		assert(st1.size() == 3 && st2.size() == 2);
		st1.swap(st2);
		assert(st1.size() == 2 && st2.size() == 3);
		ministl::swap(st1, st2);
		assert(st1.size() == 3 && st2.size() == 2);
	}

	void testAllCases() {
		testCase1();
		testCase2();
		testCase3();
		testCase4();
	}
}
#endif