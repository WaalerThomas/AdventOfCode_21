#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

// NOTE: This one is not working. Solved it with a python script, but would love to manage it in C as well.

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [Input file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s, %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    // 1,2,3,4,5,6,7,8,0
    unsigned long fishes[9] = { 0 };
    
    char line[600];
    while (fgets(line, 600, fp) != NULL)
    {
        // Do stuff
    }
    
    // Cleanup
    fclose(fp);
    return 0;
}
