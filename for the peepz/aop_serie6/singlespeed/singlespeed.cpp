/** 
 * Function definitions for our Class "Singlespeed"
 */

#include "singlespeed.h"
#include <cmath>     //for M_PI
#include <iostream>  //for calls in info()

/**
 * Defining our constructor and
 * passing our arguments as list
 * which is faster and allows 
 * initialisation of variables
 * declared as 'const'. Cause:
 *
 * const int a = 1;  <- works
 * 
 * const int a;
 * a = 1;            <- doesn't
 *
 * We use the passed arguments to 
 * initialize our created object 
 * with values we wish for.
 */

Singlespeed::Singlespeed(unsigned int cr, unsigned int sk, const double d)

: chainring      (cr)
, sprocket       (sk)
, wheel_diameter ( d)

{
	//Don't need nothing in here
}

/**
 * Calculates the circumference of our wheel.
 * 
 * @return circumference in mm
 */
double Singlespeed::get_circumference() const
{
	return (M_PI * wheel_diameter); 
}

/**
 * Calculates the expansion of our wheel, based on
 * chainring- and sprocketsize.
 * 
 * @return Expansion in m
 */
double Singlespeed::get_expansion() const
{
	return (chainring /  sprocket) * (M_PI * wheel_diameter);
}

/**
 * Calculates the speed we are going based on our expansion 
 * and a given cadence.
 *
 * We have to convert our units, tho
 * 
 * @param  cadence  crank revolutions per minute
 * @return          speed in km/h
 */
double Singlespeed::get_speed(unsigned int cadence) const
{
	return ((cadence * 60) * (chainring / sprocket) * (M_PI * wheel_diameter) / 1000);
}

/**
 * Just a fancy show-off of our attributes given to the
 * instance of our object.
 */
void Singlespeed::info() const
{
	std::cout << "\n############## My BIKE ##############\n";

	std::cout << "\nChainring:\t\t"      << chainring;
	std::cout << "\nSprocket:\t\t"       << sprocket; 	
	std::cout << "\nWheel Diameter:\t\t" << wheel_diameter << std::endl;	
}
