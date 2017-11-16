#pragma once
#ifndef _TEST_STRING_H
#define _TEST_STRING_H
#include<string>
#include"string.h"
#include<assert.h>
namespace ministl{

	template<class C1, class C2>
	bool Equal_string(const C1& l, const C2& r)
	{
		//cout << r.size() << endl;
		if (l.size() != r.size())
			return false;
		auto i = l.begin();
		auto j = r.begin();
		while (i != l.end())
		{
			if (*i == *j)
				i++, j++;
			else
				return false;
		}
		return true;
	}
		void testCase1(){
			const char *ptr = "hello world";

			std::string s1(ptr);
			string s2(ptr);
			assert(Equal_string(s1, s2));

			std::string s3(ptr, 5);
			string s4(ptr, 5);
			assert(Equal_string(s3, s4));

			std::string s5(10, 'z');
			string s6(10, 'z');
			assert(Equal_string(s5, s6));

		/*	char arr[] = "zouxiaohang love cpp";
			std::string s7(std::begin(arr), std::end(arr));
			string s8(std::begin(arr), std::end(arr));
			assert(Equal_string(s7, s8));*/
		}
		void testCase2(){
			std::string temp1("hello, world");
			string temp2("hello, world");

			std::string s1(temp1);
			string s2(temp2);
			assert(Equal_string(s1, s2));

			std::string s3(std::move(s1));
			string s4(std::move(s2));
			assert(Equal_string(s3, s4));

			/*std::string s5(temp1, 1);
			string s6(temp2, 1);
			assert(Equal_string(s5, s6));

			std::string s7(temp1, 0, 5);
			string s8(temp2, 0, 5);
			assert(Equal_string(s7, s8));*/
		}
		void testCase3(){
			std::string t1("hello, world");
			string t2("hello, world");

			std::string s1; s1 = 'a';
			string s2; s2 = 'a';
			assert(Equal_string(s1, s2));

			std::string s3; s3 = "hello";
			string s4; s4 = "hello";
			assert(Equal_string(s3, s4));

			std::string s5; s5 = t1;
			string s6; s6 = t2;
			assert(Equal_string(s5, s6));

			std::string s7; s7 = std::move(t1);
			string s8; s8 = std::move(t2);
			assert(Equal_string(s7, s8));
		}
		void testCase4(){
			string str("Test string");
			std::string s(str.begin(), str.end());
			auto i = 0;
			for (string::iterator it = str.begin(); it != str.end(); ++it, ++i){
				assert(*it == s[i]);
			}
			
			/*i = s.size() - 1;
			for (string::reverse_iterator it = str.rbegin(); it != str.rend(); ++it, --i){
				assert(*it == s[i]);
			}*/
		}
		void testCase5(){
			string s;
			assert(s.size() == 0);
			assert(s.length() == 0);

			s = "hello, world";
			assert(s.size() == 12);
			assert(s.size() == 12);
		}
		void testCase6(){
			std::string s1("hello, world");
			string s2("hello, world");

			s1.resize(5);
			s2.resize(5);
			assert(Equal_string(s1, s2));

			s1.resize(20, 'z');
			s2.resize(20, 'z');
			assert(Equal_string(s1, s2));

			s1.resize(6, 'a');
			s2.resize(6, 'a');
			assert(Equal_string(s1, s2));

			s1.resize(100);
			s2.resize(100);
			assert(Equal_string(s1, s2));
		}
		void testCase7(){
			string s;
			s.reserve(10);
		//	std::cout << s.capacity();
			assert(s.capacity() == 10);
		}
		void testCase8(){
			string s;
			assert(s.empty());

			s = "hello, world";
			assert(!s.empty());

			s.clear();
			assert(s.empty());
		}
		void testCase9(){
			string s;
			s.resize(10);
			for (auto i = 0; i != s.size(); ++i)
				s[i] = 'a' + i;
			assert(s == "abcdefghij");

			s.back() = 'Z';
			s.front() = 'A';
			assert(s == "AbcdefghiZ");
		}
		void testCase10(){
			std::string s1;
			string s2;
			for (auto i = 0; i != 10; ++i){
				s1.push_back('a' + i);
				s2.push_back('a' + i);
			}
			assert(Equal_string(s1, s2));
		}
		void testCase11(){
			std::string s1;
			string s2;

			s1.insert(s1.begin(), 'A'); 
			s2.insert(s2.begin(), 'A'); 
			assert(Equal_string(s1, s2));

			s1.insert(s1.end(), 2, 'Z');
			s2.insert(s2.end(), 2, 'Z');
			assert(Equal_string(s1, s2));

			size_t n = 2;
			s1.insert(2, 10, '@');
			s2.insert(2, (size_t)10, '@');
			assert(Equal_string(s1, s2));

			s1.insert(0, "hello, world");
			s2.insert(0, "hello, world");
			assert(Equal_string(s1, s2));

			s1.insert(s1.size() - 1, "zouxiaohang", 3);
			s2.insert(s2.size() - 1, "zouxiaohang", 3);
			assert(Equal_string(s1, s2));

			std::string s3;
			string s4;

		/*	s3.insert(s3.begin(), s1.begin(), s1.end());
			s4.insert(s4.begin(), s2.begin(), s2.end());
			assert(Equal_string(s3, s4));*/

			s3.insert(0, s1);
			s4.insert(0, s2);
			assert(Equal_string(s3, s4));

		/*	std::string t1("zouxiaoHANG");
			string t2("zouxiaoHANG");
			s3.insert(s3.size(), t1, 7, t1.size() - 7);
			s4.insert(s4.size(), t2, 7, t2.size() - 7);
			assert(Equal_string(s3, s4));*/
		}
		void testCase12(){
			std::string s1;
			string s2;

			s1.append(std::string("abc"));
			s2.append(string("abc"));
			assert(Equal_string(s1, s2));

			
			s1.append("hello");
			s2.append("hello");
			assert(Equal_string(s1, s2));

			s1.append("world", 0, 5);
			s2.append("world", 0, 5);
			assert(Equal_string(s1, s2));


			/*std::string s3; s3.append(s1.begin(), s1.end());
			string s4; s4.append(s2.begin(), s2.end());
			assert(Equal_string(s3, s4));*/
		}
		void testCase13(){
			std::string s1;
			string s2;

			s1 += 'A';
			s2 += 'A';
			assert(Equal_string(s1, s2));

			s1 += "hello";
			s2 += "hello";
			assert(Equal_string(s1, s2));

			s1 += std::string("world");
			s2 += string("world");
			assert(Equal_string(s1, s2));
		}
		void testCase14(){
			std::string s1("hello world");
			string s2("hello world");

			s1.pop_back();
			s2.pop_back();
			assert(Equal_string(s1, s2));
		}
		void testCase15(){
			std::string s1("hello world");
			string s2("hello world");

			s1.erase(s1.begin() + 1);
			s2.erase(s2.begin() + 1);
			assert(Equal_string(s1, s2));

			s1.erase(2, s1.size() - 4);
			s2.erase(2, s2.size() - 4);
			assert(Equal_string(s1, s2));

			s1.erase(s1.begin(), s1.end());
			s2.erase(s2.begin(), s2.end());
			assert(Equal_string(s1, s2));
		}
		/*void testCase16(){
			std::string s1("zouxiaohang"), t1("I Love C++");
			string s2("zouxiaohang"), t2("I Love C++");

			s1.replace(0, 3, t1);
			s2.replace(0, 3, t2);
			assert(Equal_string(s1, s2));

			s1.replace(s1.begin(), s1.begin() + s1.size() / 2, t1);
			s2.replace(s2.begin(), s2.begin() + s2.size() / 2, t2);
			assert(Equal_string(s1, s2));

			s1.replace(0, s1.size(), t1, 0, t1.size());
			s2.replace(0, s2.size(), t2, 0, t2.size());
			assert(Equal_string(s1, s2));

			s1.replace(0, s1.size(), "123456789");
			s2.replace(0, s2.size(), "123456789");
			assert(Equal_string(s1, s2));

			s1.replace(s1.begin(), s1.end(), std::string("hubei"));
			s2.replace(s2.begin(), s2.end(), string("hubei"));
			assert(Equal_string(s1, s2));

			s1.replace(0, s1.size(), "wuhan", 5);
			s2.replace(0, s2.size(), "wuhan", 5);
			assert(Equal_string(s1, s2));

			s1.replace(s1.begin(), s1.end(), "hongshanqu", 10);
			s2.replace(s2.begin(), s2.end(), "hongshanqu", 10);
			assert(Equal_string(s1, s2));

			s1.replace(0, s1.size(), 10, 'Z');
			s2.replace(0, s2.size(), 10, 'Z');
			assert(Equal_string(s1, s2));

			s1.replace(s1.begin(), s1.end(), 10, 'A');
			s2.replace(s2.begin(), s2.end(), 10, 'A');
			assert(Equal_string(s1, s2));

			s1.replace(s1.begin(), s1.end(), t1.begin(), t1.end());
			s2.replace(s2.begin(), s2.end(), t2.begin(), t2.end());
			assert(Equal_string(s1, s2));
		}*/
		void testCase17(){
			string buyer("money");
			string seller("goods");

			seller.swap(buyer);
			assert(seller == "money");
			assert(buyer == "goods");
		}
		void testCase18(){
			char buffer[20];
			string str("Test string...");
			std::size_t length = str.copy(buffer, 6, 5);
			buffer[length] = '\0';
			std::equal(std::begin(buffer), std::end(buffer), str.begin());
		}
		void testCase19() {
			string str("There are two needles in this haystack with needles.");
			string str2("needle");

			auto found = str.find(str2);
			assert(found == 14);

			found = str.find("needles are small", found + 1, 6);
			assert(found == 44);

			found = str.find(string("wuhan"));
			assert(found == (size_t)(-1));

			found = str.find("haystack");
			if (found != 30)
				std::cout << 1;
			assert(found == 30);

			found = str.find('.');
			assert(found == 51);

			str.replace(str.find(str2), str2.length(), "preposition");
			assert(Equal_string(str,
				string("There are two prepositions in this haystack with needles.")));
		}
			
