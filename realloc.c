#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: Byte to fill the memory area with.
 * @n: Number of bytes to be filled.
 *
 * Return: Pointer to the memory area @s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int t;

    for (t = 0; t < n; t++)
        s[t] = b;

    return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings to be freed.
 *
 * Return: Nothing.
 */
void ffree(char **pp)
{
    char **a = pp;

    if (!pp)
        return;

    while (*pp)
    {
        free(*pp);
        pp++;
    }

    free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous memory block allocated.
 * @old_size: Previous block size.
 * @new_size: New block size.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return (malloc(new_size));

    if (!new_size)
    {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size)
        return (ptr);

    p = malloc(new_size);
    if (!p)
        return (NULL);

    old_size = (old_size < new_size) ? old_size : new_size;

    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];

    free(ptr);

    return (p);
}

