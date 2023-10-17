#include <stdlib.h>
#include <stdio.h>
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
        printf("Could not open file %s, %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    int numUniques = 0;
    
    char line[600];
    while ((fgets(line, 600, fp)) != NULL)
    {
        char outputValues[4][8] = { 0 };
        
        sscanf(line, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %s %s %s", outputValues[0], outputValues[1], outputValues[2], outputValues[3]);
        
        for (int i = 0; i < 4; i++)
        {
            int num = strlen(outputValues[i]);
            if (num == 2 || num == 3 || num == 4 || num == 7) { numUniques++; }
        }
    }
    
    printf("Number of unique digits: %d\n", numUniques);
    
    // NOTE(Tom): I don't know how to do part 2 :/
    
    // Cleanup
    fclose(fp);
    return 0;
}