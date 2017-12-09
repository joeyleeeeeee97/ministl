#pragma once
#ifndef _THREADSAFE_STACK
#define _THREADSAFE_STACK
#include"stack.h"
#include"smart_ptr.h"
#include<mutex>

namespace ministl
{
	template<class T>
	class threadsafe_stack
	{
		typedef threadsafe_stack self;
	private:
		stack<T> data;
		mutable std::mutex m;
	public:
		threadsafe_stack() = default;
		threadsafe_stack(const self&) = delete;
		threadsafe_stack& operator= (const self&) = delete;

		void push(T val)
		{
			std::lock_guard<std::mutex> lk(m);
			//data.push(val);
			data.push(std::move(val));
		}

		shared_ptr<T> pop()
		{
			std::lock_guard<std::mutex> lk(m);
			if (data.empty())
			{
				std::cerr << "empty stack" << std::endl;
				exit(1);
			}
			shared_ptr<T> ret(std::move(data.top()));
			data.pop();
			return ret;
		}


		bool empty() const
		{
			std::lock_guard<std::mutex> lk(m);
			return data.empty();
		}

		size_t size() const
		{
			std::lock_guard<std::mutex> lk(m);
			return data.size();
		}

	};
}



#endif