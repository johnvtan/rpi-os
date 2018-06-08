#include <stddef.h>
#include <common/strings.h>

// sets n bytes of value c to s
void *memset(void *s, int c, size_t n) {
    if (0 == n || NULL == s) {
        return NULL;
    }
    unsigned char *rv = (unsigned char *)s;
    while (n--) {
        *(unsigned char *)s++ = (unsigned char) c;
    }
    return rv;
}

// copy n bytes of src into dst
void *memcpy(void *dst, void *src, size_t n) {
    if (NULL == dst || NULL == src || 0 == n) {
        return NULL;
    }
    void *rv = dst;
    while (n--) {
        *(unsigned char *)dst++ = *(unsigned char *)src++;
    }
    return rv;
}

// find the length of string s (not including \0)
int strlen(const char *s) {
    if (NULL == s) {
        return -1;
    }
    int count = 0;
    while (*s++ != '\0') {
        count++;
    }
    return count;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (0 == n) {
        return 0;
    } else {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

unsigned int strtonum(const char *str, const char **endptr) {
    if (NULL == str) {
        return -1;
    }
    return 0;
}

int strlcat(char *dst, const char *src, int maxsize) {
    return 0;
}