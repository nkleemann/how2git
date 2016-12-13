#include "singlespeed.h"
#include <iostream>

/**
 * Could pass those as arguments 
 * but since our program is pretty 
 * much useless and only serves
 * educational purpouse.. who cares
 */

#define CADENCE 	80 
#define CHAINRING 	53
#define SPROCKET	11
#define W_DIAMETER	0.65

int main(int argc, char **argv)
{

	/**
	 * We generate an object/ instance of
	 * our class "Singlespeed" by calling 
	 * our constructor. 
	 *
	 * Also we initialize it's attributes
	 * with values we passed.
	 */
	
	Singlespeed singlespeed(CHAINRING, SPROCKET, W_DIAMETER);

	

	singlespeed.info();

	std::cout << "Wheel circumference:\t" 			<< singlespeed.get_circumference();
	std::cout << "\nExpansion:\t\t"  					<< singlespeed.get_expansion();
	std::cout << "\nSpeed(" << CADENCE << ")\t\t" 	<< singlespeed.get_speed(CADENCE);

	std::cout << "\n\n######################################\n\n";
}
