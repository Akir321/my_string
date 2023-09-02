#ifndef MY_STRING_H
#define MY_STRING_H

#define sizear(str) sizeof(str)/sizeof(str[0])

const int ALPHABET_SIZE = 256;
const int HASH_MOD = 10069;
const int EXPANSION_RATE = 2;
const int TERMINATING_SYMBOLS = 2;

void printStr(const char *str, size_t size);

int myPuts(const char *str);

char *myStrcpy(char *dest, const char *src);

char *myStrchr(const char *str, char symbol);

size_t myStrlen(const char *str);

char *myStrncpy(char *dest, const char *src, int n);

char *myStrcat(char *to, const char *from);

char *myStrncat(char *to, const char *from, int n);

char *myFgets(char *str, int n, FILE *fstream);

char *myStrdup(const char *str);

size_t myGetline(char **lineptr, size_t *n, FILE *fstream);

int myStrcmp(const char *str1, const char *str2);

int myStrncmp(const char *str1, const char *str2, size_t n);

char *myStrstr(char *foundIn, const char *found);

char *myStrstrRK(char *foundIn, const char *found);

char *myStrstrBMH(char *text, const char *pattern);

char *myStrtok(char *str, const char *sep);

int getMod(int num, int mod);

#endif //MY_STRING_H
