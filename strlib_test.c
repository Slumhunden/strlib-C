#include <stdio.h>
#include "strlib.h"

void test_construct_and_destruct() {
    printf("Test: Construct and Destruct\n");
    String s = str_construct("Hello, UTF-8 🌍");
    if (s.utf8 != NULL) {
        printf("Constructed: '%s'\n", str_valueOf(s));
    }
    str_destruct(s);
}

void test_str_length() {
    printf("\nTest: String Length\n");
    String s = str_construct("Hello, UTF-8 🌍");
    printf("Expected codepoint length: 12, Got: %zu\n", str_length(s));
    str_destruct(s);
}

void test_str_codePointAt() {
    printf("\nTest: String Code Point At\n");
    String s = str_construct("Hello, UTF-8 🌍");
    printf("Expected code point at index 7 ('U'): 85, Got: %d\n", str_codePointAt(s, 7));
    printf("Expected code point at index 11 ('🌍'): 127757, Got: %d\n", str_codePointAt(s, 11));
    str_destruct(s);
}

void test_str_concat() {
    printf("\nTest: String Concat\n");
    String s1 = str_construct("Hello, ");
    String s2 = str_construct("world!");
    String result = str_concat(s1, s2);
    printf("Expected concatenated: 'Hello, world!', Got: '%s'\n", str_valueOf(result));
    str_destruct(s1);
    str_destruct(s2);
    str_destruct(result);
}

void test_str_slice() {
    printf("\nTest: String Slice\n");
    String s = str_construct("Hello, UTF-8 🌍");
    String slice = str_slice(s, 7, 11);
    printf("Expected slice: 'UTF-8', Got: '%s'\n", str_valueOf(slice));
    str_destruct(s);
    str_destruct(slice);
}

void test_str_startsWith() {
    printf("\nTest: StartsWith\n");
    String s = str_construct("Hello, UTF-8 🌍");
    String prefix = str_construct("Hello");
    printf("Expected startsWith: 1, Got: %d\n", str_startsWith(s, prefix));
    str_destruct(s);
    str_destruct(prefix);
}

void test_str_endsWith() {
    printf("\nTest: EndsWith\n");
    String s = str_construct("Hello, UTF-8 🌍");
    String suffix = str_construct("🌍");
    printf("Expected endsWith: 1, Got: %d\n", str_endsWith(s, suffix));
    str_destruct(s);
    str_destruct(suffix);
}

int main() {
    test_construct_and_destruct();
    test_str_length();
    test_str_codePointAt();
    test_str_concat();
    test_str_slice();
    test_str_startsWith();
    test_str_endsWith();
    return 0;
}