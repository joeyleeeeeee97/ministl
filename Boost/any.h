#pragma once
#ifndef _BOOST_ANY_H
#define _BOOST_ANY_H
#include<algorithm>
#include<typeinfo>
#include<iostream>
#include<assert.h>
namespace ministl
{
	class holder
	{
	public:
		virtual holder* clone() const = 0;
		virtual const std::type_info& type() const = 0;
		virtual ~holder()
		{

		}
	};

	template<typename value_type>
	class dataholder : public holder
	{
	private:
		typedef dataholder<value_type> self;
	public:
		dataholder(const value_type& v) :val(v) {}
		dataholder(const self&) = delete;
		self& operator = (const self& rhs) = delete;

		virtual dataholder* clone() const
		{
			return new dataholder(val);
		}

		virtual const std::type_info& type() const
		{
			return typeid(val);
		}
		value_type val;
	};

	class any
	{
	public:
		template<typename value_type>
		friend value_type& any_cast(const any& rhs);
		any() :content(nullptr) {}
		template<typename value_type>
		any(const value_type& val) :content(new dataholder<value_type>(val)) {}
		any(const any& rhs)
		{
			content = rhs.content->clone();
		}

		any& operator=(const any& rhs)
		{
			any tmp(rhs);
			std::swap(*this, tmp);
		}
		
		~any()
		{
			delete content;
		}

		const std::type_info& type() const
		{
			return content == nullptr ? typeid(void) : content->type();
		}
	private:
		holder* content;
	};

	template<typename value_type>
	value_type& any_cast(const any& rhs)
	{
		assert(typeid(typename value_type) == rhs.type());
		return static_cast<dataholder<value_type>*>(rhs.content)->val;
	}


	
}



#endif 