#include "util.h"
#include <cstdio>
#include <iostream>

#include "SDL.h"

char *filetobuf(const char file[]) {
  FILE *fptr;
  long length;
  char *buf;

  fptr = fopen(file, "rb"); // Open file for reading
  if (!fptr) 
    return NULL;
  fseek(fptr, 0, SEEK_END); 
  length = ftell(fptr); // Find out how many bytes into the file we are
  buf = (char *)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
  fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
  fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
  fclose(fptr); // Close the file
  buf[length] = 0; // Null terminator

  return buf; // Return the buffer
}

void sdldie(std::string msg) {
  std::cerr << msg << ":" << SDL_GetError() << std::endl;
  SDL_Quit();
  exit(1);
}