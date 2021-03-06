#pragma once
#ifndef _FUNCTIONAL_H
#define _FUNCTIONAL_H
#include<functional>
#include<tuple>
namespace ministl
{
	extern const int MAXN = 10866;
	//一个行为类似函数的对象
	template<class Arg, class Result>
	struct unary_function
	{
		typedef Arg argument_type;
		typedef Result result_type;
	};

	template<class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template<class T>
	struct plus : binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x + y;
		}
	};

	template<class T>
	struct minus :binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x - y;
		}
	};

	template<class T>
	struct multiplies : binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x*y;
		}
	};

	template <class T>
	struct modulus : binary_function <T, T, T>
	{
		T operator() (const T& x, const T& y) const
		{
			return x%y;
		}
	};

	template<class T>
	struct negate :unary_function<T, T>
	{
		T operator()(const T& x) const
		{
			return -x;
		}
	};

	template<class T>
	struct less :binary_function<T, T, bool>
	{
		bool operator()(const T&lhs, const T& rhs) const
		{
			return lhs < rhs;
		}
	};
	
	template <class T>
	struct greater : binary_function<T, T, bool>
	{
		bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs > rhs;
		}
	};

	template <class T> 
	struct equal_to : binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const
		{
			return x == y;
		}
	};

	template<class T>
	struct greater_equal : binary_function<T, T, bool>
	{
		bool operator()(const T& lhs, const T& rhs)
		{
			return lhs >= rhs;
		}
	};

	template<class T>
	struct less_equal : binary_function<T, T, bool>
	{
		bool operator()(const T& lhs, const T& rhs)
		{
			return lhs <= rhs;
		}
	};

	template <class Predicate>
	class unary_negate
		: public unary_function <typename Predicate::argument_type, bool>
	{
	protected:
		Predicate fn;
	public:
		explicit unary_negate(const Predicate& pred) : fn(pred) {}
		bool operator() (const typename Predicate::argument_type& x) const
		{
			return !fn(x);
		}
	};

	template <class Predicate>
	class binary_negate
		: public binary_function<typename Predicate::first_argument_type, typename Predicate::second_argument_type, bool>
	{
	protected:
		Predicate fn;
	public:
		explicit binary_negate(const Predicate& pred) :fn(pred) {}
		bool operator() (const typename Predicate::first_argument_type& x,
			const typename Predicate::second_argument_type& y) const
		{
			return !fn(x, y);
		}
	};

	template<class Operation>
	class binder1st
		: public binary_function<typename Operation::first_argument_type, typename Operation::second_argument_type, typename  Operation::result_type>
	{
	protected:
		typename Operation::first_argument_type val;
		Operation op;
	public:
		explicit binder1st(const Operation& operation, const typename Operation::first_argument_type x) :op(operation).val(x) {}
		typename Operation::result_type operator()(const typename Operation::second_argument_type& xs)
		{
			return op(val, x);
		}
	};

	template<class Operation>
	class binder2nd
		: public binary_function<typename Operation::first_argument_type, typename Operation::second_argument_type, typename  Operation::result_type>
	{
	protected:
		typename Operation::second_argument_type val;
		Operation op;
	public:
		explicit binder2nd(const Operation& operation, const typename Operation::second_argument_type x) :op(operation).val(x) {}
		typename Operation::result_type operator()(const typename Operation::first_argument_type& xs)
		{
			return op(x, val);
		}
	};

	template<class Arg, class Result>
	class pointer_to_unary_function : public unary_function<Arg, Result>
	{
	protected:
		Result(*pfunc)(Arg);
	public:
		explicit pointer_to_unary_function(Result(*f)(Arg)) :pfunc(f) {}

		Result operator()(Arg x) const
		{
			return pfunc(x);
		}
	};

	template <class Arg1, class Arg2, class Result>
	class pointer_to_binary_function : public binary_function <Arg1, Arg2, Result>
	{
	protected:
		Result(*pfunc)(Arg1, Arg2);
	public:
		explicit pointer_to_binary_function(Result(*f)(Arg1, Arg2)) : pfunc(f) {}
		Result operator() (Arg1 x, Arg2 y) const
		{
			return pfunc(x, y);
		}
	};

	//接收一个T的指针，调用它返回S的那个成员函数
	template<class S,class T>
	class mem_fun_t : public unary_function<T*, S>
	{
		S(T::*pmem)();
	public:
		explicit mem_fun_t(S(T::*p)()) :pmem(p) {}
		S operator()(T* p)
		{
			return (p->*mem)();
		}
	};
	
	//Returns a function object that encapsulates function f.
	template <class Arg, class Result>
	pointer_to_unary_function<Arg, Result> ptr_fun(Result(*f)(Arg))
	{
		return pointer_to_unary_function<Arg, Result>(f);
	}

	template <class Arg1, class Arg2, class Result>
	pointer_to_binary_function<Arg1, Arg2, Result> ptr_fun(Result(*f)(Arg1, Arg2))
	{
		return pointer_to_binary_function<Arg1, Arg2, Result>(f);
	}

	template <class S, class T> mem_fun_t<S, T> mem_fun(S(T::*f)())
	{
		return mem_fun_t<S, T>(f);
	}

	template <class S, class T, class A>
	class mem_fun1_t : public binary_function <T*, A, S>
	{
		S(T::*pmem)(A);
	public:
		explicit mem_fun1_t(S(T::*p)(A)) : pmem(p) {}
		S operator() (T* p, A x) const
		{
			return (p->*pmem)(x);
		}
	};

	template <class S, class T, class A> mem_fun1_t<S, T, A> mem_fun(S(T::*f)(A))
	{
		return mem_fun1_t<S, T, A>(f);
	}

	template <class S, class T>
	class const_mem_fun_t : public unary_function <T*, S>
	{
		S(T::*pmem)() const;
	public:
		explicit const_mem_fun_t(S(T::*p)() const) : pmem(p) {}
		S operator() (T* p) const
		{
			return (p->*pmem)();
		}
	};

	template <class S, class T> const_mem_fun_t<S, T> mem_fun(S(T::*f)() const)
	{
		return const_mem_fun_t<S, T>(f);
	}

	template <class S, class T, class A>
	class const_mem_fun1_t : public binary_function <T*, A, S>
	{
		S(T::*pmem)(A) const;
	public:
		explicit const_mem_fun1_t(S(T::*p)(A) const) : pmem(p) {}
		S operator() (T* p, A x) const
		{
			return (p->*pmem)(x);
		}
	};

	template <class S, class T, class A> const_mem_fun1_t<S, T, A> mem_fun(S(T::*f)(A) const)
	{
		return const_mem_fun1_t<S, T, A>(f);
	}
	

	template <class S, class T>
	class mem_fun_ref_t : public unary_function <T, S>
	{
		S(T::*pmem)();
	public:
		explicit mem_fun_ref_t(S(T::*p)()) : pmem(p) {}
		S operator() (T& p) const
		{
			return (p.*pmem)();
		}
	};
	template<class S,class T,class A>
	class mem_fun1_ref_t : public binary_function<T, S, A>
	{
		S(T::*pmem)(A);
	public:
		explicit mem_fun1_ref_t(S(T::*p)(A)) :pmem(p) {}
		S operator()(T& p, A x) const
		{
			return (p.*pmem)(x);
		}
	};

	template <class S, class T>
	class const_mem_fun_ref_t : public unary_function <T, S>
	{
		S(T::*pmem)() const;
	public:
		explicit const_mem_fun_ref_t(S(T::*p)() const) : pmem(p) {}
		S operator() (T& p) const
		{
			return (p.*pmem)();
		}
	};

	template <class S, class T, class A>
	class const_mem_fun1_ref_t : public binary_function <T, A, S>
	{
		S(T::*pmem)(A) const;
	public:
		explicit const_mem_fun1_ref_t(S(T::*p)(A) const) : pmem(p) {}
		S operator() (T& p, A x) const
		{
			return (p.*pmem)(x);
		}
	};

	//Returns a function object that encapsulates member function f of type T.
	template <class S, class T>
	mem_fun_ref_t<S, T> mem_fun_ref(S(T::*f)())
	{
		return mem_fun_ref_t<S, T>(f);
	}

	template <class S, class T, class A>
	mem_fun1_ref_t<S, T, A> mem_fun_ref(S(T::*f)(A))
	{
		return mem_fun1_ref_t<S, T, A>(f);
	}

	template <class S, class T>
	const_mem_fun_ref_t<S, T> mem_fun_ref(S(T::*f)() const)
	{
		return const_mem_fun_ref_t<S, T>(f);
	}

	template <class S, class T, class A>
	const_mem_fun1_ref_t<S, T, A> mem_fun_ref(S(T::*f)(A) const)
	{
		return const_mem_fun1_ref_t<S, T, A>(f);
	}


	template <std::size_t...>
	struct tuple_indices {};


	template <std::size_t Sp, class IntTuple, std::size_t Ep>
	struct make_indices_imp;

	template <std::size_t Sp, std::size_t... Indices, std::size_t Ep>
	struct make_indices_imp<Sp, tuple_indices<Indices...>, Ep>
	{
		typedef typename make_indices_imp<Sp + 1, tuple_indices<Indices..., Sp>, Ep>::type type;
	};

	template <std::size_t Ep, std::size_t... Indices>
	struct make_indices_imp<Ep, tuple_indices<Indices...>, Ep>
	{
		typedef tuple_indices<Indices...> type;
	};

	template <std::size_t Ep, std::size_t Sp = 0>
	struct make_tuple_indices
	{
		typedef typename make_indices_imp<Sp, tuple_indices<>, Ep>::type type;
	};

	template <class F, class... Args>
	struct binder
	{
		binder(F&& f, Args&&... args) :data(std::forward<F>(f), std::forward<Args>(args)...) {}
		inline auto operator()()
		{
			typedef typename make_tuple_indices<std::tuple_size<std::tuple<F, Args...> >::value, 1>::type index_type;
			return run2(index_type());
		}
		template <std::size_t... Indices>
		void run2(tuple_indices<Indices...>)
		{
			invoke(std::move(std::get<0>(data)), std::move(std::get<Indices>(data))...);
		}
		inline auto invoke(F&& f, Args&&... args)
		{
			return std::forward<F>(f)(std::forward<Args>(args)...);
		}
		std::tuple<F,Args...> data;
	};
	

	template <class F, class... Args >
	ministl::binder<F,Args...> bind(F&& f, Args&&... args)
	{
		return binder<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...);
	}
}


#endif