#include "shell.h"

/**
 * get_history_file - Get the history file.
 * @info: Structure containing potential arguments.
 *
 * Return: Allocated string with the history file.
 */
char *get_history_file(info_t *info) {
    char *home_dir = _getenv(info, "HOME=");
    if (!home_dir) {
        return NULL;
    }

    char *history_file = malloc(strlen(home_dir) + strlen(HIST_FILE) + 2);
    if (!history_file) {
        return NULL;
    }

    strcpy(history_file, home_dir);
    strcat(history_file, "/");
    strcat(history_file, HIST_FILE);
    return history_file;
}

/**
 * write_history - Create or append to the history file.
 * @info: Structure containing potential arguments.
 *
 * Return: 1 on success, otherwise -1.
 */
int write_history(info_t *info) {
    int fd;
    char *filename = get_history_file(info);

    if (!filename) {
        return -1;
    }

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1) {
        return -1;
    }

    list_t *node = info->history;

    while (node) {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
        node = node->next;
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * read_history - Read history from a file.
 * @info: Structure containing potential arguments.
 *
 * Return: History count on success, 0 otherwise.
 */
int read_history(info_t *info) {
    int j, last = 0, linecount = 0;
    ssize_t d, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL;
    char *filename = get_history_file(info);

    if (!filename) {
        return 0;
    }

    d = open(filename, O_RDONLY);
    free(filename);

    if (d == -1) {
        return 0;
    }

    if (!fstat(d, &st)) {
        fsize = st.st_size;
    }

    if (fsize < 2) {
        return 0;
    }

    buf = malloc(fsize + 1);

    if (!buf) {
        return 0;
    }

    rdlen = read(d, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0) {
        free(buf);
        return 0;
    }

    close(d);

    for (j = 0; j < fsize; j++) {
        if (buf[j] == '\n') {
            buf[j] = 0;
            build_history_list(info, buf + last, linecount++);
            last = j + 1;
        }
    }

    if (last != j) {
        build_history_list(info, buf + last, linecount++);
    }

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX) {
        delete_node_at_index(&(info->history), 0);
    }

    renumber_history(info);
    return info->histcount;
}

/**
 * build_history_list - Add an entry to the history linked list.
 * @info: Structure containing potential arguments.
 * @buff: Buffer.
 * @linecount1: History line count.
 *
 * Return: 0 on success.
 */
int build_history_list(info_t *info, char *buff, int linecount1) {
    list_t *node = NULL;

    if (info->history) {
        node = info->history;
    }

    add_node_end(&node, buff, linecount1);

    if (!info->history) {
        info->history = node;
    }

    return 0;
}

/**
 * renumber_history - Renumber history after changes.
 * @info: Structure containing potential arguments.
 *
 * Return: The new history count.
 */
int renumber_history(info_t *info) {
    list_t *node = info->history;
    int j = 0;

    while (node) {
        node->num = j++;
        node = node->next;
    }

    return (info->histcount = j);
}

