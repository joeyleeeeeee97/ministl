#pragma once
#ifndef _ALLOC_H__
#define _ALLOC_H__
#include <cstdlib>
/*
第二级适配器，当区块小于128bytes时，以内存池管理
*/
namespace ministl
{
	class alloc
	{
	private:
		enum {_ALIGN = 8};//小型区块
		enum {_MAXBYTES = 128};
		enum {_NFREELISTS = _MAXBYTES/_ALIGN};
		enum { _NOBJS = 20 };
	private:
		//可以看作确定地址也可以看作指向下一节点
		union obj
		{
			union obj *next;
			char client[1];
		};

		static obj* freelist[_NFREELISTS];

	private:
		static char *start, *end;
		static size_t heap_size;

	private:
		static size_t ROUND_UP(size_t bytes)
		{
			return ((bytes + _ALIGN - 1)&~(_ALIGN - 1));
		}
		static size_t FREELIST_INDEX(size_t bytes)
		{
			return (((bytes)+_ALIGN - 1) / _ALIGN - 1);
		}
		static void* refill(size_t n);
		static char* chunk_alloc(size_t size, size_t &nobjs);
	public:
		static void* allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_size, size_t new_size);
	};

	char *alloc::start = 0;
	char *alloc::end = 0;
	size_t alloc::heap_size = 0;
	alloc::obj *alloc::freelist[_NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	
	void *alloc::allocate(size_t bytes)
	{
		if (bytes > _MAXBYTES)
		{
			return malloc(bytes);
		}
		obj *pos = freelist[FREELIST_INDEX(bytes)];
		if (pos)
		{
			freelist[FREELIST_INDEX(bytes)] = pos->next;
			return pos;
		}
		else
		{
			return refill(ROUND_UP(bytes));
		}
	}

	void alloc::deallocate(void* ptr, size_t bytes)
	{
		if (bytes > _MAXBYTES)
		{
			free(ptr);
		}
		else
		{
			obj *tmp = (obj *)ptr;
			tmp->next = freelist[FREELIST_INDEX(bytes)];
			freelist[FREELIST_INDEX(bytes)] = tmp;
		}
	}

	void *alloc::reallocate(void *ptr, size_t old_size, size_t new_size)
	{
		alloc::deallocate(ptr, old_size);
		ptr = allocate(new_size);
		return ptr;
	}
	//返回一个大小为n的对象，并且有时候会为适当的freelist增加节点
	//假设n已经上调到8的倍数
	void *alloc::refill(size_t bytes)
	{
		size_t nobjs = _NOBJS;
		obj **myfreelist = NULL;
		obj *result = NULL;
		obj *current_obj = 0, *next_obj = 0;
		char *chunk = chunk_alloc(bytes, nobjs);
		if (nobjs == 1)
		{
			return chunk;
		}
		else
		{
			myfreelist = freelist+ FREELIST_INDEX(bytes);
			//这一块返回给客户端
			result = (obj*)chunk;
			//下面导引freelist指向新配置的空间（内存池）
			*myfreelist = next_obj = (obj*)(chunk + bytes);

			for (int i = 1;; i++)
			{
				current_obj = next_obj;
				next_obj = (obj*)((char*)next_obj + bytes);

				if (nobjs - 1 == i)
				{
					current_obj->next = 0;
					break;
				}
				else
				{
					current_obj->next = next_obj;
				}
			}
			return result;
		}
	}
	/*
	从链表中分配nobjs个空间，每一块的大小为bytes.如果链表中至少有一个满足要求，那么分配尽可能多的块并且修改nobjs的值，如果数量不足就从内存中分配两倍的空间
	*/
	char *alloc::chunk_alloc(size_t bytes, size_t &nobjs)
	{
		char *result = 0;
		size_t total_bytes = bytes*nobjs;
		size_t bytes_left = end - start;
		if (bytes_left >= total_bytes)
		{
			result = start;
			start = start + total_bytes;
			return result;
		}
		else if(bytes_left >= bytes)
		{
			nobjs = bytes_left / bytes;
			total_bytes = nobjs*bytes;
			result = start;
			start = start + total_bytes;
			return result;
		}
		else
		{
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if (bytes_left > 0)
			{
				obj* volatile *myfreelist = freelist + FREELIST_INDEX(bytes_left);
				((obj*)start)->next = *myfreelist;
				*myfreelist = (obj*)start;
			}
			start = (char*)malloc(bytes_to_get);
			if (!start)
			{
				obj **myfreelist = 0, *p = 0;
				for (int i = 0; i < _MAXBYTES; i += _ALIGN)
				{
					myfreelist = freelist + FREELIST_INDEX(i);
					p = *myfreelist;
					if (!p)
					{
						*myfreelist = p->next;
						start = (char*)p;
						end = start + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end = 0;
			}
			heap_size += bytes_to_get;
			end = start + bytes_to_get;
			return chunk_alloc(bytes, nobjs);
		}
	}

}
#endif