#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Check for input file in the arguments
    if (argc < 2)
    {
        printf("Usage: %s [input file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Open the file
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open %s, %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    // Go through each line
    char line[200];      // Input buffer
    int numIncr = 0;
    int prevNum = 0;
    while (fgets(line, 200, fp) != NULL)
    {
        // This is where we do stuff for each line in the input file
        // Skip everything if it's the first item in the list
        if (prevNum == 0) {
			prevNum = atoi(line);    // atoi stands for Ascii to Integer
            continue;
        }
        
        int currentNum = atoi(line);
        if (currentNum > prevNum) {
            numIncr++;
        }
        
        prevNum = currentNum;
    }
    
    printf("Number of depth increased: %d\n", numIncr);
    
    // Cleaning up
    fclose(fp);
    return 0;
}
