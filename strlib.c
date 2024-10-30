#include "strlib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // For printf debugging

// Helper functions to determine UTF-8 byte properties
int is_ascii_byte(uint8_t byte) {
    return byte <= 0x7F;
}

int utf8_sequence_length(uint8_t first_byte) {
    if (is_ascii_byte(first_byte)) return 1;
    if ((first_byte & 0xE0) == 0xC0) return 2;
    if ((first_byte & 0xF0) == 0xE0) return 3;
    if ((first_byte & 0xF8) == 0xF0) return 4;
    return 0;
}

// Construct a String from a given UTF-8 encoded char array
String str_construct(const char *str) {
    String new_string;
    new_string.byte_length = strlen(str);
    new_string.utf8 = malloc((new_string.byte_length + 1) * sizeof(char));
    if (new_string.utf8 != NULL) {
        strcpy(new_string.utf8, str);
    }

    // Calculate the length in code points
    size_t codepoints = 0;
    const unsigned char *ptr = (const unsigned char *)str;
    while (*ptr) {
        ptr += utf8_sequence_length(*ptr);
        codepoints++;
    }
    new_string.codepoint_length = codepoints;

    return new_string;
}

// Destruct a String and free memory
void str_destruct(String string) {
    if (string.utf8 != NULL) {
        free(string.utf8);
        string.utf8 = NULL;
    }
}

// Return a NUL-terminated char array from a String
char *str_valueOf(String string) {
    if (string.utf8[string.byte_length] == '\0') {
        return string.utf8;
    }

    char *real_str = malloc((string.byte_length + 1) * sizeof(char));
    if (real_str != NULL) {
        strncpy(real_str, string.utf8, string.byte_length);
        real_str[string.byte_length] = '\0';
    }
    return real_str;
}

// Return the length in code points of a String
size_t str_length(String string) {
    return string.codepoint_length;
}

// Return the code point at a specific index
int32_t str_codePointAt(const String string, int index) {
    const unsigned char *ptr = (const unsigned char *)(string.utf8);
    int current_index = 0;
    while (*ptr && current_index < index) {
        ptr += utf8_sequence_length(*ptr);
        current_index++;
    }
    if (current_index == index && *ptr) {
        int seq_len = utf8_sequence_length(*ptr);
        int32_t code_point = 0;
        if (seq_len == 1) {
            code_point = *ptr;
        } else {
            code_point = (*ptr & (0xFF >> (seq_len + 1)));
            for (int i = 1; i < seq_len; i++) {
                ptr++;
                code_point = (code_point << 6) | (*ptr & 0x3F);
            }
        }
        return code_point;
    }
    return -1; // Index out of range
}

// Concatenate two Strings
String str_concat(const String str1, const String str2) {
    size_t new_byte_length = str1.byte_length + str2.byte_length;
    char *new_utf8 = malloc((new_byte_length + 1) * sizeof(char));
    if (new_utf8 == NULL) {
        return (String){ NULL, 0, 0 }; // Return an empty String if allocation fails
    }

    strcpy(new_utf8, str1.utf8);
    strcat(new_utf8, str2.utf8);

    return str_construct(new_utf8);
}

// Slice a part of the String
String str_slice(const String string, int start, int end) {
    if (start < 0 || end >= string.codepoint_length || start > end) {
        return (String){ NULL, 0, 0 }; // Return an empty String if range is invalid
    }

    const unsigned char *ptr = (const unsigned char *)string.utf8;
    const unsigned char *substring_start = NULL;
    const unsigned char *substring_end = NULL;
    int current_index = 0;

    while (*ptr) {
        if (current_index == start) {
            substring_start = ptr;
        }
        if (current_index == end + 1) {
            substring_end = ptr;
            break;
        }
        ptr += utf8_sequence_length(*ptr);
        current_index++;
    }
    
    if (substring_end == NULL) {
        substring_end = ptr;
    }

    size_t slice_length = substring_end - substring_start;
    char *new_utf8 = malloc((slice_length + 1) * sizeof(char));
    if (new_utf8 != NULL) {
        strncpy(new_utf8, (const char *)substring_start, slice_length);
        new_utf8[slice_length] = '\0';
    }
    
    return str_construct(new_utf8);
}

// Check if the String starts with a certain prefix
bool str_startsWith(const String string, const String prefix) {
    if (prefix.byte_length > string.byte_length) return false;
    return strncmp(string.utf8, prefix.utf8, prefix.byte_length) == 0;
}

// Check if the String ends with a certain suffix
bool str_endsWith(const String string, const String suffix) {
    if (suffix.byte_length > string.byte_length) return false;
    return strcmp(string.utf8 + string.byte_length - suffix.byte_length, suffix.utf8) == 0;
}

// Other functions such as `str_indexOf`, `str_includes`, `str_toLowerCase`, `str_toUpperCase`, `str_trim`, etc.,
// would be similarly adjusted to operate on `String` structs and deal with UTF-8 encoding and memory management.