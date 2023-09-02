#include <assert.h>
#include <stdio.h>
#include "my_string.h"

// vs code snippets

void printStr(const char *str, size_t size)
{
    assert(str);

    for (size_t i = 0; i < size; i++) {
        printf("%c(%d)", str[i], str[i]);
    }
    putchar('\n');
}

int myPuts(const char *str)
{
    assert(str);

    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
    putchar('\n');
    return i + 1;
}

char* myStrcpy(char *dest, const char *src)
{
    assert(src);
    assert(dest);
    assert(src != dest);

    size_t i = 0;
    do {
        dest[i] = src[i];
    } while (src[i++] != '\0');

    return dest;
}

char* myStrchr(const char *str, char symbol) 
{
    assert(str);

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == symbol) {
            return (char*)(str + i);
        }
        i++;
    }
    return NULL;
}

size_t myStrlen(const char *str)
{
    assert(str);

    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}

char* myStrncpy(char *dest, const char *src, int n)
{
    assert(dest);
    assert(src);
    assert(src != dest);

    int lastSymbol = n - 1;
    int i = 0;
    while (i < lastSymbol && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i++] = '\0';
    }
    
    return dest;
}

char *myStrcat(char *to, const char *from)
{
    assert(to);
    assert(from);
    assert(to != from);

    size_t i = myStrlen(to);
    size_t j = 0;

    while (from[j] != '\0') {
        to[i++] = from[j++];
    }
    to[i] = '\0';
    return to;
}

char *myStrncat(char *to, const char *from, int n)
{
    assert(to);
    assert(from);
    assert(to != from);

    size_t i = myStrlen(to);
    int j = 0;

    while(from[j] != '\0' && j < n) {
        to[i++] = from[j++];
    }
    to[i] = '\0';
    return to;
}

char *myFgets(char *str, int n, FILE *fstream)
{
    assert(str);
    assert(fstream);

    int maxSize = n - 1;
    int i = 0;
    int c = fgetc(fstream);
    while (c != '\n' && c != EOF && i < maxSize) {
        str[i++] = char(c);
        c = fgetc(fstream);
    }
    str[i] = '\0';

    if (i == 0) return NULL;
    return str;
}

char *myStrdup(const char *str)
{
    assert(str);

    size_t size = myStrlen(str);
    char *newStr = (char *)calloc(size + 1, sizeof(char));

    size_t i = 0;
    while (str[i] != '\0') {
        newStr[i] = str[i];
        i++;
    }

    newStr[i] = '\0';
    return newStr;
}

size_t myGetline(char **lineptr, size_t *n, FILE *fstream)
{
    assert(lineptr);
    assert(n);
    assert(fstream);

    size_t i = 0;
    int c = fgetc(fstream);
    while (c != '\n' && c != EOF) {
        if (i >= *n + TERMINATING_SYMBOLS) {
            (*n) *= EXPANSION_RATE;
            *lineptr = (char *)realloc(*lineptr, *n * sizeof(char)); 
            if (*lineptr == NULL) {
                return -1;
            }
        }
        (*lineptr)[i++] = char(c);
        c = fgetc(fstream);
    }

    if (c == '\n') {
        (*lineptr)[i++] = '\n';
    }
    (*lineptr)[i++] = '\0';

    if (i == 0) return -1;

    *n = i;
    *lineptr = (char *)realloc(*lineptr, *n * sizeof(char));
    
    return *n;
}

int myStrcmp(const char *str1, const char *str2)
{
    assert(str1);
    assert(str2);
    assert(str1 != str2);

    size_t i = 0;
    while (str1[i] == str2[i] && str2[i] != '\0') {
        i++;
    }

    return str1[i] - str2[i];
}

int myStrncmp(const char *str1, const char *str2, size_t n)
{
    assert(str1);
    assert(str2);
    assert(str1 != str2);

    size_t comparedLast = n - 1;
    size_t i = 0;

    while (str1[i] == str2[i]  && str2[i] != '\0' && i < comparedLast) {
        i++;
    }

    return str1[i] - str2[i];
}

