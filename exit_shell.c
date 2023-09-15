#include "shell.h"
#include <string.h> // Include necessary header for string functions

/**
 * _strncpy - function that copies a string up to a specified number of characters
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to copy
 * Return: pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n) {
    char *original_dest = dest;

    while (*src && n > 0) {
        *dest++ = *src++;
        n--;
    }

    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return original_dest;
}

/**
 * _strncat - function that concatenates two strings up to a specified number of characters
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to concatenate
 * Return: pointer to the destination string
 */
char *_strncat(char *dest, const char *src, size_t n) {
    char *original_dest = dest;

    while (*dest)
        dest++;

    while (*src && n > 0) {
        *dest++ = *src++;
        n--;
    }

    *dest = '\0';

    return original_dest;
}

/**
 * _strchr - function that locates a character in a string
 * @str: the string to search
 * @c: the character to find
 * Return: pointer to the first occurrence of the character in the string, or NULL if not found
 */
char *_strchr(const char *str, int c) {
    while (*str) {
        if (*str == c)
            return (char *)str;
        str++;
    }

    return NULL;
}

