#include "shell.h"

/**
 * main_shell_loop - Main shell loop function
 * @info: Pointer to the shell information structure
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or NULL
 */
int main_shell_loop(ShellInfo *info, char **av) {
    ssize_t read_result = 0;
    int builtin_ret = 0;

    while (read_result != -1 && builtin_ret != -2) {
        clear_shell_info(info);
        if (interactive(info)) {
            print_string("$ ");
        }
        flush_buffer();
        read_result = get_input(info);
        if (read_result != -1) {
            set_shell_info(info, av);
            builtin_ret = find_builtin_command(info);
            if (builtin_ret == -1) {
                find_command(info);
            }
        } else if (interactive(info)) {
            print_character('\n');
        }
        free_shell_info(info, 0);
    }

    write_shell_history(info);
    free_shell_info(info, 1);

    if (!interactive(info) && info->status) {
        exit(info->status);
    }

    if (builtin_ret == -2) {
        if (info->err_num == -1) {
            exit(info->status);
        }
        exit(info->err_num);
    }

    return builtin_ret;
}

/**
 * find_builtin_command - Find a built-in command and execute it
 * @info: Pointer to the shell information structure
 *
 * Return: -1 if built-in is not found, 0 if built-in executed successfully,
 *         1 if built-in found but not successful, -2 if built-in signals exit()
 */
int find_builtin_command(ShellInfo *info) {
    int idx, builtin_ret = -1;
    BuiltinCommand builtin_table[] = {
        {"exit", exit_shell},
        {"env", display_environment},
        {"help", display_help},
        {"history", display_history},
        {"setenv", set_environment_variable},
        {"unsetenv", unset_environment_variable},
        {"cd", change_directory},
        {"alias", display_alias},
        {NULL, NULL}
    };

    for (idx = 0; builtin_table[idx].type; idx++) {
        if (string_compare(info->argv[0], builtin_table[idx].type) == 0) {
            info->line_count++;
            builtin_ret = builtin_table[idx].func(info);
            break;
        }
    }

    return builtin_ret;
}

/**
 * find_command - Find and execute an external command
 * @info: Pointer to the shell information structure
 */
void find_command(ShellInfo *info) {
    char *path = NULL;

    info->path = info->argv[0];

    if (info->linecount_flag == 1) {
        info->line_count++;
        info->linecount_flag = 0;
    }

    int arg_count = 0;
    for (int idx = 0; info->arg[idx]; idx++) {
        if (!is_delimiter(info->arg[idx], " \t\n")) {
            arg_count++;
        }
    }

    if (arg_count == 0) {
        return;
    }

    path = find_path(info, getenv_variable(info, "PATH="), info->argv[0]);

    if (path) {
        info->path = path;
        fork_command(info);
    } else {
        if ((interactive(info) || getenv_variable(info, "PATH=") || info->argv[0][0] == '/') && is_command(info, info->argv[0])) {
            fork_command(info);
        } else if (*(info->arg) != '\n') {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_command - Fork a child process and execute an external command
 * @info: Pointer to the shell information structure
 */
void fork_command(ShellInfo *info) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork error");
        return;
    }

    if (child_pid == 0) {
        if (execve(info->path, info->argv, get_environment(info)) == -1) {
            free_shell_info(info, 1);
            if (errno == EACCES) {
                exit(126);
            }
            exit(1);
        }
    } else {
        wait(&(info->status));
        if (WIFEXITED(info->status)) {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126) {
                print_error(info, "Permission denied\n");
            }
        }
    }
}

