#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compar(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b); // Compare the strings
}

int main() {
  FILE *fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    perror("Failed to open file");
    return 1;
  }

  char *lineptr = NULL;
  size_t n = 0;
  int sizeOfTheArrays = 0;
  size_t longestItem = 0;

  // First pass to determine the size of arrays and the longest token
  while (getline(&lineptr, &n, fptr) != -1) {
    ++sizeOfTheArrays;
    char *token;
    char delimiter[] = " ";
    token = strtok(lineptr, delimiter);

    while (token != NULL) {
      // Update the longest item length if necessary
      if (strlen(token) > longestItem) {
        longestItem = strlen(token);
      }
      token = strtok(NULL, delimiter);
    }
  }

  // Allocate memory for list1 and list2 dynamically
  char **list1 = malloc(sizeOfTheArrays * sizeof(char *));
  char **list2 = malloc(sizeOfTheArrays * sizeof(char *));
  for (int i = 0; i < sizeOfTheArrays; i++) {
    list1[i] =
        malloc((longestItem + 1) * sizeof(char)); // +1 for the null terminator
    list2[i] =
        malloc((longestItem + 1) * sizeof(char)); // +1 for the null terminator
  }

  // Reset the file pointer to read from the start of the file again
  rewind(fptr);
  int listIndex = 0;
  int tokenIndex = 0;

  // Second pass to split the lines and fill list1 and list2
  while (getline(&lineptr, &n, fptr) != -1) {
    char *token;
    char delimiter[] = " ";
    token = strtok(lineptr, delimiter);

    while (token != NULL) {
      if (strlen(token) <= longestItem) {
        // Check if the token length fits within the allocated space
        if (tokenIndex % 2 == 0) {
          // If even index, copy to list1
          strcpy(list1[listIndex], token);
        } else {
          // If odd index, copy to list2
          strcpy(list2[listIndex], token);
        }
      } else {
        // Token is too long, handle it (e.g., skip it)
        fprintf(stderr,
                "Warning: Token '%s' is too long and will be skipped.\n",
                token);
      }

      token = strtok(NULL, delimiter);
      tokenIndex++;
    }
    listIndex++;
  }

  // Length of the lists
  size_t nmemb = sizeOfTheArrays; // The number of elements in list1 and list2

  // Sort list1 and list2 using qsort
  qsort(list1, nmemb, sizeof(char *), compar);
  qsort(list2, nmemb, sizeof(char *), compar);

  int sum = 0;
  for (int i = 0; i < sizeOfTheArrays; ++i) {
    printf("%s - %s - %i\n", list1[i], list2[i], i);
    sum += abs(atoi(list1[i]) - atoi(list2[i]));
  }

  printf("The answer is: %d\n", sum);

  // Free dynamically allocated memory
  for (int i = 0; i < sizeOfTheArrays; i++) {
    free(list1[i]);
    free(list2[i]);
  }
  free(list1);
  free(list2);

  fclose(fptr);
  free(lineptr); // Free the buffer allocated by getline
  return 0;
}
