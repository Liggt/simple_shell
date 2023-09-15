#include <stdlib.h> // Include the necessary header file

/**
 * bfree - Function that frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed successfully, 0 otherwise.
 */
int bfree(void **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr); // Free the memory pointed to by ptr
        *ptr = NULL; // Set the pointer to NULL
        return 1; // Return 1 to indicate success
    }
    return 0; // Return 0 if ptr is already NULL or if *ptr is NULL
}

