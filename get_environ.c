#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * get_environ - function that returns a copy of the environment variables as a string array
 * @info: Structure that holds potential arguments. Maintain constant function prototype.
 * Return: A string array containing environment variables.
 */
char **get_environ(info_t *info) {
    if (!info->environ || info->env_changed) {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * _unsetenv - function that removes environment variables
 * @info: Structure that holds arguments. Maintain constant function prototype.
 * @var: The name of the environment variable to remove.
 * Return: 1 if the variable is removed, 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var) {
    if (!info->env || !var)
        return 0;

    int removed = 0;
    size_t index = 0;
    char *q;
    list_t *node = info->env;

    while (node) {
        q = starts_with(node->str, var);
        if (q && *q == '=') {
            info->env_changed = delete_node_at_index(&(info->env), index);
            removed = 1;
            node = info->env; // Restart from the beginning of the list
            continue;
        }
        node = node->next;
        index++;
    }

    return removed;
}

/**
 * _setenv - function that initializes a new environment variable or modifies an existing one
 * @info: Structure that holds arguments. Maintain constant function prototype.
 * @var: The name of the environment variable.
 * @value: The value of the environment variable.
 * Return: 0 on success, 1 on memory allocation failure.
 */
int _setenv(info_t *info, const char *var, const char *value) {
    if (!var || !value)
        return 0;

    char *buff;
    list_t *node;
    char *q;

    buff = malloc(strlen(var) + strlen(value) + 2);
    if (!buff)
        return 1;

    sprintf(buff, "%s=%s", var, value);
    node = info->env;

    while (node) {
        q = starts_with(node->str, var);
        if (q && *q == '=') {
            free(node->str);
            node->str = strdup(buff);
            free(buff);
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buff, 0);
    free(buff);
    info->env_changed = 1;
    return 0;
}

