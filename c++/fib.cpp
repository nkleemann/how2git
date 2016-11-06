#include <iostream>
#include <cstdlib>

int main (int argc, char **argv)
{
	unsigned int fib = 0, tmp = 1;

	for (unsigned int i = atoi(argv[1]); i-- && i < 47;)
	{
		printf("%i%c", fib, i?' ':'\n'); 		//toll, oder martin?
		fib += tmp;
		tmp  = fib - tmp;
	}
}
