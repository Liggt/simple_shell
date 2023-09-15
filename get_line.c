#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * input_buf - Buffer chained commands and read input.
 * @info: Parameter struct containing arguments.
 * @buf: Address of the buffer.
 * @len: Address of the len variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len) {
    ssize_t t = 0;
    size_t len_p = 0;

    if (!*len) {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        t = getline(buf, &len_p, stdin);
#else
        t = _getline(info, buf, &len_p);
#endif

        if (t > 0) {
            if ((*buf)[t - 1] == '\n') {
                (*buf)[t - 1] = '\0';
                t--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            *len = t;
            info->cmd_buf = buf;
        }
    }
    return (t);
}

/**
 * get_input - Get a line of input without the newline character.
 * @info: Parameter struct containing arguments.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info) {
    static char *buf; // Buffer for command chain
    static size_t x, y, len;
    ssize_t t = 0;
    char **buf_p = &(info->arg), *p;

    putchar(BUF_FLUSH);
    t = input_buf(info, &buf, &len);

    if (t == -1) {
        return (-1); // EOF
    }

    if (len) {
        y = x;
        p = buf + x;

        check_chain(info, buf, &y, x, len);
        while (y < len) {
            if (is_chain(info, buf, &y)) {
                break;
            }
            y++;
        }

        x = y + 1;
        if (x >= len) {
            x = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return (strlen(p));
    }

    *buf_p = buf;
    return (t);
}

/**
 * read_buf - Read data into a buffer.
 * @info: Parameter struct containing arguments.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Read data.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i) {
    ssize_t t = 0;

    if (*i) {
        return (0);
    }

    t = read(info->readfd, buf, READ_BUF_SIZE);
    if (t >= 0) {
        *i = t;
    }

    return (t);
}

/**
 * _getline - Get the next line of input from standard input.
 * @info: Parameter struct containing arguments.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: Read data.
 */
int _getline(info_t *info, char **ptr, size_t *length) {
    static char buf[READ_BUF_SIZE];
    static size_t x, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length) {
        s = *length;
    }

    if (x == len) {
        x = len = 0;
    }

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0)) {
        return (-1);
    }

    c = strchr(buf + x, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = realloc(p, s, s ? s + k : k + 1);
    if (!new_p) {
        return (p ? (free(p), -1) : -1);
    }

    if (s) {
        strncat(new_p, buf + x, k - x);
    } else {
        strncpy(new_p, buf + x, k - x + 1);
    }

    s += k - x;
    x = k;
    p = new_p;

    if (length) {
        *length = s;
    }

    *ptr = p;
    return (s);
}

/**
 * sigintHandler - Signal handler to block Ctrl+C.
 * @sig_num: Signal number.
 */
void sigintHandler(__attribute__((unused)) int sig_num) {
    putchar('\n');
    printf("$ ");
    fflush(stdout);
}

