//Function definitions for our Class "Bike" in bike.h

/**
 * LEGENDE
 * 				
 * BIKE             -> RadmitGang, ganz normales Rad 
 * chainrings       -> Kettenblaetter
 * sprocket         -> Ritzel
 * cassette         -> Kassette (Alle Zahnraeder/Ritzel hinten)
 * count_cr         -> anzahl_kettenblatter 
 * count_sk         -> anzahl_ritzel
 * cr               -> Kettenblatt
 * sk               -> Ritzel
 * d                -> Raddurchmesser
 * cadence          -> Triitfrequenz in Umdrehung pro Minute
 */

#include "bike.h"
#include <cmath>	//for M_PI (3.14xxxxxyouknowthedeal)
#include <iostream>	//for calls in info()

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

Bike::Bike(const double d) 

: wheel_diameter ( d)

{
	//Don't need nothing in here
}

/**
 * Counts our chainrings.
 * 
 * @return Number of chainrings (elements of array - chaingrings)
 */
unsigned int Bike::count_cr() const
{
	/**
	 * We could always
	 *
	 * return 2;
	 *
	 * here, but that has no learn effect,
	 * I guess..
	 */
	
	/**
	 * We divide the size of our complete array in bytes
	 * by the size of one of it's elements (the first)
	 * in bytes. this returns the length in 'elements'.
	 *
	 * Using this method because we (I) still do not like
	 * C++ - style Arrays and don't want to deal with 
	 * bulky syntax. :)
	 */
	
	return ( sizeof(chainrings) / sizeof(*chainrings) );
	
}

/**
 * Counts our sprockets.
 * 
 * @return Number of sprockets (elements of array - cassette)
 */
unsigned int Bike::count_sk() const
{
	//See "count_cr()" for more details
	return ( sizeof(cassette) / sizeof(*cassette) );
	
}

/**
 * Sets our gear ratio -- Selects the gear we are in.
 * 
 * @param cr_nr chainring number - number of element in array "chainrings"
 * @param sk_nr sprocket  number - number of element in array "cassette"
 */
void Bike::set_gear_ratio(unsigned int cr_nr, unsigned int sk_nr)
{
	/**
	 * Remember, we are counting from zero.
	 *
	 * So for better readabillity when calling this function, 
	 * we subtract 1 from our argument. because chainring: 1
	 * sits at chainrings[0].
	 */
	
	gear_ratio = (chainrings[cr_nr] - 1) / ( cassette[sk_nr] - 1); 
}

/**
 * Calculates the circumference of our wheel.
 * 
 * @return circumference in mm
 */
double Bike::get_circumference() const
{
	return (M_PI * wheel_diameter); 
}

/**
 * Calculates the expansion of our wheel, based on
 * chainring- and sprocketsize -- which defines our 
 * gear ratio. 
 *
 * Keep in mind:
 *
 * 	(chainring / sprocket) == gear_ratio;
 * 
 * @return Expansion in m
 */
double Bike::get_expansion() const
{
	return gear_ratio * (M_PI * wheel_diameter);
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
double Bike::get_speed(unsigned int cadence) const
{
	return ((cadence * 60) * gear_ratio * (M_PI * wheel_diameter) / 1000);
}

/**
 * Just a fancy show-off of our attributes given to the
 * instance of our object.
 */
void Bike::info() const
{
	std::cout << "\n############## My BIKE ##############\n";

	
	std::cout << "\nChainrings:\t\t";
	for (unsigned int i = 0; i < count_cr(); i++)
		std::cout << chainrings[i] << " ";
	
	std::cout << "\nCassette:\t\t";
	for (unsigned int i = 0; i < count_sk(); i++)
		std::cout << cassette[i] << " ";

	std::cout << "\nWheel Diameter:\t\t"   	<< wheel_diameter << std::endl;	
}
