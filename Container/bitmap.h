#pragma once
#ifndef _BITMAP_H
#define _BITMAP_H
#include"allocator.h"
#include"memory.h"
namespace ministl
{
	class bitmap
	{
	private:
		const int SHIFT = 5;//移位数
		const int MASK = 0x1f;//掩码 最低的五位为一
		const int BITSPERWORD = 32;//采用32位int
		int* start;
		int* End;
		ministl::allocator<int> data_allocator;
		inline size_t block_size(size_t num) const { return num&MASK + 1; }
		void check(size_t num)
		{
			if (size() >= num) return;
			int* new_start = data_allocator.allocate(block_size(num));
			ministl::uninitialized_copy(start, End, new_start);
			data_allocator.deallocate(start, End - start);
			start = new_start;
			End = start + block_size(num);
			memset(start, 0, (End - start) * 4);
		}
	public:
		bitmap() :start(nullptr), End(nullptr) {}
		void resize(size_t num)
		{
			check(num);
		}
		size_t size()
		{
			return (End - start) * 32;
		}
		void set(int i)
		{
			check(i);
			start[i >> SHIFT] |= (1 << (i & MASK));
		}
		void clr(int i)
		{
			check(i);
			start[i >> SHIFT] &= ~(1 << (i & MASK));
		}
		int test(int i)
		{
			check(i);
			return start[i >> SHIFT] & (1 << (i & MASK));
		}
	};
}

#endif