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
    unsigned int base = 10;
    unsigned int rv = 0;
    const char *str_ptr = str;
    
    // if str starts with 0x, then base 16. otherwise, base 10. 
    if (0 == strncmp(str, "0x", 2)) {
        base = 16;
        str_ptr += 2;
    }

    int len = strlen(str_ptr);
    int new_digit = 0;
    char new_char = 0;
    // since we're going left to right, we can multiply the existing value by 10
    // and add the new digit to the new ones place 
    while (len--) {
        new_char = *str_ptr++;
        if (new_char > '0' && new_char < '9') {
            new_digit = new_char - '0';
        } else if (new_char >= 'A' && new_char <= 'F' && base == 16) {
            new_digit = 10 + new_char - 'A';
        } else {
            // if it's not a valid digit for this base, then break out and return
            break;
        }
        rv = (rv * base)  + new_digit;
    }

    *endptr = str_ptr;
    return rv;
}

// reverses a string - used for numtostr
char *reverse_str(char *str, size_t len) {
    int start = 0;
    int end = len - 1;
    char temp = 0;
    while (start < end) {
        temp = *(str + start);
        *(str + start) = *(str + end);
        *(str + end) = temp;
        ++start;
        --end;
    }
    return str;
}

// transforms int i into string so that it can be printed more easily
char *numtostr(unsigned int num, char *str, size_t *len) {
    if (NULL == len) {
        return NULL;
    }

    int remainder = 0;
    int i = 0;
    while (num) {
        remainder = num % 10;
        *(str + i++) = remainder + '0';
        num = num / 10; 
    }
    *(str + i) = '\0';
    *len = i - 1;
    return reverse_str(str, i);
}

int strlcat(char *dst, const char *src, int maxsize) {
    return 0;
}