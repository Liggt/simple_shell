#include "shell.h"

/**
 * string_length - Calculate the length of a string
 * @str: The input string
 *
 * Return: The length of the string
 */
int string_length(const char *str) {
    int length = 0;

    if (!str)
        return 0;

    while (*str++) {
        length++;
    }

    return length;
}

/**
 * starts_with - Check if a string starts with a prefix
 * @str: The string to search in
 * @prefix: The prefix to check
 *
 * Return: A pointer to the first character after the prefix in 'str', or NULL if not found
 */
char *starts_with(const char *str, const char *prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) {
            return NULL;
        }
    }
    return (char *)str;
}

/**
 * string_concatenate - Concatenate two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: A pointer to the destination buffer
 */
char *string_concatenate(char *dest, const char *src) {
    char *result = dest;

    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = *src;

    return result;
}

/**
 * string_compare - Compare two strings
 * @str1: The first string
 * @str2: The second string
 *
 * Return: 0 if the strings are equal, a positive value if str1 > str2, a negative value if str1 < str2
 */
int string_compare(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }

    if (*str1 == *str2) {
        return 0;
    } else {
        return (*str1 < *str2 ? -1 : 1);
    }
}

