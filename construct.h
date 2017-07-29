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

//������destroy()�ڶ��汾 ���������������˺����跨�ҳ�Ԫ�ص���ֵ�ͱ�
//��������__type_traits<>��ȡ���ʵ��Ĵ�ʩ
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