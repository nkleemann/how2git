/**
 *
 *    Writing to P4-type Bitmap (bytewise)
 *
 */

#include <iostream>
#include <fstream>
#include <time.h>   
#include <stdint.h> 
#include <cmath>


#define WIDTH  400
#define HEIGHT 400


int main(int argc, char **argv)
{

  std::ofstream pbm("YOOO.pbm", std::ios::out | std::ios::binary);

  /** 
   * Writing Header  ( 
   *                   0x50 0x34 0x20 0x34
   *                   0x30 0x30 0x20 0x34
   *                   0x30 0x30 0x20
   *                 )
   */
                      
  //To Do: Pass as string so my defines are actually usefull
  
  pbm.write("P4 400 400 ", 11); 


  // Data array
  
  uint8_t data[WIDTH * HEIGHT]; 
  int bit;
  int dim = WIDTH * HEIGHT;


  // Start iterating over body & writing data
  
  for (int i = 0; i < dim; i++) 
  {

    /**
     *  We are writing byte per byte - 
     *  setting each bit independently.
     */
    
    for (int j = 0; j < 8; j++) 
    {

      /**
       *  Example drawing logic.
       *  Data will be gathered from
       *  stdin in the future.
       */
      
      bit = (i*i*i < j) ? 0 : 1; 

      /**
       *  Set the last bit and shift 
       *  until byte is finished. 
       */
      
      data[i] = (data[i] << 1) | bit; 

    }
  }

  //casting, because .write needs char array
  
  pbm.write((char*)data, sizeof(data));


  pbm.close();
}

