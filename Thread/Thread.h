#pragma once
#ifndef _THREAD_H
#define _THREAD_H
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <process.h>
#include <tuple>
#include "functional.h"
namespace ministl
{
	/*
	cpp thread implementation based on windows api
	*/
	struct Runnable
	{
		//virtual ~Runnable() {}; 虚析构函数有问题！
		void debug()
		{
			std::cout << 1;
		}
		virtual void run() = 0;
	};

	template< class F, class... Args >
	struct threadfunc : public Runnable
	{
		threadfunc(F&& f, Args&&... args) :thbinder(std::forward<F>(f), std::forward<Args>(args)...) {}
		ministl::binder<F, Args...> thbinder;
		void run()
		{
			thbinder();
		}
	};
	
	template<class F, class... Args >
	threadfunc<F, Args...> bind_threadfunc(F&& f, Args&&... args)
	{
		return threadfunc<F,Args...>(std::forward<F>(f), std::forward<Args>(args)...);
	}

	class thread 
	{
	public:
		thread() :thread_id(0), handle(nullptr), func_handle(nullptr){}
		thread(thread&& rhs) noexcept :thread_id(rhs.thread_id), handle(rhs.handle), func_handle(nullptr)
		{
			rhs.thread_id = 0, rhs.handle = nullptr;
		}
		~thread()
		{
			while (1) {}
		}
		template< class Function, class... Args >
		explicit thread(Function&& f, Args&&... args)
		{
			func_handle = &ministl::bind_threadfunc(std::forward<Function>(f), std::forward<Args>(args)...);
			handle = (HANDLE)_beginthreadex(0, 0,
				[](void* parm)-> unsigned __stdcall
				{
					Runnable* r = static_cast<Runnable*>(parm);
					if (!r)
					{
						std::cerr << "static_cast error form void* to Runnable" << std::endl;
						return 0;
					}
					r->run();
					return 0;
				},
				func_handle, 0, &thread_id);
		}
		thread(const thread&) = delete;
		thread& operator=(const thread&) = delete;
	private:
		unsigned thread_id;
		HANDLE handle;
		Runnable* func_handle;
	};

}


#endif