#pragma once
#ifndef _TUPLE_H
#define _TUPLE_H
namespace ministl
{
	template<typename... Args> struct tuple;

	template<>
	struct tuple<> {};
	typedef tuple<> nulltuple;

	template<typename T, typename... Args>
	struct tuple<T, Args...> : public tuple<Args...>
	{
		typedef tuple<T, Args...> self_type;
		typedef tuple<Args...> base_type;
		typedef T value_type;
		tuple(const T& v, const Args&... tails) :base_type(tails...), value(v) {}
		tuple(T&& v, Args&&... tails) :base_type(std::move(tails)...), value(std::forward<T>(v)) {}
		tuple(T&& v, Args&... tails) :base_type(std::move(tails)...), value(std::forward<T>(v)) {}
		tuple(T& v, Args&&... tails) :base_type(std::move(tails)...), value(std::forward<T>(v)) {}

		T& getval() 
		{
			return value;
		}

		T value;
	};

	template<typename T>
	struct tuple<T> : public nulltuple
	{
		typedef T value_type;
		tuple(const T& val) :value(val) {}

		T& getval() 
		{
			return value;
		}

		T value;
	};
	template<size_t n, typename T> struct tuple_at;

	template<size_t n, typename T,typename... Args>
	struct tuple_at<n, tuple<T,Args...>>
	{
		typedef typename tuple_at<n - 1, tuple<Args...>>::value_type value_type;
		typedef typename tuple_at<n - 1, tuple<Args...>>::tuple_type tuple_type;
	};

	template<typename T,typename... Args>
	struct tuple_at<0, tuple<T,Args...>>
	{
		typedef T value_type;
		typedef typename tuple<T, Args...> tuple_type;
	};

	template<typename T>
	struct tuple_at<0, tuple<T>>
	{
		typedef T value_type;
		typedef typename tuple<T> tuple_type;
	};

	template<>
	struct tuple_at<0,tuple<>>
	{
		typedef tuple<> tuple_type;
		typedef tuple<> value_type;
	};

	template<size_t n,typename... Args>
	typename tuple_at<n, tuple<Args...>>::value_type& tuple_get(tuple<Args...>& t)
	{
		typedef typename tuple_at<n, tuple<Args...>>::tuple_type ret_tuple_type;
		return static_cast<ret_tuple_type&>(t).getval();	
	}
}


#endif