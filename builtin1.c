#include "shell.h"
#include <stdio.h> // Include necessary headers

int _myexit(info_t *info) {
    if (info->argv[1]) {
        int exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1) {
            info->status = 2;
            fprintf(stderr, "Illegal number: %s\n", info->argv[1]);
        } else {
            info->err_num = exit_status;
            return -2;
        }
    }
    info->err_num = -1;
    return -2;
}

int _mycd(info_t *info) {
    char *new_directory;
    char current_directory[1024];

    if (!info->argv[1] || _strcmp(info->argv[1], "~") == 0) {
        new_directory = _getenv(info, "HOME");
    } else if (_strcmp(info->argv[1], "-") == 0) {
        new_directory = _getenv(info, "OLDPWD");
        if (!new_directory) {
            fprintf(stderr, "OLDPWD not set\n");
            return 1;
        }
    } else {
        new_directory = info->argv[1];
    }

    if (chdir(new_directory) == -1) {
        fprintf(stderr, "cd: can't change to directory %s\n", new_directory);
        return 1;
    }

    getcwd(current_directory, sizeof(current_directory));
    _setenv(info, "OLDPWD", _getenv(info, "PWD"));
    _setenv(info, "PWD", current_directory);
    return 0;
}

int _myhelp(info_t *info) {
    // Add your help message here
    printf("This is a simple shell program. Add your help information here.\n");
    return 0;
}

