/**
 * PBM-Class prototype functions.
 *
 * The model for "Point" inside our bitmap I use is:
 * P(row, col) - where row is the Row-Index and col is the
 * collumn index. I find that to be more readable than using
 * x and y. 
 * 
 * Since we always print and iterate from top to bottom modelling
 * our bitmap as a coordinate system, which the usage of x and y 
 * implies, would be rather complicated and not so practical, imo.
 *
 * Please keep that in mind whenever you read about "Points" in my
 * documentation. 
 *
 * Also we only use P2 - Type ASCII PGM's. I have written some procedural
 * Code handling P4-Type Binary Bitmap files as a module for a personal 
 * project, which I might integrate. 
 *
 * Niklas Kleemann - 02.02.2017
 */

#include "pbm.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

typedef unsigned long ulong;

/**
 * Basic and default Constructor.
 */
PBM::PBM()
{

}

/**
 * Construct PBM with initial data.
 * 
 * @param Row Number of rows in bitmap 
 * @param Col Number of collumns in bitmap
 * @param Maxgrey Maximum Grey-Value for individual pixel
 * @param Cmt Optional Comment used in header 
 */
PBM::PBM(const ulong Row, const ulong Col, int Maxgrey, std::string Cmt)
: maxgrey (Maxgrey)
{
  //Building file-header (P2 fixed atm, might extend to use with binary PBM's later)
  
  header.push_back("P2\n"); 
  header.push_back("# " + Cmt + '\n'); 
  header.push_back(std::to_string(Col) + ' ' + std::to_string(Row) + '\n');
  header.push_back(std::to_string(maxgrey) + '\n');

  //Initialising data array 
  
  pixels.resize(Row);

  for (ulong i = 0; i < Row; i++)
  {
    for (ulong j = 0; j < Col; j++)
    {
      pixels.at(i).push_back(0);
    }
  }
}

/**
 * Detect whitespace in data array & making it readable.
 *
 * Allthough it is not used here, it can be usefull
 * as I expand this program in the future.
 * 
 * @param  row Row-Index in data-array
 * @param  col Collumn-Index in data-array
 * @return     true if character is newline or space, false if not
 */
bool PBM::is_whtspce(const size_t row, const size_t col) const
{
  const unsigned char c = pixels.at(row).at(col);
  //since we only use newlines & spaces it is safe,atm, to discard the others
  return (c == ' ' || c == '\n');
}

/**
 * Multi-purpouse function for checking if
 * a line, given by two Points, is drawable (read: vertical or horizontal) 
 * and returning the type of line it is going to be.
 *
 * 
 * @param  srow Row-Index to start at
 * @param  scol Collumn-Index to start at
 * @param  erow Row-Index to stop at
 * @param  ecol Collumn-Index to stop at 
 * @return      1: line is horizontal, 2: line is vertical, 0: line is neither
 */
int PBM::orientation(const ulong srow, const ulong scol, const ulong erow, const ulong ecol) const
{
  //horizontal
  if (!(erow - srow))
    return 1;

  //vertical
  else if (!(ecol - scol))
    return 2;

  else
    return 0;
}

/**
 * Drawing a line in the bitmap using two Points: P_0(srow, scol) and P_1(erow, ecol)
 * Sets the value of our Data-Array to pbm.maxgrey (set calling the 
 * second constructor) for optimum contrast.
 *
 * It was requested to implement this as a bool-type function, but for better
 * readabillity and future plans to use this class in other projects I extended
 * the return type to int. This MAINTAINS the requested usage because it still 
 * returns true if a line has been drawn and false if not. But also it tells the
 * calling program which line it has drawn by returning 1 for horizontal and 2 for
 * vertical lines.
 * 
 * Also I think using this kind of "state-approach" offers good readabillity.
 * (May define an extra enum type for lines and other geometrical figures in the f.)
 *
 * 
 * @param  srow Row-Index to start drawing at
 * @param  scol Collumn-Index to start drawing at
 * @param  erow Row-Index to stop drawing at
 * @param  ecol Collumn-Index to stop drawing at 
 * @return      1: line is horizontal, 2: line is vertical, 0: line is neither
 */
int PBM::draw_line(const ulong srow, const ulong scol, const ulong erow, const ulong ecol)
{
  int line_type = orientation(srow, scol, erow, ecol);

  //hrztl
  if (line_type == 1) 
  {
    for (ulong i = scol; i <= ecol; i++)
    {
      pixels.at(srow).at(i) = static_cast<unsigned char>(maxgrey);
    }
  }

  //vert
  if (line_type == 2)
  {
    for (ulong i = srow; i <= erow; i++)
    {
      pixels.at(i).at(scol) = static_cast<unsigned char>(maxgrey);
    }
  }

  return line_type;
}

