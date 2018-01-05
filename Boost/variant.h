#pragma once
#ifndef _VARIANT_H
#define _VARIANT_H
#include <typeinfo>
#include <memory>
/*
½è¼ø https://www.cnblogs.com/catch/p/4903653.html
2018/1/2
*/
namespace ministl
{
	template<typename T>
	void destroy_at(unsigned char* ptr)
	{
		reinterpret_cast<T*>(ptr)->~T();
	}

	template<typename... Ts>
	struct TypeMaxSize;

	template<>
	struct TypeMaxSize<>
	{
		static constexpr std::size_t size = 0;
		static constexpr std::size_t align = 0;
	};

	template<typename T, typename... Args>
	struct TypeMaxSize < T, Args... >
	{
		static constexpr std::size_t cur_size = sizeof(T);
		static constexpr std::size_t next_size = TypeMaxSize<Args...>::size;
		static constexpr std::size_t size = cur_size > next_size ? cur_size : next_size;
		static constexpr std::size_t cur_align = alignof(T);
		static constexpr std::size_t next_align = TypeMaxSize<Args...>::align;
		static constexpr std::size_t align = cur_align > next_align ? cur_align : next_align;
	};

	template<typename T, typename... Args>
	struct TypeExist;

	template<typename T>
	struct TypeExist<T>
	{
		enum { exist = 0 };
		static constexpr std::size_t id = 0;
	};

	template<typename T, typename Front, typename... Args>
	struct TypeExist<T, Front, Args...>
	{
		enum { exist = std::is_same<T, Front>::value || TypeExist<T, Args...>::exist };
		static constexpr std::size_t id = std::is_same<T, Front>::value ? 1 : 1 + TypeExist<T, Args...>::id;
	};


	template<typename... Ts>
	struct variant
	{
	public:
		template<class T>
		variant(T&& v) :type(TypeExist<typename std::remove_reference<T>::type, Ts...>::id)
		{
			static_assert(TypeExist<typename std::remove_reference<T>::type, Ts...>::exist, "invalid type for variant");
			new(data) typename std::remove_reference<T>::type(std::forward<T>(v));
		}
		~variant()
		{
			if (type != 0)
			{
				fun[type - 1](data);
			}
		}
	private:
		constexpr static std::size_t Alignment()
		{
			return TypeMaxSize<Ts...>::align;
		}
		constexpr static std::size_t TypeSize()
		{
			return TypeMaxSize<Ts...>::size;
		}
		using destroy_func_t = void(*)(unsigned char*);
		constexpr static destroy_func_t fun[] = { ministl::destroy_at<Ts>... };
		size_t type = 0;
		alignas(Alignment()) unsigned char data[TypeSize()];
	};

	template<class ...TS>
	constexpr typename variant<TS...>::destroy_func_t variant<TS...>::fun[];
}

#endif