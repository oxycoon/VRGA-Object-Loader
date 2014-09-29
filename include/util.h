#pragma once
#ifndef _UTIL_H__
#define _UTIL_H__

#include <string>

// A function that will read a file into an allocated char pointer buffer
char* filetobuf(const char file[]);

void sdldie(std::string msg);

#endif //_UTIL_H__