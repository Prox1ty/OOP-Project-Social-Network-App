#include "stringFunctions.h"

int getLength(const char* str) {
    if (str == nullptr) return 0;
    
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

void copyString(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr) return;

    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool areEqual(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    // they are equal only if both reached the null terminator at the same time
    return s1[i] == s2[i];
}