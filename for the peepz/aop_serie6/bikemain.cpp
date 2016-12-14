/**
 * Our main Program which should contain
 * just a little logic, user interaction 
 * and input / output routines.
 */

#include "bike.h"
#include <iostream>

/**
 * The cadence we are generating with our
 * leg-guns (currently fixed), will be
 * fixed forever since this program
 * is pretty much useless.
 */
#define CADENCE 90

/**
 * Wrap printing this visual SEParation in a 
 * function so our code gets less bold and ugly..
 */
void sep();
void sep()
{
	std::cout << "\n\n######################################\n\n";
}

int main(int argc, char **argv)
{

	/**
	 * We call our constructor and generate
	 * an object of type "Bike" named "bike"
	 * and set the Wheel diameter to 0.65mm
	 */

	Bike bike(0.65);

	/**
	 * Show us some info about our 
	 * freshly created object on our screens please.
	 */
	
	bike.info();

	//This is a little messy, might implement this in Bike::info() aswell...
	std::cout << "Wheel circumference:\t"         << bike.get_circumference();
	std::cout << "\nExpansion:\t\t"               << bike.get_expansion();
	std::cout << "\nSpeed(" << CADENCE << ")\t\t" << bike.get_speed(CADENCE);
	sep();

	/**
	 * Let's change gears!
	 * (internally altering the gear_ratio - variable)
	 *
	 * This only affects speed and expension..
	 * no need printing the rest.
	 */

	bike.set_gear_ratio(1, 8);

	std::cout << "Changing gear...\n";
	std::cout << "\nExpansion:\t\t"                << bike.get_expansion();
	std::cout << "\nSpeed(" << CADENCE << ")\t\t"  << bike.get_speed(CADENCE);
	sep();
	
	/**
	
		TODO:
		- PRINT ALL SPEEDS (is this even english?) FOR ALL GEARS AT CADENCE 80
			-> should be easy using a double nested for loop

		- GIVE GEAR FOR GIVEN SPEED AND CADENCE
			-> since we use gear_ratio we need to work with our formula:
					gear_ratio = chainring / sprocket
			    to get our actual gear back. 
	
	 */

}

