#pragma once

#include "boolean.h"

class Literal : public Boolean
{
	private:
		
		bool m_valuation;
			
	public:

		Literal (const std::string & name, bool valuation):
			Boolean (name),
			m_valuation (valuation)
		{}

		Literal (const Literal & l):
			Boolean (l),
			m_valuation (l.m_valuation)
		{}

		~Literal ()
		{}

		bool is_true () const
		{
			return m_valuation;
		}

		bool is_false () const
		{
			return !m_valuation;
		}
		
		std::string  to_string () const
		{
			return ( (m_valuation ? "" : "-") + Boolean::to_string () );
		}

		Boolean * clone () const
		{
			return new Literal (*this);
		}
};

std::ostream & operator << (std::ostream & os, const Literal & l)
{
	return os << l.to_string();
}