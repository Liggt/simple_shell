#include "shell.h"

/**
 * split_string - Split a string into words using specified delimiters
 * @str: The input string
 * @delimiters: The delimiter characters
 *
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **split_string(char *str, char *delimiters) {
    int i, j, k, numWords = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!delimiters)
        delimiters = " ";

    for (i = 0; str[i] != '\0'; i++) {
        if (!is_delimiter(str[i], delimiters) && (is_delimiter(str[i + 1], delimiters) || str[i + 1] == '\0'))
            numWords++;
    }

    if (numWords == 0)
        return NULL;

    words = malloc((numWords + 1) * sizeof(char *));
    if (!words)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++) {
        while (is_delimiter(str[i], delimiters))
            i++;

        k = 0;
        while (!is_delimiter(str[i + k], delimiters) && str[i + k])
            k++;

        words[j] = malloc((k + 1) * sizeof(char));
        if (!words[j]) {
            for (k = 0; k < j; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (int l = 0; l < k; l++)
            words[j][l] = str[i++];
        words[j][k] = '\0';
    }

    words[numWords] = NULL;
    return words;
}

/**
 * split_string2 - Split a string into words using a single delimiter character
 * @str: The input string
 * @delimiter: The delimiter character
 *
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **split_string2(char *str, char delimiter) {
    int i, j, k, numWords = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return NULL;

    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] != delimiter && str[i + 1] == delimiter) ||
            (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
            numWords++;
    }

    if (numWords == 0)
        return NULL;

    words = malloc((numWords + 1) * sizeof(char *));
    if (!words)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++) {
        while (str[i] == delimiter && str[i] != '\0')
            i++;

        k = 0;
        while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
            k++;

        words[j] = malloc((k + 1) * sizeof(char));
        if (!words[j]) {
            for (k = 0; k < j; k++)
                free(words[k]);
            free(words);
            return NULL;
        }

        for (int l = 0; l < k; l++)
            words[j][l] = str[i++];
        words[j][k] = '\0';
    }

    words[numWords] = NULL;
    return words;
}

