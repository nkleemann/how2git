/**
 *  Generating P4-type PBM, C Version
 *  Input from STDIN
 */

#include <stdio.h>
#include <stdlib.h>


struct pgm
{
  unsigned int  width;
  unsigned int  height;
  unsigned int  max;
  unsigned char *data;
};


int write_pgm(const char *filename, const struct pgm *frame) 
{
  FILE *fp;
  fp = fopen(filename, "w");

  if (!fp) 
  {
    printf("Error while opening %s\n", filename);
    return 1;
  }

  // Writing header
  fprintf(fp, "P5\n%d %d\n%d\n", frame->width, frame->height, frame->max);

  // Writing data
  fwrite(frame->data, (size_t) frame->width, (size_t) frame->height, fp);

  fclose(fp);
  return 0;
}


int main(int argc, char **argv) 
{
  int i, c;
  unsigned char byte;
  struct pgm frame;

  if (argc < 3) 
  {
    printf("Usage: cat sequence | make_bitmap width height\n");
    return 1;
  }

  frame.width  = atoi(argv[1]);
  frame.height = atoi(argv[2]);

  if (frame.width > 4096 || frame.height > 4096) 
  {
    printf("Error: one dimension is > 4096\n");
    return 1;
  }

  // Max Greyscale Value
  frame.max = 255;

  frame.data = malloc(frame.width * frame.height);

  if (!frame.data) 
  {
    printf("Error: malloc() failed\n");
    return 1;
  }

  for (i = 0; i < frame.width * frame.height; i++) 
  {
    c = fgetc(stdin);
    
    if (c == EOF) 
    {
      printf("Error: unexpected EOF\n");
      return 1;
    }

    byte = (c == '0') ? 0 : 255;  
    
    frame.data[i] = byte;
  }

  write_pgm("bitmap.pgm", &frame);

  return 0;

}
