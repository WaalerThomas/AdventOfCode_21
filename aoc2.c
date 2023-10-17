#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [input file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("Could not open %s: %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    char line[200];
    int horizontalPos = 0;
    int depth = 0;
    while (fgets(line, 200, fp) != NULL)
    {
        char direction[20] = { 0 };
        int distance;
        sscanf(line, "%s %d", direction, &distance);
        
        if (strcmp(direction, "forward") == 0) {
            horizontalPos += distance;
        }
        else if(strcmp(direction, "up") == 0) {
            depth -= distance;
        }
        else if (strcmp(direction, "down") == 0) {
            depth += distance;
        }
    }
    
    printf("Horizontal Position: %d | Depth: %d | Equals: %d\n", horizontalPos, depth, (horizontalPos * depth));
    
    // Cleanup
    fclose(fp);
    return 0;
}