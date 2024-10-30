#ifndef STRLIB_H
#define STRLIB_H

#include <stdbool.h>
#include <stdint.h> // For int32_t

// String struct definition
typedef struct {
    char *utf8;   // Pointer til starten af den UTF-8 encodede streng
    size_t byte_length;  // Længde i bytes
    size_t codepoint_length; // Længde i codepoints for effektivitet
} String;

// Function prototypes

// Constructing and Destructing Strings
String str_construct(const char *str);
void str_destruct(String string);
char *str_valueOf(String string);

// Length of string
size_t str_length(String string);
int32_t str_codePointAt(const String string, int index);

// Accessing characters
char str_charAt(const String string, int index);
char str_at(const String string, int index);

// Manipulating strings
String str_concat(const String str1, const String str2);
String str_slice(const String string, int start, int end);

// Search/comparing strings
int str_indexOf(const String haystack, const String needle);
bool str_includes(const String string, const String substring);

// Start and end checks
bool str_startsWith(const String string, const String prefix);
bool str_endsWith(const String string, const String suffix);

// Case Conversion
String str_toLowerCase(String string);
String str_toUpperCase(String string);

// Trimming
String str_trim(String string);
String str_trimStart(String string);
String str_trimEnd(String string);

#endif