		void testCase20(){
			string str("The sixth sick sheik's sixth sheep's sick.");
			string key("sixth");

			auto found = str.rfind(key);
			assert(found == 23);

			found = str.rfind(key, 24);
			assert(found == 23);

			found = str.rfind('.');
			assert(found == str.size() - 1);

			found = str.rfind("The");
			assert(found == 0);

		
		}
			void testCase21(){
			string str("Please, replace the vowels in this sentence by asterisks.");
			string key("aeiou");
			const char *arr = "aeiou";

			auto found = str.find_first_of(arr);
			assert(found == 2);

			found = str.find_first_of(arr, found + 1);
			assert(found == 3);

			found = 12;

			found = str.find_first_of(key, found + 1);
			assert(found == 14);

			found = str.find_first_of('v', found + 1);
			assert(found == 20);
		}
		void testCase22(){
			string str("1234567890098765432112345678900");

			auto found = str.find_last_of('6');
			assert(found == 25);

			found = str.find_last_of('6', found - 1);
			assert(found == 14);

			found = str.find_last_of("01", 11, 2);
			assert(found == 10);

			found = str.find_last_of(string("#1"), 19);
			assert(found == 19);
		}
		void testCase23(){
			string str("look for non-alphabetic characters...");

			auto found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");
			assert(found == 12);
		}
		void testCase24(){
			string str("12345678900987654321");

			auto found = str.find_last_not_of("023456789", str.size() - 2);
			//if(found!=0)
			assert(found == 0);
		}
		void testCase25(){
			string str = "We think in generalities, but we live in details.";

			auto s = str.substr(3, 5);
			assert(Equal_string(s, string("think")));
		}
		void testCase26(){
			string str1("green apple");
			string str2("red apple");

			assert(str1.compare(str2) != 0);
			
		}
		void testCase28(){
			string foo = "alpha";
			string bar = "beta";

			assert(!(foo == bar)); 
			assert(foo != bar); 
			assert(foo < bar); 
			assert(!(foo > bar)); 
			assert(foo <= bar); 
			assert(!(foo >= bar)); 
		}
		

		void testAllCases(){
			testCase1();
			testCase2();
			testCase3();
			testCase4();
			testCase5();
			testCase6();
			testCase7();
			testCase8();
			testCase9();
			testCase10();
			testCase11();
			testCase12();
			testCase13();
			testCase14();
			testCase15();
		//testCase16();
			testCase17();
			testCase18();
			testCase19();
			testCase20();
			testCase21();
			testCase22();
			testCase23();
			testCase24();
			//testCase25();
			//testCase26();
			//testCase27();
			testCase28();
			//testCase29();
		}
	}
#endif