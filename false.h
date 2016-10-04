#pragma once

#include "boolean.h"

class False : public Boolean
{
	public:
		
		False ():
			Boolean ("false")
		{}

		False (const False & f):
			Boolean (f)
		{}

		~False ()
		{}

		bool is_true () const
		{
			return false;
		}

		bool is_false () const
		{
			return true;
		}

		Boolean * clone () const
		{
			return new False(*this);
		}
};
