#include"Tree.h"
#include<assert.h>
#include<vector>
#include<random>
#include<algorithm>
namespace Ministl {
	namespace BinarySearchTreeTest {
		template<class Container1, class Container2>
		bool container_equal( Container1& con1,  Container2& con2) 
		{
			if (con1.size() != con2.size())
				return false;
			else
			{
				auto i = con1.begin();
				auto j = con2.begin();
				while (i != con1.end() && j != con2.end() && (*i == *j))
					i++, j++;
				if (i != con1.end())
					return false;
				return true;
			}
		}


		void testCase1() {
			ministl::BStree<std::string,std::string> bst;

			assert(bst.empty());
			assert(bst.size() == 0);

			bst.insert("1","1");
			assert(!bst.empty());
			assert(bst.size() == 1);
		}
		void testCase2() {
			ministl::BStree<int,int> bst;

			for (auto i = 0; i != 100; ++i)
				bst.insert(i,i);
			assert(bst.size() == 100);
		}
		void testCase3() {
			ministl::BStree<int, int> bst;
			std::vector<int> v;
			std::random_device rd;

			for (auto i = 0; i != 100; ++i) {
				auto r = rd() % 65536;
				bst.insert(r,r);
				v.push_back(r);
			}
			std::sort(v.begin(), v.end());
			v.erase(std::unique(v.begin(), v.end()), v.end());
			assert(container_equal(bst, v));

			/*for (auto i = 0; i != 20; ++i) {
				bst.erase(*bst.begin());
				v.erase(v.begin());
				assert(container_equal(bst, v));
			}
*/
			ministl::BStree<int, int> bst1;
			//bst1.insert(v.begin(), v.end());
			//assert(container_equal(bst1, v));
		}
		void testCase4() {
			ministl::BStree<int, int> bst;
			for (auto i = 0; i != 10; ++i)
				bst.insert(i,i);

			assert(*bst.find(5) == 5);
			assert(*bst.begin() == 0);
		//	assert(*bst.find_max() == 9);
		}


		void testAllCases() {
			testCase1();
			testCase2();
			testCase3();
			testCase4();
		}
	}
}