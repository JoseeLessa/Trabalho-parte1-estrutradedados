#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static inline void str_trim(char *s) {
    if (!s) return;
    
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    
    if (*start == '\0') {
        *s = '\0';
        return;
    }
    
    char *end = s + strlen(s) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    size_t len = end - start + 1;
    if (start != s) memmove(s, start, len);
    s[len] = '\0';
}

static inline int safe_atoi(const char *str, int *out) {
    if (!str || !out) return 0;
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') return 0;
    *out = (int)val;
    return 1;
}

static inline int str_starts_with_case_insensitive(const char *str, const char *prefix) {
    if (!str || !prefix) return 0;
    while (*prefix) {
        if (tolower((unsigned char)*str) != tolower((unsigned char)*prefix))
            return 0;
        str++;
        prefix++;
    }
    return 1;
}

static inline void print_utf8_padded(const char *text, int width) {
    int len = strlen(text);
    printf("%s", text);
    for (int i = len; i < width; i++) printf(" ");
}

#endif
