/**
 * Program entryoint. 
 *
 * Niklas Kleemann 02.02.2017
 */

#include "pbm.hpp"
#include <iostream>
#include <fstream>
#include <exception>


void draw_rand(PBM &);
bool main_routine(std::ifstream &, std::ofstream &, int argn, char **);
void ani();

int main(int argc, char **argv)
{ 

  try 
  {

    PBM pbm;
    std::ifstream ifile;
    std::ofstream ofile;

    //handle args and open filestreams

    if (main_routine(ifile, ofile, argc, argv))
    {
    
      //parse file into object

      ifile >> pbm;
      ifile.close();


      //draw some random lines & rectangles

      for (int i = 0; i < 10e3; i++)
      {
        draw_rand(pbm);
      }
      

      //write to file and close

      ofile << pbm;
      ofile.close();

    }

    //main_routine() handles output if something is off

    else
      return -1;

    //leaving you with a short fancy animation..
    
    ani();

  }


  //very verbouse error handling right here

  catch (const std::exception &e) 
  {

    std::cerr << "\n\n" << e.what() << std::endl;
  }

}
