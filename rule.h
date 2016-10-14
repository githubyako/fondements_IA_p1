#pragma once

#include <set>
#include "boolean.h"

class Rule 
{
	private:
	
		std::string m_name;
		std::set <Boolean *> m_premises;
		Boolean * m_conclusion;
		unsigned int m_id;

		static unsigned int s_id;
		

	public:
		
		Rule (const std::string & name, const std::set <Boolean *> premises, Boolean * conclusion):
			m_name (name),
			m_premises (premises), 
			m_conclusion (conclusion->clone()),
			m_id (++s_id)
		{}

		Rule (const Rule & r):
			m_name (r.m_name),
			m_premises (r.m_premises),
			m_conclusion (r.m_conclusion->clone()),
			m_id (r.m_id)
		{}

		~Rule ()
		{
			delete m_conclusion;
		}

		const std::set <Boolean *> & get_premises () const
		{
			return m_premises;
		}

		Boolean * get_conclusion () const
		{
			return m_conclusion;
		}

		const std::string & get_name () const
		{
			return m_name;
		}

		bool operator < (const Rule & r) const
		{
			return ( m_id < r.m_id );
		}

		bool operator == (const Rule & r) const
		{
			return ( m_id == r.m_id );
		}
		friend std::ostream & operator << (std::ostream & os, const Rule & r){
		  os << "[";
		  for (auto e : r.get_premises())
		  {
			  os << "-(" << *e << ");";
		  }
		  os << *r.get_conclusion();
		  os << "]";
		  return os; 
		}
};
