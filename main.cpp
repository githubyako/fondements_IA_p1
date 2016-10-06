#include <cstdlib>

#include "diagnostic.h"

int main (int argc, char * argv[])
{
	std::set < std::string > K;

	K.insert ("fievre");
	K.insert ("asthénie");
	K.insert ("malade");

	Diagnostic d1 (K);

	d1.forward_chaining();
	
	Diagnostic d2 (K);
	
	d2.backward_chaining("grippe");


	return EXIT_SUCCESS;
}
