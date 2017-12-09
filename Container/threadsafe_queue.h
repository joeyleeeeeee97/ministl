#pragma once
#ifndef _THREADSAFE_QUEUE
#define _THREADSAFE_QUEUE
#include"queue.h"
#include<mutex>
#include<memory>
#include<condition_variable>
namespace ministl
{
	template<class T>
	class threadsafe_queue
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef T& reference;
		typedef T* pointer;
	private:
		queue<T> data;
		mutable std::mutex m;
		std::condition_variable data_cond;
	public:
		threadsafe_queue() {}

		void wait_and_pop(T& value)
		{
			std::unique_lock<std::mutex> lk(m);
			data_cond.wait(lk, [this] {return !data.empty(); });
			value = std::move(data.front());
			data.pop();
		}

		std::shared_ptr<T> wait_and_pop()
		{
			std::unique_lock<std::mutex> lk(m);
			data_cond.wait(lk, [this] {return !data.empty(); });
			std::shared_ptr<T> ret = make_shared<T>(data.front());
			data.pop();
			return ret;
		}

		bool try_pop(T& value)
		{
			std::lock_guard<std::mutex> lk(m);
			if (data, empty())
				return false;
			value = std::mmove(data.front());
			data.pop();
			return true;
		}

		std::shared_ptr<T> try_pop()
		{
			std::unique_lock<std::mutex> lk(m);
			if (data.empty())
				return std::shared_ptr<T>();
			std::shared_ptr<T> ret = std::make_shared<T>(data.front());
			data.pop();
			return ret;
		}


	};
}


#endif