#include "shell.h"

/**
 * string_copy - Copy a string from source to destination
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to the destination buffer
 */
char *string_copy(char *dest, const char *src) {
    int index = 0;

    if (dest == src || src == NULL)
        return dest;

    while (src[index]) {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

/**
 * string_duplicate - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string or NULL on failure
 */
char *string_duplicate(const char *str) {
    int length = 0;
    char *ret;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return NULL;

    for (length++; length--;) {
        ret[length] = *--str;
    }

    return ret;
}

/**
 * string_print - Print a string to stdout
 * @str: The string to print
 *
 * Return: Nothing
 */
void string_print(const char *str) {
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0') {
        character_print(str[index]);
        index++;
    }
}

/**
 * character_print - Write a character to stdout
 * @c: The character to print
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int character_print(char c) {
    static int buffer_index;
    static char output_buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE) {
        write(1, output_buffer, buffer_index);
        buffer_index = 0;
    }

    if (c != BUF_FLUSH) {
        output_buffer[buffer_index++] = c;
    }

    return 1;
}