char *myStrstr(char *text, const char *pattern)
{
    assert(text);
    assert(pattern);
    assert(text != pattern);

    size_t textIter = 0;
    size_t patIter = 0;

    while (text[textIter + patIter] != '\0' && pattern[patIter] != '\0') {
        if (text[textIter + patIter] == pattern[patIter]) {
            patIter++;
        }
        else {
            patIter = 0;
            textIter++;
        }
    }

    if (pattern[patIter] == '\0') {
        return text + textIter;
    }

    return NULL;
}

int getMod(int num, int mod)
{
    return (num % mod + mod) % mod;
}

// TODO: tests
char *myStrstrRK(char *text, const char *pattern) // Rabin-Karp algorithm
{
    assert(text);
    assert(pattern);
    assert(pattern != text);

    int hashStr       = text[0]    % HASH_MOD;
    int hashPattern   = pattern[0] % HASH_MOD;
    int firstElemHash = 1;

    size_t patternLength = 0;

    // TODO: function for hashing
    for (size_t i = 0; pattern[i] != '\0'; i++) {
        hashStr       = (hashStr       * ALPHABET_SIZE + text[i])    % HASH_MOD;
        hashPattern   = (hashPattern   * ALPHABET_SIZE + pattern[i]) % HASH_MOD;
        firstElemHash = (firstElemHash * ALPHABET_SIZE)              % HASH_MOD;
        patternLength++;
    }

    if (patternLength == 0) {
        return text;
    }

    for (size_t i = 0; text[i + patternLength - 1] != '\0'; i++) {

        if (hashStr == hashPattern &&
            myStrncmp(text + i, pattern, patternLength) == 0) {

            return text + i;
        }
        hashStr -= (firstElemHash * text[i]) % HASH_MOD;
        hashStr = getMod(hashStr, HASH_MOD);
        hashStr *= ALPHABET_SIZE;
        hashStr += text[i + patternLength];
        hashStr %= HASH_MOD;
    }

    return NULL;
}

char *myStrstrBMH(char *text, const char *pattern) // Boyer-Moore-Horspool algorithm
{                                                  // only bad-character heuristic used
    assert(text);
    assert(pattern);
    assert(text != pattern);

    if (pattern[0] == '\0')
        return text;

    int lastOcc[ALPHABET_SIZE] = {};
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        lastOcc[i] = -1;
    }

    size_t patternLength = 0;      // it is actually (patternLength - 1)
    for (size_t i = 0; pattern[i + 1] != '\0'; i++) {
        lastOcc[int(pattern[i])] = int(i);
        patternLength++;
    }

    size_t i = 0;
    while (text[i + patternLength] != '\0') {
        int j = int(patternLength);
        while (text[i + j] == pattern[j]) {
            j--;
            if (j == -1) {
                return text + i;
            }
        }

        if (lastOcc[int(text[i + patternLength])] == -1) {
            i += patternLength + 1;
        }
        else {
            i += lastOcc[int(text[i + patternLength])] + 1;
        }
    }
    return NULL;
}

char *myStrtok(char *str, const char *sep)
{
    assert(sep);
    assert(str != sep);

    static char *prevEnd = NULL;

    if (!str) str = prevEnd;
    if (!str) return NULL;

    // comparing the current symbol in str with every symbol in sep
    while (myStrchr(sep, *str)) {
        str++;
    }

    prevEnd = str;

    while (!myStrchr(sep, *prevEnd) && *prevEnd != '\0') {
        prevEnd++;
    }
        
    
    if (*prevEnd == '\0') {
        prevEnd = NULL;
    }
    else {
        *prevEnd++ = '\0';
    }

    return str;
}

// kmp ???????????????????
// prefix function ?????????????
