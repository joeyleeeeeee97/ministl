#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include<new>
#include<cstddef>
#include<climits>
#include<iostream>
#include<cstdlib>
#include"construct.h"
#include"alloc.h"
namespace ministl
{
	template<class T,class Alloc>
	class simple_alloc
	{
	public:
		static T* allocate(size_t n)
		{
			return n == 0 ? 0 : (T*)Alloc::allocate(n * sizeof(T));
		}
		static T* allocate(void)
		{
			return (T*)Alloc::allocate(sizeof(T));
		}
		static void deallocate(T *p, size_t n)
		{
			if (n != 0)
				Alloc::deaallocate(p, n * sizeof(T));
		}
		static void deallocate(T* p)
		{
			Alloc::deallocate(p, sizeof(T));
		}
	};


	template<class T>
	inline T* _allocate(size_t n, T*)
	{
		return static_cast<T*>(alloc::allocate(n));
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		alloc::deallocate(static_cast<T*>(buffer), sizeof(T));
	}


	template<class T>
	class allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		pointer allocate(size_type n,const void* hint = 0)
		{
			return _allocate((difference_type)n, pointer(0));
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_address(const reference x)
		{
			return (const_pointer)&x;
		}
		
		size_type max_size()const
		{
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}
#endif
