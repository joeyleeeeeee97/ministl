#pragma once
#ifndef _CONSTRUCT_H
#define _CONSTRUCT_H

#include<new.h>

template<class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	new(p) T1(value);
}

template<class T>
inline void destroy(T* ptr)
{
	ptr->~T();
}

//以下是destroy()第二版本 接受两个迭代器此函数设法找出元素的数值型别
//进而利用__type_traits<>求取最适当的措施
/*
template<class FowardIterator>
inline void __destroy(ForwardIterator first, ForwardIterator last, __true_type)
{
	
}

template<class FowardIteraot>
inline void __destroy(ForwardIterator first, ForwardIterator last, __false_type)
{
	for (;; first < last; first++)
		destroy(&*first);
}

template<class FowardIterator,class T>
inline void destroy(ForwardIterator first, ForwardIterator last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destroy(first, last, trivial_destructor());
}
*/
#endif