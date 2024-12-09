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
      if (lines[i][y] == 'X') {
        // Diagonal up-left
        if (i - 3 >= 0 && y - 3 >= 0) {
          if (lines[i - 1][y - 1] == 'M' && lines[i - 2][y - 2] == 'A' &&
              lines[i - 3][y - 3] == 'S') {
            ++wordCounter;
          }
        }

        // Diagonal up-right
        if (i - 3 >= 0 && y + 3 < maxColumn) {
          if (lines[i - 1][y + 1] == 'M' && lines[i - 2][y + 2] == 'A' &&
              lines[i - 3][y + 3] == 'S') {
            ++wordCounter;
          }
        }

        // Diagonal down-left
        if (i + 3 < maxRow && y - 3 >= 0) {
          if (lines[i + 1][y - 1] == 'M' && lines[i + 2][y - 2] == 'A' &&
              lines[i + 3][y - 3] == 'S') {
            ++wordCounter;
          }
        }

        // Diagonal down-right
        if (i + 3 < maxRow && y + 3 < maxColumn) {
          if (lines[i + 1][y + 1] == 'M' && lines[i + 2][y + 2] == 'A' &&
              lines[i + 3][y + 3] == 'S') {
            ++wordCounter;
          }
        }

        // Horizontal left
        if (y - 3 >= 0) {
          if (lines[i][y - 1] == 'M' && lines[i][y - 2] == 'A' &&
              lines[i][y - 3] == 'S') {
            ++wordCounter;
          }
        }

        // Horizontal right
        if (y + 3 < maxColumn) {
          if (lines[i][y + 1] == 'M' && lines[i][y + 2] == 'A' &&
              lines[i][y + 3] == 'S') {
            ++wordCounter;
          }
        }

        // Vertical up
        if (i - 3 >= 0) {
          if (lines[i - 1][y] == 'M' && lines[i - 2][y] == 'A' &&
              lines[i - 3][y] == 'S') {
            ++wordCounter;
          }
        }

        // Vertical down
        if (i + 3 < maxRow) {
          if (lines[i + 1][y] == 'M' && lines[i + 2][y] == 'A' &&
              lines[i + 3][y] == 'S') {
            ++wordCounter;
          }
        }
      }
    }
  }
  printf("%s%i", "The result is: ", wordCounter);
  return 0;
}