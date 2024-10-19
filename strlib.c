#include "strlib.h"
#include <ctype.h>
#include <string.h>

// Length
int str_length(const char *str) {
    const char *s = str;
    while (*s) s++;
    return s - str;
}

// Access
char str_charAt(const char *str, int index) {
    return str[index];
}

char str_at(const char *str, int index) {
    int len = str_length(str);
    if (index < 0) index += len;
    if (index >= 0 && index < len) return str[index];
    return '\0';
}

// Manipulation
void str_concat(char *dest, const char *src) {
    while (*dest) dest++;
    while ((*dest++ = *src++));
}

void str_slice(char *dest, const char *src, int start, int end) {
    int len = str_length(src);
    if (start < 0) start += len;
    if (end < 0) end += len;
    if (start < 0) start = 0;
    if (end > len) end = len;
    src += start;
    while (start++ < end && (*dest++ = *src++));
    *dest = '\0';
}

// Search/Comparison
int str_indexOf(const char *str, const char *substring) {
    const char *p = strstr(str, substring);
    return p ? p - str : -1;
}

bool str_includes(const char *str, const char *substring) {
    return strstr(str, substring) != NULL;
}

// Start and End Checks
bool str_startsWith(const char *str, const char *prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) return false;
    }
    return true;
}

bool str_endsWith(const char *str, const char *suffix) {
    int len_str = str_length(str);
    int len_suffix = str_length(suffix);
    if (len_suffix > len_str) return false;
    return strcmp(str + len_str - len_suffix, suffix) == 0;
}

// Case Conversion
void str_toLowerCase(char *str) {
    char *s = str;
    while (*s) {
        *s = tolower(*s);
        s++;
    }
}

void str_toUpperCase(char *str) {
    char *s = str;
    while (*s) {
        *s = toupper(*s);
        s++;
    }
}

// Trimming
void str_trim(char *str) {
    str_trimStart(str);
    str_trimEnd(str);
}

void str_trimStart(char *str) {
    char *s = str;
    while (isspace(*s)) s++;
    memmove(str, s, strlen(s) + 1);
}

void str_trimEnd(char *str) {
    char *end = str + str_length(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = '\0';
}