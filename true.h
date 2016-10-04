#pragma once

#include "boolean.h"

class True : public Boolean
{
	public:
		
		True ():
			Boolean ("true")
		{}

		True (const True & t):
			Boolean (t)
		{}

		~True ()
		{}

		bool is_true () const
		{
			return true;
		}

		bool is_false () const
		{
			return false;
		}

		Boolean * clone () const
		{	
			return new True(*this);
		}

	
};
