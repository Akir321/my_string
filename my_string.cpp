#include <assert.h>
#include <stdio.h>
#include "my_string.h"

// vs code snippets

void printStr(char *str, size_t size)
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

    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
    putchar('\n');
    return 1;
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

char* myStrchr(char *str, char symbol) // const char*
{
    assert(str);

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == symbol){
            return str + i;
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

char* myStrncpy(char *dest, const char *src, const int n)
{
    assert (dest);
    assert(src);
    assert(src != dest);

    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
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

ssize_t myGetline(char **lineptr, size_t *n, FILE *fstream)
{
    assert(lineptr);
    assert(n);
    assert(fstream);

    size_t i = 0;
    int c = fgetc(fstream);
    while (c != '\n' && c != EOF) {
        if (i == *n) {
            (*n)++;
            *lineptr = (char *)realloc(*lineptr, *n * sizeof(char));
        }
        (*lineptr)[i] = char(c);
        i++;
        c = fgetc(fstream);
    }

    if (c == '\n') {
        if (*n <= i + 1) {
            *n = i + 2;
            *lineptr = (char *)realloc(*lineptr, *n * sizeof(char));
        }
        (*lineptr)[i++] = '\n';
    }
    else if (*n <= i) {
        (*n) = i + 1;
        *lineptr = (char *)realloc(*lineptr, *n * sizeof(char));
    }
    (*lineptr)[i] = '\0';

    if (i == 0) return -1;
    return *n;
}

int myStrcmp(const char *str1, const char *str2)
{
    assert(str1);
    assert(str2);
    assert(str1 != str2);

    size_t i = 0;
    while (str2[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }

    return str1[i] - str2[i];
}

int myStrncmp(const char *str1, const char *str2, const size_t n)
{
    assert(str1);
    assert(str2);
    assert(str1 != str2);

    size_t seenLast = n - 1;
    size_t i = 0;

    while (str2[i] != '\0' && str1[i] == str2[i] && i < seenLast) {
        i++;
    }

    return str1[i] - str2[i];
}

char *myStrstr(char *foundIn, const char *found) //const char
{
    assert(foundIn);
    assert(found);
    assert(foundIn != found);

    size_t i = 0;
    size_t j = 0;

    while (foundIn[i + j] != '\0' && found[j] != '\0') {

        if (foundIn[i + j] == found[j]) {
            j++;
        }
        else {
            j = 0;
            i++;
        }
    }

    if (found[j] == '\0')
        return foundIn + i;

    return NULL;
}

char *myStrstrRK(char *foundIn, const char *found) // Rabin-Karp algorithm
{
    assert(foundIn);
    assert(found);
    assert(found != foundIn);

    int hashStr  =  foundIn[0] % HASH_MOD;
    int hashPattern = found[0] % HASH_MOD;
    int firstElemHash = 1;

    size_t patternLength = 0;

    for (size_t i = 0; found[i] != '\0'; i++) {
        hashStr   =   (hashStr   *   ALPHABET_SIZE + foundIn[i]) % HASH_MOD;
        hashPattern = (hashPattern * ALPHABET_SIZE  +  found[i]) % HASH_MOD;
        firstElemHash     =    (firstElemHash  *  ALPHABET_SIZE) % HASH_MOD;
        patternLength++;
    }

    if (patternLength == 0)
        return foundIn;

    for (size_t i = 0; foundIn[i + patternLength - 1] != '\0'; i++) {

        if (hashStr == hashPattern &&
            myStrncmp(foundIn + i, found, patternLength) == 0) {

            return foundIn + i;
        }
        hashStr -= (firstElemHash * foundIn[i]) % HASH_MOD;
        hashStr += HASH_MOD;
        hashStr *= ALPHABET_SIZE;
        hashStr += foundIn[i + patternLength];
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

    int lastOcc[ALPHABET_SIZE];
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