/**
 * Drawing a rectangle spanned by two given points inside our Data-Array.
 * First Point given is P_0(srow, scol), second P_1(erow, ecol). The first
 * always is the top left, the second the bottom right point. Illustration:
 *
 *
 *      P_0-------------------*
 *       |                    |
 *       |                    |
 *       |                    |
 *       |                    |
 *       *-------------------P_1
 *
 * 
 *
 * @param  srow Row-Index to start drawing at
 * @param  scol Collumn-Index to start drawing at
 * @param  erow Row-Index to stop drawing at
 * @param  ecol Collumn-Index to stop drawing at 
 */
void PBM::draw_rect(const ulong srow, const ulong scol, const ulong erow, const ulong ecol)
{
  for (ulong i = srow; i <= erow; i++)
  {
    for (ulong j = scol; j <= ecol; j++)
    {
      if (i == srow || i == erow || j == scol || j == ecol)
      {
        pixels.at(i).at(j) = static_cast<unsigned char>(maxgrey);
      }

      else
      {
        continue;
      }
    }
  }
}


/**
 * Overloading operator<< for formatted printing of our PBM
 * object to an open filestream.
 *
 * @param out Output filestream
 * @param pbm PBM object, intern modelled-bitmap
 * @return out Output filestream, which now contains header and pixel info.
 */
std::ofstream &operator<<(std::ofstream &out, const PBM &pbm)
{
  for (ulong i = 0; i < pbm.header.size(); i++)
  {
      out << pbm.header.at(i);
  }
  
  ulong rows = pbm.pixels.size();
  ulong cols = pbm.pixels.at(0).size();

  for (ulong i = 0; i < rows; i++)
  {
    for (ulong j = 0; j < cols; j++)
    {
      out << static_cast<int>(pbm.pixels.at(i).at(j)) << ' ';
    }
    out << '\n';
  }

  return out;

}


/**
 * Overloading operator>> for reading/parsing *.pbm files and
 * turning them into our modelled objects.
 *
 * @param in Input filestream
 * @param pbm PBM object, intern modelled-bitmap
 * @return in Giving back the read ifstream
 */
std::ifstream &operator>>(std::ifstream &in, PBM &pbm)
{

  //Let's do some hacked-together parsing..

  std::string line;

  /**
   * I know, using fixed-length loops is not-so-cool
   * but in this case we know our header will ALWAYS
   * have 4 lines, divided by 'newline'.
   *
   * Unless we find a bitmap with missing comment-line..
   * We then have to work with seeking file-pointers to navigate
   * through the header or use a different parsing-approach.
   *
   * I will point out fixed positions whenever i use them.
   *
   * But it works for now with the bitmaps I generate and use.
   */
  
  for (int i = 0; i < 4; i++)
  {
    std::getline(in, line);
    pbm.header.push_back(line + '\n');
  }

  /****** PARSING DIMENSIONS *******/

  ulong col, row;

  //begin splitting the string containing the dimension by ' '
  std::string str(pbm.header.at(2));

  //create buffer, and throw our string in a stringstream
  
  std::string buf; 
  std::stringstream ss(str); 

  //array to hold our tokens
  std::vector<std::string> tokens; 

  while (ss >> buf)
  {
    tokens.push_back(buf);
  }

  //again, fixed position
  col = static_cast<ulong>(std::stoi(tokens.at(0)));
  row = static_cast<ulong>(std::stoi(tokens.at(1)));

  /******         DONE      *******/

  //and fixed again
  pbm.maxgrey = std::stoi(pbm.header.at(3));

  /****++    PARSING DATA   *******/

  pbm.pixels.resize(row);

  for (ulong i = 0; i < row; i++) 
  {
    pbm.pixels.at(i).resize(col);
  }

  int px;

    for (ulong i = 0; i < col; i++)
    {
      for (ulong j = 0; j < col; j++)
      {
        in >> px;
        pbm.pixels.at(i).at(j) = static_cast<unsigned char>(px);
      }
    }

  /******         DONE      *******/

  return in;
}

/******* DEBUG *******/

/**
 * Getting the Number of rows.
 * 
 * @return Number of rows in Bitmap
 */
ulong PBM::rows() const
{
  return pixels.size();
}

/**
 * Getting the Number of collumns.
 * 
 * 
 * @return Number of collumns in Bitmap
 */
ulong PBM::cols() const
{ 
  //muh boundchecks..
  return pixels.at(0).size();
}

/**
 * This function is for debugging-purpouse.
 * I use it for formatted-printing our pbm to std::cout
 * for quick unix-style piping or redirecting. Handy for
 * checking if something is WAYY off or not.
 */
void PBM::print() const
{  
  for (ulong i = 0; i < header.size(); i++)
  {
      std::cout << header.at(i);
  }
  

  for (ulong i = 0; i < pixels.size(); i++)
  {
    for (ulong j = 0; j < pixels.size(); j++)
    {
      std::cout << static_cast<int>(pixels.at(i).at(j)) << ' ';
    }
    std::cout << '\n';
  }
}
