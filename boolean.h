#pragma once


#include <string>
#include <iostream>


class Boolean
{
	private:
		
		std::string m_name;

	public:

		Boolean (const std::string & name):
			m_name (name)
		{}

		Boolean (const Boolean & b):
			m_name (b.m_name)
		{}

		virtual bool is_true () const = 0;
		virtual bool is_false () const = 0;

		const std::string & get_name () const
		{
			return m_name;
		}
		
		virtual std::string to_string () const
		{
			return m_name;
		}

		bool operator < (const Boolean & b) const
		{
			return ( to_string() < b.to_string());
		}

		bool operator == (const Boolean & b) const
		{
			return ( to_string() == b.to_string());
		}

		virtual Boolean * clone() const = 0;

	
		virtual ~Boolean() 
		{}
		
		    
		friend std::ostream & operator << (std::ostream & os, const Boolean & b)
		{
			return os << b.to_string();
		}
};