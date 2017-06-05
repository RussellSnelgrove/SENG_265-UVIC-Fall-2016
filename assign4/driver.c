#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

int main(int argc, char *argv[]) {
  struct Results result;
  char *lines[] = {
    ".LW 30",
    "While there    are enough characters   here to",
    "fill",
    "   at least one line, there is",
    "plenty",
    "of",
    "            white space that needs to be",
    "eliminated",
    "from the original",
    "         text file." 
  };
    int  num_lines = 10;

  result = format_lines(lines, &num_lines);

  if (result.data == NULL) {
    printf("%s: it appears 'format_lines' is not yet complete\n",
      argv[0]);
    exit(1);
  }

  int loop;
  for (loop = 0; loop < result.size; loop++) {
    printf ("%s\n", result.data[loop]);
  }

  exit(0);
}