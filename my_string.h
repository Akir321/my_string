#ifndef MY_STRING_H
#define MY_STRING_H

#define sizear(str) sizeof(str)/sizeof(str[0])

const int ALPHABET_SIZE = 256;
const int HASH_MOD = 10069;

void printStr(char *str, size_t size);

int myPuts(const char *str);

char *myStrcpy(char *dest, const char *src);

char *myStrchr(char *str, const char symbol);

size_t myStrlen(const char *str);

char *myStrncpy(char *dest, const char *src, const int n);

char *myStrcat(char *to, const char *from);

char *myStrncat(char *to, const char *from, int n);

char *myFgets(char *str, int n, FILE *fstream);

char *myStrdup(const char *str);

size_t myGetline(char **lineptr, size_t *n, FILE *fstream);

int myStrcmp(const char *str1, const char *str2);

int myStrncmp(const char *str1, const char *str2, const size_t n);

char *myStrstr(char *foundIn, const char *found);

char *myStrstrRK(char *foundIn, const char *found);

char *myStrstrBMH(char *text, const char *pattern);

#endif //MY_STRING_H
