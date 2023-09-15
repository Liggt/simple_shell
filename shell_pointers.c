#include "shell.h"

/**
 * is_executable - Check if a file is executable
 * @info: Pointer to the shell information structure
 * @path: Path to the file
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(info_t *info, char *path) {
    struct stat file_stat;

    (void)info;

    if (!path || stat(path, &file_stat) != 0) {
        return 0;
    }

    if (file_stat.st_mode & S_IXUSR) {
        return 1;
    }

    return 0;
}

/**
 * duplicate_chars - Duplicate a range of characters from a string
 * @str: The input string
 * @start: Starting index of the range
 * @end: Ending index of the range
 *
 * Return: Pointer to the duplicated substring
 */
char *duplicate_chars(const char *str, int start, int end) {
    static char buf[1024];
    int index = 0;

    for (int i = start; i < end; i++) {
        if (str[i] != ':') {
            buf[index++] = str[i];
        }
    }

    buf[index] = '\0';
    return buf;
}

/**
 * find_command_path - Find the full path of a command in the PATH variable
 * @info: Pointer to the shell information structure
 * @pathstr: The PATH variable string
 * @cmd: The command to find
 *
 * Return: Full path of the command or NULL if not found
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd) {
    int start = 0;
    char *path;

    if (!pathstr) {
        return NULL;
    }

    if (_strlen(cmd) > 2 && starts_with(cmd, "./")) {
        if (is_executable(info, cmd)) {
            return cmd;
        }
    }

    for (int t = 0; pathstr[t]; t++) {
        if (pathstr[t] == ':') {
            path = duplicate_chars(pathstr, start, t);
            if (!*path) {
                _strcat(path, cmd);
            } else {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_executable(info, path)) {
                return path;
            }

            if (!pathstr[t]) {
                break;
            }

            start = t + 1;
        }
    }

    return NULL;
}

