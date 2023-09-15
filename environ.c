#include "shell.h"
#include <stdio.h> // Include necessary headers

int _myenv(info_t *info) {
    // Print the current environment variables
    print_list_str(info->env);
    return 0;
}

char *_getenv(info_t *info, const char *nm) {
    // Search for the specified environment variable
    list_t *node = info->env;
    while (node) {
        if (starts_with(node->str, nm)) {
            return node->str;
        }
        node = node->next;
    }
    return NULL; // Return NULL if the variable is not found
}

int _mysetenv(info_t *info) {
    if (info->argc != 3) {
        fprintf(stderr, "Usage: %s <variable> <value>\n", info->argv[0]);
        return 1;
    }

    // Set the environment variable
    if (_setenv(info, info->argv[1], info->argv[2]) == 0) {
        return 0;
    } else {
        fprintf(stderr, "Error setting environment variable %s\n", info->argv[1]);
        return 1;
    }
}

int _myunsetenv(info_t *info) {
    if (info->argc == 1) {
        fprintf(stderr, "Usage: %s <variable> ...\n", info->argv[0]);
        return 1;
    }

    // Unset the specified environment variables
    for (int j = 1; j < info->argc; j++) {
        if (_unsetenv(info, info->argv[j]) != 0) {
            fprintf(stderr, "Error unsetting environment variable %s\n", info->argv[j]);
        }
    }
    return 0;
}

int populate_env_list(info_t *info) {
    // Populate the environment linked list from the system's environment
    for (int j = 0; environ[j]; j++) {
        add_node_end(&(info->env), environ[j], 0);
    }
    return 0;
}

