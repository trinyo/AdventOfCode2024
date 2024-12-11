#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct for visited coordinates
struct Point {
  int x; // x-coordinate
  int y; // y-coordinate
};

// function to check if a coordinate was visited
bool checkIfCordIsAlreadyVisited(struct Point **list, int n, int currentXCord,
                                 int currentYCord) {
  int index = 0;
  while (index < n &&
         (list[index]->x != currentXCord || list[index]->y != currentYCord)) {
    ++index;
  }
  if (index < n) {
    return true;
  } else {
    return false;
  }
}

int main() {
  FILE *inputFile = fopen("input.txt", "r");

  char **map = NULL;
  char *linptr = NULL;
  size_t n;

  int rowCounter = 0;
  int guardPostionX = 0;
  int guardPostionY = 0;

  while (getline(&linptr, &n, inputFile) != -1) {
    // Allocate memory for the pointer that points to char pointers
    map = (char **)realloc(map, sizeof(char *) * (rowCounter + 1));

    // Allocate memory for the pointer that points to characters
    map[rowCounter] = (char *)malloc(sizeof(char) * (strlen(linptr) + 1));
    strcpy(map[rowCounter], linptr);

    // Character indexer
    for (int columnCounter = 0; columnCounter < strlen(linptr);
         ++columnCounter) {
      if (linptr[columnCounter] == '^') {
        guardPostionX = rowCounter;
        guardPostionY = columnCounter;
      }
    }
    ++rowCounter;
  }
  free(linptr);
  fclose(inputFile);

  int mapRowCount = rowCounter;
  int mapColumnCount = strlen(map[0]);

  bool outOfBounds = false;
  int visitedTiles = 0;
  struct Point **visitedTilesList = NULL;
  int direction = 0;

  while (!outOfBounds) {
    switch (direction) {
    case 0:
      if (guardPostionX - 1 < 0) {
        ++visitedTiles;
        outOfBounds = true;
        break;
      }
      if (map[guardPostionX - 1][guardPostionY] == '#') {
        direction = 1;
      } else {
        if (!checkIfCordIsAlreadyVisited(visitedTilesList, visitedTiles,
                                         guardPostionX, guardPostionY)) {
          struct Point *currentPoint =
              (struct Point *)malloc(sizeof(struct Point));
          currentPoint->x = guardPostionX;
          currentPoint->y = guardPostionY;
          visitedTilesList = (struct Point **)realloc(
              visitedTilesList, sizeof(struct Point *) * (visitedTiles + 1));
          visitedTilesList[visitedTiles] = currentPoint;
          ++visitedTiles;
        }
        --guardPostionX;
      }
      break;

    case 1:
      if (guardPostionY + 1 >= mapColumnCount) {
        ++visitedTiles;
        outOfBounds = true;
        break;
      }
      if (map[guardPostionX][guardPostionY + 1] == '#') {
        direction = 2;
      } else {
        if (!checkIfCordIsAlreadyVisited(visitedTilesList, visitedTiles,
                                         guardPostionX, guardPostionY)) {
          struct Point *currentPoint =
              (struct Point *)malloc(sizeof(struct Point));
          currentPoint->x = guardPostionX;
          currentPoint->y = guardPostionY;
          visitedTilesList = (struct Point **)realloc(
              visitedTilesList, sizeof(struct Point *) * (visitedTiles + 1));
          visitedTilesList[visitedTiles] = currentPoint;
          ++visitedTiles;
        }
        ++guardPostionY;
      }
      break;

    case 2:
      if (guardPostionX + 1 >= mapRowCount) {
        ++visitedTiles;
        outOfBounds = true;
        break;
      }
      if (map[guardPostionX + 1][guardPostionY] == '#') {
        direction = 3;
      } else {
        if (!checkIfCordIsAlreadyVisited(visitedTilesList, visitedTiles,
                                         guardPostionX, guardPostionY)) {
          struct Point *currentPoint =
              (struct Point *)malloc(sizeof(struct Point));
          currentPoint->x = guardPostionX;
          currentPoint->y = guardPostionY;
          visitedTilesList = (struct Point **)realloc(
              visitedTilesList, sizeof(struct Point *) * (visitedTiles + 1));
          visitedTilesList[visitedTiles] = currentPoint;
          ++visitedTiles;
        }
        ++guardPostionX;
      }
      break;

    case 3:
      if (guardPostionY - 1 < 0) {
        ++visitedTiles;
        outOfBounds = true;
        break;
      }
      if (map[guardPostionX][guardPostionY - 1] == '#') {
        direction = 0;
      } else {
        if (!checkIfCordIsAlreadyVisited(visitedTilesList, visitedTiles,
                                         guardPostionX, guardPostionY)) {
          struct Point *currentPoint =
              (struct Point *)malloc(sizeof(struct Point));
          currentPoint->x = guardPostionX;
          currentPoint->y = guardPostionY;
          visitedTilesList = (struct Point **)realloc(
              visitedTilesList, sizeof(struct Point *) * (visitedTiles + 1));
          visitedTilesList[visitedTiles] = currentPoint;
          ++visitedTiles;
        }
        --guardPostionY;
      }
      break;
    }
  }

  printf("The result is: %i\n", visitedTiles);

  // Free allocated memory
  for (int i = 0; i < visitedTiles; ++i) {
    free(visitedTilesList[i]);
  }
  free(visitedTilesList);

  for (int i = 0; i < mapRowCount; ++i) {
    free(map[i]);
  }
  free(map);

  return 0;
}
