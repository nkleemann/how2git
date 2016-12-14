// Include-Guard, so that we don't link & bind this header multiple times 
#ifndef BIKE_H
#define BIKE_H

/**
 * LEGENDE
 * 				
 * BIKE                 -> RadmitGang, ganz normales Rad 
 * chainrings                 -> Kettenblaetter
 * cassette                -> Kassette (Alle Zahnraeder/Ritzel hinten)
 * count_cr                   -> anzahl_kettenblatter 
 * count_sk         -> anzahl_ritzel
 * cr               -> Kettenblatt
 * sk               -> Ritzel
 * d                -> Raddurchmesser
 * cadence          -> Triitfrequenz in Umdrehung pro Minute
 */

//Class definition for an ordenary Bike, which has gears ("RadMitGang")
class Bike
{

/**
 * Just our function declarations - 
 * Definitions in "bike.cpp"
 */

public:

	/**
	 * Declaring our Constructor.
	 * As a special kind of function
	 * it has no return type. 
	 * It does return the instance 
	 * of our class when we call it.
	 */

	Bike(const double d);

	/**
	 * All member functions, most of
	 * them are "const" since they do 
	 * not alter values, they just 
	 * need to read them.
	 */

	unsigned int count_cr() const;
	unsigned int count_sk() const;
	
	double get_circumference() const;
	double get_expansion() 	   const ;
	double get_speed(unsigned int cadence) const;

	//shows some fancy output on the screen
	void info() const;


	//This one is not "const" since we alter the variable "gear_ratio" with it
	void set_gear_ratio(unsigned int cr, unsigned int sk);

//Attributes
private:

	/**
	 * C-style Arrays, cause C++'s syntax is bulky > AF <
	 * and we don't need bound checks here.
	 *
	 * Keep in mind that chainrings[2] is an array of 
	 * size 2 with it's first element sitting 
	 * at chainring[0].
	 *
	 * Since we know our groupset very well and don't plan changing
	 * it via runtime we can initialize it and set it to 'const'.
	 */
	
	const unsigned int chainrings[2] = {34, 50};
	const unsigned int cassette[9]	 = {28, 24, 21, 19, 17, 15, 13, 12, 11};

	/**
	 * The gear you are using when riding your bike
	 * is defined by the size of the chainring 
	 * and sprocket you selected.
	 *
	 * If you divide chainring_size by sprocket_size you
	 * get the GEAR RATIO. 
	 *
	 * To simplyfy our calculations and avoid handling with
	 * more variables than we actually need we decide to
	 * substitute (chainring / sprocket) with our 
	 * variable gear_ratio.
	 *
	 * We set the default Ratio to the gear you get when
	 * you select the chainring of size 34 and sprocket of
	 * size 28, which is expressed as:
	 *
	 * chainrings[0] / cassette[0] ==
	 *
	 *           34  / 28
	 *
	 *
	 * Also we are dividing integers but want double-division
	 * with floating-point values, so we cast one divisor 
	 * to double. (C style). TO DO: Use C++ -style- Cast
	 */
	
	double gear_ratio = chainrings[0] / (double)cassette[0]; 

	const double wheel_diameter; 

};

#endif
