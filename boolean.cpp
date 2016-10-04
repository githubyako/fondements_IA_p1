#include "boolean.h"

std::ostream & operator << (std::ostream & os, const Boolean & b)
{
	return os << b.to_string();
}
