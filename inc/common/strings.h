#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stddef.h>

void *memset(void *s, int c, size_t n);
void *memcpy(void *dst, void *src, size_t n);
int strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
unsigned int strtonum(const char *str, const char **endptr);
char *reverse_str(char *str, size_t len);
char *numtostr(unsigned int num, char *str, size_t *len);
int strlcat(char *dst, const char *src, int maxsize);

#endif