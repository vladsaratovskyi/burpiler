#include <stdio.h>
#include <stdlib.h>

#include "tokenizzer.h"

int main(int argc, char *argv[]) {

  printf("Source file: %s\n", argv[1]);

  FILE *source;
  source = fopen(argv[1], "r");

  char myString[100];

  // Read the content and print it
  while(fgets(myString, 100, source)) {
    printf("%s", myString);
  }

  printf("\n");
  printf("kek\n");

  tokenizze(source);

  return 0;
}
