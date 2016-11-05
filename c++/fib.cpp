#include <iostream>
#include <cstdlib>

int main (int argc, char **argv)
{
	unsigned int fib = 0, tmp = 1;
<<<<<<< HEAD

	for (unsigned int i = atoi(argv[1]); i-- && i < 47;)
	{
	printf("%i%c", fib, i?' ':'\n'); //toll, oder martin?
	fib += tmp;
	tmp  = fib - tmp;
=======
  
  for (unsigned int i = atoi(argv[1]); i-- && i < 47;)
	{
	   printf("%i%c", fib, i?' ':'\n'); 									//toll, oder martin?
   	 fib += tmp;
     tmp  = fib - tmp;
>>>>>>> 8518f3165f97a1702d375fa9887fce0cc8769043
	}
}
