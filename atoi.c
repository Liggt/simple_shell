#include "shell.h"
#include <ctype.h> // Include the header for isatty

int interactive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int is_delim(char d, char *delim) {
    while (*delim) {
        if (*delim++ == d) {
            return 1;
        }
    }
    return 0;
}

int _isalpha(int d) {
    return isalpha(d); // Use the standard library isalpha function
}

int _atoi(char *z) {
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; z[i] != '\0' && flag != 2; i++) {
        if (z[i] == '-') {
            sign *= -1;
        }

        if (isdigit(z[i])) { // Use isdigit to check for digits
            flag = 1;
            result *= 10;
            result += (z[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    if (sign == -1) {
        output = -result;
    } else {
        output = result;
    }

    return output;
}
