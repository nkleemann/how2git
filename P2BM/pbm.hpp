/**
 * Class for generating, writing and reading
 * PBM P2-type ASCII Bitmap files. (v. P2)
 *
 * Niklas Kleemann - 02.02.2017
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#ifndef PBM_H
#define PBM_H

/**
 * silencing compiler warnings while 
 * keeping everything short&pretty..
 */
typedef unsigned long ulong;

class PBM 
{

public:

  PBM();
  PBM(const ulong row, const ulong col, int maxgrey, std::string cmt);

  bool is_whtspce(const ulong row, const ulong col) const;
  int orientation(const ulong srow, const ulong scol, const ulong erow, const ulong ecol) const;

  int draw_line(const ulong srow, const ulong scol, const ulong erow, const ulong ecol);
  void draw_rect(const ulong srow, const ulong scol, const ulong erow, const ulong ecol);

  friend std::ofstream &operator<<(std::ofstream &out, const PBM &pbm);
  friend std::ifstream &operator>>(std::ifstream &in, PBM &pbm);

  /******* DEBUG *******/

  void print() const;

  ulong rows() const;
  ulong cols() const;


private:

  std::vector<std::string > header;
  int maxgrey;
  std::vector< std::vector<unsigned char> > pixels;
  
};

#endif
