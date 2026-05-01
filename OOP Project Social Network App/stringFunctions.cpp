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

char* join(const char* s1, const char* s2) {
    if (s1 == nullptr && s2 == nullptr) return nullptr;
    if (s1 == nullptr) {
        int len2 = getLength(s2);
        char* res = new char[len2 + 1];
        copyString(res, s2);
        return res;
    }
    if (s2 == nullptr) {
        int len1 = getLength(s1);
        char* res = new char[len1 + 1];
        copyString(res, s1);
        return res;
    }

    int len1 = getLength(s1);
    int len2 = getLength(s2);

    // Allocate new memory for combined length + null terminator
    char* result = new char[len1 + len2 + 1];

    // Copy first string
    int i = 0;
    for (; i < len1; i++) {
        result[i] = s1[i];
    }

    // Copy second string starting where first one ended
    for (int j = 0; j < len2; j++, i++) {
        result[i] = s2[j];
    }

    result[i] = '\0'; // Add the null terminator
    return result;
}

const char* convertIntToChar(int num) {
    int length = 0;
    int copy_num = num;
    while (copy_num) {
        length++;
        copy_num /= 10;
    }
    copy_num = num;
    char* charOutput = new char[length + 1];
    int write_idx = length - 1;
    while (copy_num && write_idx >= 0) {
        int temp = copy_num % 10;
        copy_num /= 10;
        charOutput[write_idx--] = (temp + '0');
    }
    charOutput[length] = '\0';

    return charOutput;
}

// Appends `src` to the end of `dest`. Assumes `dest` has enough space.
void concatStr(char* dest, const char* src) {
	if (!dest || !src) return;
	int destLen = getLength(dest);
	int srcLen = getLength(src);
	for (int i = 0; i <= srcLen; ++i) { // copy including terminating '\0'
		dest[destLen + i] = src[i];
	}
}