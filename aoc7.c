#include <stdio.h>
#include <stdlib.h>
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
    
    int *data = malloc(sizeof(int) * 1000);
    int amountOfItems = 0;
    int smallestValue = 0;
    int biggestValue = 0;
    
    char line[5000];
    while ((fgets(line, 5000, fp)) != NULL)
    {
        static int index = 0;
        
        char *token = strtok(line, ",");
        while(token != NULL)
        {
            int number = atoi(token);
            if (number < smallestValue)     { smallestValue = number; }
            else if (number > biggestValue) { biggestValue = number; }
            
            data[index] = number;
            amountOfItems++;
            index++;
            token = strtok(NULL, ",");
        }
    }
    
    int bestOutcome = 0;
    for (int i = 0; i <= biggestValue - smallestValue; i++)
    {
        int totalFuel = 0;
        for (int j = 0; j < amountOfItems; j++)
        {
            int fuelUsage = abs(data[j] - i);
            totalFuel += fuelUsage;
        }
        
        if (bestOutcome == 0) { bestOutcome = totalFuel; }
        else {
            if (bestOutcome > totalFuel) { bestOutcome = totalFuel; }
        }
    }
    
    printf("Best outcome: %d\n", bestOutcome);
    
    bestOutcome = 0;
    for (int i = 0; i <= biggestValue - smallestValue; i++)
    {
        int totalFuel = 0;
        for (int j = 0; j < amountOfItems; j++)
        {
            int diff = abs(data[j] - i);
            int fuelUsage = (diff * (diff + 1)) / 2;
            totalFuel += fuelUsage;
        }
        
        if (bestOutcome == 0) { bestOutcome = totalFuel; }
        else {
            if (bestOutcome > totalFuel) { bestOutcome = totalFuel; }
        }
    }
    
    printf("Best outcome: %d\n", bestOutcome);
    
    // Cleanup
    free(data);
    fclose(fp);
    return 0;
}