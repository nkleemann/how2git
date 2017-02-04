/**
 * Global function Prototypes.
 *
 * Niklas Kleemann - 02.02.2017
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include "pbm.hpp"


/**
 * Evaluate Command line arguments, parse them into our opened filestreams
 * and display dialog. 
 * 
 * @param  ifile Bitmapfile to read from
 * @param  ofile Bitmapfile to write to
 * @param  argn  Argument Count
 * @param  args  Argument Strings
 * @return       false if we do not have enough arguments or files can not
 *               be opened. else true
 */
bool main_routine(std::ifstream &ifile, std::ofstream &ofile, int argn, char **args)
{
  if (argn != 3)
  {  
    std::cout << "usage: " << args[0] << " <in_file> <out_file>" << std::endl;
    return 0;
  }
  
  ifile.open(args[1]);
  ofile.open(args[2]);

  if (ifile.is_open() && ofile.is_open())
  {
    return 1;
  }
  else
  {
    std::cout << "Error opening file" << std::endl;
    return 0;
  }
}

/**
 * This function is just a little gimmick to make drawing lines
 * and boxes a little more interesting. It generates random Points
 * to draw a line and a rectangle in the given PBM object.
 * 
 * @param pbm PBM object to draw in
 */
void draw_rand(PBM &pbm)
{
  
  ulong sr, sc, er, ec;

  //we draw a vertical line of random length and a randomly sized rectangle
  for (ulong i = 0; i < 2; i++)
  {

    //seeding time in for loop now
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    er = static_cast<unsigned long>(std::rand()) % pbm.rows();
    sr = static_cast<unsigned long>(std::rand()) % er;

    sc = static_cast<unsigned long>(std::rand()) % pbm.cols();
    ec = sc;

    if (i == 0)
    {
      pbm.draw_line(sr, sc, er, ec);
    }
    else
    {
      //not so pretty but quick & always works (srand::time is to vague..)
      pbm.draw_rect(sr, sc, pbm.rows()-1, pbm.cols()-1);
    }
  }
}

/**
 * Just a fancy little animation to show-off. 
 * 40x40px pbm, fixed.
 */
void ani()
{
  std::srand(std::time(NULL));
  PBM pbm2(40, 40, 1, "NULL");

  for (int i = 0; i < 40; i++)
  {
    pbm2.draw_rect(0, 0, (int)(std::rand())%40, (int)(std::rand())%40);
    pbm2.print();

    system("sleep 0.1");
    system("clear");
    flush(std::cout);
  }
}
