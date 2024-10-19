#ifndef STRLIB_H
#define STRLIB_H

#include <stdbool.h>

//Function prototypes

//length of string
int strlib_strlen(const char *str);

//Accessing characters
char str_charAt(const char *str, int index);
char str_at(const char *str, int index);

//Manipulating strings
void str_concat(char *dest, const char *src);
void str_slice(char *dest, const char *src, int start, int end);

//search/comparing strings
int str_indexOf(const char *str, const char *substring);
bool str_includes(const char *str, const char *substring);

//Start and end checks
bool str_startsWith(const char *str, const char *prefix);
bool str_endsWith(const char *str, const char *suffix);

#endif