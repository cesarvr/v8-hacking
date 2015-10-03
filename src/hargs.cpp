#include <stdio.h> 
#include <stdlib.h>
#include "include/tools.h"


int main(int argc, char * argv[]) {

  if (argc != 2) {
      printf("usage: %s Javascript file. \n", argv[0]);
  } else {
    char *buffer = readFile(argv[1]);
    printf( "data-> %s", buffer );
    free(buffer);
  }

  return 0;
}
