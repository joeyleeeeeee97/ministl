#pragma once
#ifndef _SMART_PTR_H
#define _SMART_PTR_H

namespace ministl
{
	template<class T>
	class shared_ptr_node
	{
	public:

		shared_ptr_node() :cnt(0) {}
		shared_ptr_node(T* _ptr)
		{
			if (ptr == NULL)
				shared_ptr_node();
			else
				ptr = _ptr, cnt = 1;
		}
		~shared_ptr_node()
		{
			
		}
		void increment()
		{
			cnt++;
		}
		void decrement()
		{
			if (cnt != 0)
			{
				cnt--;
				if (cnt == 0)
				{
					delete ptr;
					ptr = nullptr;
				}
			}
		}

		size_t count()
		{
			return cnt;
		}
	private:
		size_t cnt;
		T* ptr;
	};

	template<class T>
	class shared_ptr
	{
		typedef shared_ptr_node<T> node;
		typedef shared_ptr_node<T>* node_ptr;
		typedef shared_ptr<T> self;
	private:
		node_ptr ptr = nullptr;
	public:
		shared_ptr()noexcept
		{
			ptr = new node();
		}
		shared_ptr(const self& x)
		{
			if (ptr != nullptr)
				ptr->decrement();
			x.ptr->increment();
			ptr = x.ptr;
		}
		explicit shared_ptr(T* data_ptr)
		{
			ptr = new node(data_ptr);
		}
		self& operator= (const self& x) noexcept
		{
			shared_ptr(x);
		}
		size_t use_count()
		{
			return ptr->count();
		}
		bool unique() const noexcept
		{
			return use_count() == 1;
		}
		void swap(shared_ptr& x) noexcept
		{
			std::swap(x.ptr, ptr);
		}
		void reset() noexcept
		{
			ptr->decrement();
			shared_ptr();
		}
		template <class U> void reset(U* p)
		{
			reset();
			ptr = new shared_ptr_node<U>(p);
		}
		T* get() noexcept
		{
			return ptr->ptr;
		}
		/*template <class T, class... Args>
		self make_shared(Args&&... args)
		{
			if (ptr != nullptr)
				ptr->decrement();
			ptr = new shared_ptr_node(args);
		}*/
		~shared_ptr()
		{
			if (ptr != nullptr)
			{
				ptr->decrement();
				ptr = nullptr;
			}
		}
	};
}










#endif