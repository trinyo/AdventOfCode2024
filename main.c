#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function for splitting strings
char **splitString(char *str, const char *delimiter) {
  char **splittedWord = (char **)malloc(sizeof(char *));
  char *token;
  token = strtok(str, delimiter);
  // Loop to get the remaining tokens
  int counter = 0;
  while (token != NULL) {
    if (splittedWord[counter] == NULL) {
      splittedWord = realloc(splittedWord, sizeof(char *) * (counter + 1));
      if (splittedWord == NULL) {
        printf("%s", "Memory allocation failed!1");
        exit(1);
      }
    }
    splittedWord[counter] = token;
    ++counter;
    token = strtok(NULL, delimiter); // Get the next token
  }
  return splittedWord;
}
// function for comparing
int compare(const void *a, const void *b) {
  // Cast the void pointers to integers
  int num1 = *(int *)a;
  int num2 = *(int *)b;

  // Return the difference for sorting in ascending order
  return num1 - num2;
}
int main() {
  FILE *inputFile = fopen("input.txt", "r");
  char *lineptr;
  size_t n;

  int *numbers1 = malloc(sizeof(int));
  int *numbers2 = malloc(sizeof(int));

  int counter = 0;
  while (getline(&lineptr, &n, inputFile) != -1) {
    char **splittedLine = splitString(lineptr, " ");

    numbers1 = realloc(numbers1, sizeof(int) * (counter + 1));
    numbers2 = realloc(numbers2, sizeof(int) * (counter + 1));

    if (numbers1 == NULL) {
      printf("%s", "Memory allocation failed!2");
      exit(1);
    }
    numbers1[counter] = atoi(splittedLine[0]);
    numbers2[counter] = atoi(splittedLine[1]);

    ++counter;
  }
  free(inputFile);
  free(lineptr);

  qsort(numbers1, counter, sizeof(int), compare);
  qsort(numbers2, counter, sizeof(int), compare);
  int sum = 0;
  for (int i = 0; i < counter; ++i) {
    int similarity = 0;
    for (int x = 0; x < counter; ++x) {
      if (numbers1[i] == numbers2[x]) {
        ++similarity;
      }
    }
    sum += similarity * numbers1[i];
  }

  printf("%s%i\n", "The result is: ", sum);
}