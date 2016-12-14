// Include-Guard, so that we don't link & bind this header multiple times 
#ifndef SINGLESPEED_H
#define SINGLESPEED_H

/**
 * 				LEGENDE
 * 				
 * Singlespeed         -> "Eingangrad"
 * chainring, cr       -> Zahnrad_vorne
 * sprocket, sk        -> Zahnrad_hinten
 * wheel_diameter,d    -> Raddurchmesser
 * circumference       -> Umfang
 * expansion           -> Entfaltung
 * cadence             -> Trittfrequenz
 */

//Class Definition for a singlespeed-type bike
class Singlespeed
{
	/**
	 * Just our function declarations - 
	 * Definitions in "singlespeed.cpp"
	 */

public:

	/**
	 * Declaring our Constructor.
	 * As a special kind of function
	 * it has no return type. 
	 * It does return the instance 
	 * of our class when we call it.
	 */
	
	Singlespeed(const unsigned int cr, const unsigned int sk, const double d);

	/**
	 * Our member functions
	 *
	 * All of them are const since
	 * we do not change or set 
	 * values, we just read and 
	 * return them.
	 */
	
	double get_circumference() const;
	double get_expansion() const ;
	double get_speed(unsigned int cadence) const;

	//shows some info of our object on stdout
	void info() const;

	//Attributes
private:

	//all const since we do not alter them after our object is created
	const unsigned int chainring;
	const unsigned int sprocket;
	const double wheel_diameter;

};

#endif
