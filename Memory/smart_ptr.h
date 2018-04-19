#pragma once
#ifndef _SMART_PTR_H
#define _SMART_PTR_H
#include <functional>
#include <assert.h>
#include <atomic>
/*
2018/4/18
auth joeylee
1. rewrite smart_ptr_node
2. provide cutomized deleter
*/
namespace ministl
{

	template<typename T>
	class Deleter {
	public:
		typedef std::function<void(T*)> DeleteFunc;

		Deleter(): func(std::bind(&Deleter::defaultfunc,this, std::placeholders::_1)){}
		Deleter(DeleteFunc df) :func(df) {}

		void operator()(T* p) const {
			func(p);
		};

	private:
		void defaultfunc(T* ptr) {
			ptr->~T();
		}
		DeleteFunc func;
	};

	template<typename T, typename Deleter = ministl::Deleter<T>>
	class unique_ptr {
	public:
		typedef T* pointer;
		unique_ptr() :data(nullptr), delfunc() {}
		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr(unique_ptr<T>&& rhs) :delfunc(rhs.delfunc), data(rhs.data) {
			rhs.data = nullptr;
		}

		unique_ptr<T>&  operator=(const unique_ptr<T>& rhs) = delete;
		
		~unique_ptr() {
			delfunc(data);
		}

		void reset() {
			delfunc(data);
			data = nullptr;
		}

		void reset(T* _data) {
			delfunc(data);
			data = _data;
		}

		pointer release() noexcept {
			pointer ret = data;
			data = nullptr;
			return ret;
		}

		pointer get() const noexcept {
			return data;
		}

		T& operator * () const noexcept{
			return *data;
		}

		T* operator ->() const noexcept{
			return &*this;
		}

	private:
		Deleter delfunc;
		T* data;
	};

	template<typename T, typename Deleter = ministl::Deleter<T>>
	class Data_node {
	public:
		Data_node() :refcnt(0), weakcnt(0), data(nullptr) {}
		Data_node(T* _data) : refcnt(1), weakcnt(1), data(_data) {}
		~Data_node() = default;

		void incref() {
			refcnt++;
		}
		void decref() {
			assert(refcnt != 0);
			refcnt--;
		}
		T* getData() {
			return data;
		}
		int getRefCnt() {
			return refcnt;
		}

		//for weak_ptr
		void incweak() {
			weakcnt++;
		}
		void desweak() {
			assert(weakcnt != 0);
			weakcnt--;
		}

		void increment() {
			refcnt++, weakcnt++;
		}
		void decrement() {
			refcnt--, weakcnt--;
			check();
		}
		// if we need to delete data or delete ptr_ndoe
		void check() {
			if (refcnt == 0) {
				delfunc(data);
				data = nullptr;
			}
			if (weakcnt == 0) {
				delete this;
			}
		}
		typedef std::atomic<int> atomic_int;
		Deleter delfunc;
		atomic_int refcnt;
		atomic_int weakcnt;
		T* data;
	};

	template<class T, typename Deleter = ministl::Deleter<T>>
	class shared_ptr
	{
		typedef Data_node<T, Deleter> node;
		typedef Data_node<T, Deleter>* node_ptr;
		typedef shared_ptr<T, Deleter> self;
	private:
		node_ptr ptr;
	public:
		shared_ptr()noexcept : ptr(nullptr)
		{
	
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
		shared_ptr(const node_ptr _ptr) {
			ptr = _ptr;
			ptr->increment();
		}
		~shared_ptr()
		{
			if (ptr != nullptr)
			{
				ptr->decrement();
				ptr = nullptr;
			}
		}
		
		operator bool() {
			return ptr != nullptr && ptr->refcnt != 0;
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
			return *(ptr->data);
		}
		size_t use_count()
		{
			if (ptr == nullptr) {
				return 0;
			}
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
			if (ptr == nullptr)return;
			ptr->decrement();
			ptr = new node();
		}
		//这里使用默认模板类型初始化删除器存在一个问题
		//无法动态改变智能指针类型
		//TODO 将删除器作为function放在指针类中
		/*template <class U> 
		void reset(U* p)
		{
			if (ptr == nullptr)return;
			ptr->decrement();
			ptr = new Data_node<U>(p);
		}*/

		T* get() noexcept
		{
			return ptr->ptr;
		}
		node_ptr get_node() noexcept {
			return ptr;
		}
	};

	template<class T, class...Args>
	shared_ptr<T> make_shared(Args... args)
	{
		return shared_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template<class T, typename Deleter = ministl::Deleter<T>>
	class weak_ptr {
		typedef Data_node<T, Deleter> node;
		typedef Data_node<T, Deleter>* node_ptr;
		typedef shared_ptr<T, Deleter> shared;
		typedef weak_ptr<T> self;
	public:
		weak_ptr() :ptr(nullptr) {
		}
		weak_ptr(const shared& rhs) {	
			ptr = rhs.ptr;
			if (rhs.ptr)
				ptr->incweak();
		}
		weak_ptr(const weak_ptr& r) noexcept {
			ptr = r.ptr;
			if (r.ptr)
				ptr->incweak();
		}
		weak_ptr(weak_ptr&& r) noexcept {
			ptr = r.ptr, r.ptr = nullptr;
		}

		self& operator=(const self& rhs) {
			if (ptr != nullptr) {
				ptr->desweak();
			}
			if (rhs.ptr != nullptr) {
				rhs.ptr->incweak();
			}
			ptr = rhs.ptr;
			return *this;
		}

		self& operator=(shared& rhs) {
			auto _ptr = rhs.get_node();
			if (ptr != nullptr) {
				ptr->desweak();
			}
			if (_ptr != nullptr) {
				_ptr->incweak();
			}
			ptr = _ptr;
			return *this;

		}


		~weak_ptr() {
			if (ptr != nullptr)
				ptr->desweak();
		}

		int use_count() {
			if (ptr == nullptr)
				return 0;
			return ptr->refcnt;
		}

		shared lock() {
			return expired() ? shared_ptr<T>() : shared_ptr<T>(ptr);
		}

		bool expired() const noexcept {
			return ptr == nullptr || ptr->refcnt == 0;
		}

	private:
		node_ptr ptr;
	};

}










#endif
