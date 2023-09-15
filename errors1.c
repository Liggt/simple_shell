#include "shell.h"
#include <stdio.h> // Include necessary headers

#define WRITE_BUF_SIZE 1024 // Define the buffer size
#define BUF_FLUSH '\0'      // Define the buffer flush character

/**
 * _eputs - function that prints an input string to stderr
 * @string: the string that is to be printed
 */
void _eputs(char *string) {
    if (string) {
        fprintf(stderr, "%s", string);
    }
}

/**
 * _eputchar - function that writes the character d to stderr
 * @d: The character to be written
 * 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int _eputchar(char d) {
    return write(2, &d, 1); // Write the character to stderr
}

/**
 * _putfd - function that writes the character d to a file descriptor
 * @d: The character to be written
 * @fd: The file descriptor to write to
 * 
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int _putfd(char d, int fd) {
    return write(fd, &d, 1); // Write the character to the specified file descriptor
}

/**
 * _putsfd - function that prints an input string to a file descriptor
 * @string: the string to print
 * @fd: the file descriptor to write to
 * 
 * Return: the number of characters written
 */
int _putsfd(char *string, int fd) {
    if (!string) {
        return 0;
    }
    
    int count = 0;
    while (*string) {
        count += _putfd(*string++, fd); // Write each character to the file descriptor
    }
    return count; // Return the total number of characters written
}

