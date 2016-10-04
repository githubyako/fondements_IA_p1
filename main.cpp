#include <cstdlib>

#include "diagnostic.h"

int main (int argc, char * argv[])
{
	std::set < std::string > K;

	K.insert ("fievre");
	K.insert ("asthénie");
	K.insert ("malade");

	Diagnostic d (K);

	d.forward_chaining();

	//std::cout << d.backward_chaining ("grippe") << std::endl;


	return EXIT_SUCCESS;
}
