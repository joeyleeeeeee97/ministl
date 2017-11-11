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
		T* get_ptr()
		{
			return ptr;
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
			if (this->ptr != x.ptr)
			{
				if (ptr != nullptr)
					ptr->decrement();
				if (x.ptr != nullptr)
					x.ptr->increment();
				ptr = x.ptr;
			}
		}
		explicit shared_ptr(T* data_ptr)
		{
			ptr = new node(data_ptr);
		}
		self& operator= (const self& x) noexcept
		{
			if (this->ptr == x.ptr)
				return *this;
			if (ptr != nullptr)
				ptr->decrement();
			if (x.ptr != nullptr)
				x.ptr->increment();
			ptr = x.ptr;
			return *this;
		}
		T& operator*()
		{
			return *(ptr->get_ptr());
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
			ptr = new node();
		}
		template <class U> void reset(U* p)
		{
			ptr->decrement();
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


	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr() :data(nullptr) {}
		unique_ptr(T* _data) :data(_data) {}
		T* release()
		{
			T* ret = data;
			data = nullptr;
			return ret;
		}
		void reset()
		{
			delete data;
			data = nullptr;
		}
		void reset(T* _data)
		{
			delete data;
			data = _data;
		}
		void operator =(const unique_ptr<T>& rhs)
		{
			if (rhs.data != nullptr)
				reset(rhs.release());
			else
				reset();
		}
		T& operator*()
		{
			return *data;
		}
	private:
		T* data;
	};
}










#endif