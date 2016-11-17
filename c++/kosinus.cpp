//clang++ -Weverything -std=c++11 -o kosinus kosinus.cpp

/** 
 *   std::cout << std::numeric_limits<long double>::max(); 
 *   eval. on your machine for MAX_2N
 */

#include <iostream>
#include <cmath>
#include <tgmath.h>
#include <limits>

#define MAX_2N 661 //max 2n! for long double ..fak(2n)

long double fak(long double n);

int main()
{
  
  long double x = 0.0l;
  long double cosinus_x = 0.0l;  

  std::cout <<"\ncos(x):\n\tx > ";
  std::cin  >> x;

  x *= (M_PI/180); // xDeg -> xRadiant  

  for (long double n = 0.0l; n < MAX_2N; n++)
  {
        /* ********* DEBUG ********** 
         
        std::cout << "\n"

        << "n:\t"
        << n
        << "\t(-1)^n:\t\t"
        << powl(-1.0l, n)
        << "\tx^2*n:\t"
        << powl(x, (2.0l * n))
        << "\tNENNER:\t\t"
        << ((powl(-1.0l, n) * powl(x, (2.0l * n))))
        << "\tZÄHLER\t "
        << fak(2.0l*n)
        << "\tBRUCH:\t "
        << ((powl(-1.0l, n) * powl(x, (2.0l * n))))  / fak(2.0l*n)

        << "\tcos(x):\t"
        << cosinus_x;

        * ******** /DEBUG ********** */

    cosinus_x +=  ((powl(-1.0l, n) * powl(x, 2.0l * n)))  / fak(2.0l * n);
  }

  std::cout << "\ncos(" << x << ") ≈ " << cosinus_x << std::endl;
  std::cout << "KORREKT: " << cos(x) << std::endl;
}

long double fak(long double n)
{
  long double fak_n  = 1.0l;
  for (long double i = 2.0l; i <= n; i++)
  {
    fak_n *= i;
  }
  return fak_n;
}
