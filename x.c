#define _GNU_SOURCE  
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

// Define the original 'read' function pointer
ssize_t (*original_read)(int, void *, size_t) = NULL;

// Our custom 'read' function
ssize_t read(int fd, void *buf, size_t count) {
    // Initialize the original 'read' function
    if (!original_read) {
        original_read = dlsym(RTLD_NEXT, "read");
        if (!original_read) {
            fprintf(stderr, "Error in dlsym: %s\n", dlerror());
            _exit(1);
        }
    }

    // Call the original 'read' function
    ssize_t result = original_read(fd, buf, count);

    // Capture the read content (for demonstration, we'll print it)
    if (result > 0) {
        write(STDOUT_FILENO, buf, result); // Print to stdout
    }

    return result;
}

