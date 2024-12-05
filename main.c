#include <stdio.h>

int main() {
 FILE* fptr;
 fptr = fopen("input.txt","r"); 
 size_t sizeOfFile = (size_t)sizeof(*fptr);
  char* lineptr;

 while (getline(lineptr, sizeOfFile, fptr)) {
 
 }
 
 fclose(fptr);
}