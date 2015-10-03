#include "tools.h"

/*  Load file into memory
 *
 */ 

char* readFile(char *filename)
{
  FILE * file = fopen(filename, "r");

  if (file == 0) {
   printf(" :[ file not found-> %s \n", filename);
   exit(0);
  }
  
  fseek(file, 0L, SEEK_END);
  long numbytes = ftell(file);
  fseek(file, 0L, SEEK_SET);

  char *buffer = (char *)malloc( numbytes*sizeof(char) );

  if(buffer == NULL){ 
   printf("out of memory in ||  really in 2015 ?");
   exit(0);
  }

  fread(buffer, sizeof(char), numbytes, file);

  return buffer;
}

