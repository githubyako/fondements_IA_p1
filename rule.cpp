#include "rule.h"

unsigned int Rule::s_id = 0;

std::ostream & operator << (std::ostream & os, const Rule & r)
{	
	os << "[";
	for (auto e : r.get_premises())
	{
		os << "-(" << *e << ");";
	}
	os << *r.get_conclusion();
	os << "]";
	return os;
}
