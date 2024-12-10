#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  FILE *inputFile = fopen("input.txt", "r");

  char *lineptr;
  size_t n;

  char **lines = NULL;

  int row = 0;

  int maxRow;
  int maxColumn;
  // loop through the lines
  while (getline(&lineptr, &n, inputFile) != -1) {

    lines = (char **)realloc(lines, sizeof(char *) * (row + 1));
    lines[row] = (char *)malloc(sizeof(char) * strlen(lineptr) + 1);
    if (lines == NULL) {
      printf("%s", "Memory alloc failed!");
      exit(1);
    }
    // copy line
    int column = 0;
    while (column < strlen(lineptr)) {
      lines[row][column] = lineptr[column];
      ++column;
    }
    maxColumn = column;
    ++row;
  }

  maxRow = row;

  fclose(inputFile);
  free(lineptr);

  int wordCounter = 0;
  for (int i = 0; i < maxRow; ++i) {
    for (int y = 0; y < maxColumn; ++y) {
      // boundary check
      if (lines[i][y] == 'A' && i - 1 >= 0 && y - 1 >= 0 && i + 1 < maxRow &&
          y + 1 < maxColumn && i + 1 < maxRow && y - 1 >= 0 && i - 1 >= 0 &&
          y + 1 < maxColumn) {
        // top-left and bottom-right
        if ((((lines[i - 1][y - 1] == 'M' && lines[i + 1][y + 1] == 'S') ||
              (lines[i - 1][y - 1] == 'S' && lines[i + 1][y + 1] == 'M'))) &&
            // bottom-left and top-right
            (((lines[i + 1][y - 1] == 'M' && lines[i - 1][y + 1] == 'S') ||
              (lines[i + 1][y - 1] == 'S' && lines[i - 1][y + 1] == 'M')))) {
          ++wordCounter;
        }
      }
    }
  }
  free(lines);

  printf("%s%i", "The result is: ", wordCounter);
  return 0;
}