#include "shell.h"
#include <stdio.h> // Include necessary headers

int _myhistory(info_t *info) {
    // Use the provided print_list function to display the history list
    print_list(info->history);
    return 0;
}

int unset_alias(info_t *info, char *str) {
    // Search for an alias starting with the provided string
    char *equals_sign = _strchr(str, '=');

    if (equals_sign) {
        // Temporarily null-terminate the string to isolate the alias name
        *equals_sign = '\0';
        int result = delete_node_starts_with(&(info->alias), str);
        // Restore the original string
        *equals_sign = '=';
        return result;
    }
    return 1; // Return 1 on error
}

int set_alias(info_t *info, char *str1) {
    // Search for an equals sign in the string
    char *equals_sign = _strchr(str1, '=');

    if (equals_sign) {
        // Temporarily null-terminate the string to isolate the alias name
        *equals_sign = '\0';
        unset_alias(info, str1); // Remove the alias if it already exists
        // Restore the original string
        *equals_sign = '=';
        return add_node_end(&(info->alias), str1, 0) == NULL ? 0 : 1;
    }
    return 1; // Return 1 on error
}

int print_alias(list_t *node1) {
    if (node1) {
        // Extract and print the alias in the specified format
        char *equals_sign = _strchr(node1->str, '=');
        if (equals_sign) {
            printf("%.*s'%s'\n", (int)(equals_sign - node1->str), node1->str, equals_sign + 1);
            return 0;
        }
    }
    return 1; // Return 1 on error
}

int _myalias(info_t *info) {
    int j = 0;
    char *equals_sign = NULL;

    if (info->argc == 1) {
        // Print all aliases
        list_t *node2 = info->alias;
        while (node2) {
            print_alias(node2);
            node2 = node2->next;
        }
        return 0;
    }

    for (j = 1; info->argv[j]; j++) {
        equals_sign = _strchr(info->argv[j], '=');
        if (equals_sign) {
            // Set an alias
            set_alias(info, info->argv[j]);
        } else {
            // Print an alias matching the provided string
            print_alias(node_starts_with(info->alias, info->argv[j], '='));
        }
    }

    return 0;
}

