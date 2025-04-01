#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void* allocate_memory(const char* size_str) {
    char* end;
    long long size = strtoull(size_str, &end, 10);
    char unit = (*end != '\0') ? tolower(*end) : 'b';

    switch(unit) {
        case 'k': size *= 1024; break;
        case 'm': size *= 1024*1024; break;
        case 'g': size *= 1024*1024*1024; break;
        default: return NULL;
    }

    void* mem = malloc(size);
    if (!mem) {
        perror("Memory allocation failed");
        return NULL;
    }
    // Touch memory pages to prevent swapping
    for (long long i = 0; i < size; i += 4096) {
        ((char*)mem)[i] = 0;
    }
    return mem;
}

int main(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "memory") != 0) {
        printf("Usage: %s memory <size>\n", argv[0]);
        return 1;
    }

    void* mem = allocate_memory(argv[2]);
    if (!mem) {
        fprintf(stderr, "Invalid size format. Use K/M/G suffix (e.g., 2G)\n");
        return 1;
    }

    printf("Allocated %s memory. Use Ctrl+C to exit.\n", argv[2]);
    while(1) sleep(1);
    return 0;
}
