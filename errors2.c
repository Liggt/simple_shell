#include "shell.h"
#include <stdio.h> // Include necessary headers
#include <stdlib.h> // Include necessary headers for atoi and itoa
#include <limits.h> // Include necessary headers for INT_MAX

#define WRITE_BUF_SIZE 1024 // Define the buffer size
#define BUF_FLUSH '\0'      // Define the buffer flush character

/**
 * _erratoi - function that converts a string to an integer
 * @str: the string to be converted
 * Return: The converted integer if successful, -1 on error
 */
int _erratoi(char *str) {
    if (str == NULL)
        return -1;

    int sign = 1;
    unsigned long int result = 0;

    if (*str == '+')
        str++; // Skip leading '+' sign
    else if (*str == '-') {
        sign = -1;
        str++; // Skip leading '-' sign
    }

    for (int j = 0; str[j] != '\0'; j++) {
        if (str[j] >= '0' && str[j] <= '9') {
            result *= 10;
            result += (str[j] - '0');
            if (result > INT_MAX)
                return -1;
        } else {
            return -1; // Non-numeric character encountered
        }
    }

    return (int)(sign * result);
}

/**
 * print_error - function that prints an error message to stderr
 * @info: parameter info struct
 * @est: string containing error
 */
void print_error(info_t *info, char *est) {
    fprintf(stderr, "%s: %d: %s: %s", info->fname, info->line_count, info->argv[0], est);
}

/**
 * print_d - function that prints a decimal number (base 10) to a file descriptor
 * @inp: input value
 * @fd: file descriptor to write to
 * Return: The number of characters printed
 */
int print_d(int inp, int fd) {
    if (fd == STDERR_FILENO) {
        return fprintf(stderr, "%d", inp);
    } else {
        return fprintf(stdout, "%d", inp);
    }
}

/**
 * convert_number - function that converts a number to a string
 * @nm: the number
 * @base: the base
 * @flag: the argument flags
 * Return: The string representation of the number
 */
char *convert_number(long int nm, int base, int flag) {
    static char buffer[50];
    char sign = 0;
    char *pt = &buffer[49];

    if (!(flag & CONVERT_UNSIGNED) && nm < 0) {
        nm = -nm;
        sign = '-';
    }

    if (base < 2 || base > 16)
        return NULL;

    *pt = '\0';

    do {
        *--pt = (flag & CONVERT_LOWERCASE) ? "0123456789abcdef"[nm % base] : "0123456789ABCDEF"[nm % base];
        nm /= base;
    } while (nm != 0);

    if (sign)
        *--pt = sign;

    return pt;
}

/**
 * remove_comments - function that replaces the first instance of '#' with null
 * @buff: address of the string that will be modified
 */
void remove_comments(char *buff) {
    if (buff == NULL)
        return;

    for (int j = 0; buff[j] != '\0'; j++) {
        if (buff[j] == '#' && (j == 0 || buff[j - 1] == ' ')) {
            buff[j] = '\0';
            break;
        }
    }
}

