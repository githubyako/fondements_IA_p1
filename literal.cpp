#include "literal.h"

std::ostream & operator << (std::ostream & os, const Literal & l)
{
	return os << l.to_string();
}
