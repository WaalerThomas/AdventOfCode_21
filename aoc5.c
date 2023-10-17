#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define POINTS_LENGTH 1000

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
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    //int points[POINTS_LENGTH * POINTS_LENGTH] = {0};
    int *points = calloc(POINTS_LENGTH * POINTS_LENGTH, sizeof(int));
    if (points == NULL)
    {
        free(points);
        printf("Failed to initialize the points array, %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    char line[200];
    size_t len;
    size_t read;
    while (fgets(line, 200, fp) != NULL)
    {
        char firstPart[8], secondPart[8];
        int x1, x2, y1, y2;
        sscanf(line, "%s %*s %s", firstPart, secondPart);

        char *token = strtok(firstPart, ",");
        while (token != NULL)
        {
            x1 = atoi(token);
            token = strtok(NULL, ",");
            y1 = atoi(token);
            token = strtok(NULL, ",");
        }

        token = strtok(secondPart, ",");
        while (token != NULL)
        {
            x2 = atoi(token);
            token = strtok(NULL, ",");
            y2 = atoi(token);
            token = strtok(NULL, ",");
        }

        // Fill points inn
        if (x1 == x2)
        {
            int fromY = min(y1, y2);
            int toY = max(y1, y2);

            for (int i = fromY; i <= toY; i++) {
                points[i * POINTS_LENGTH + x1] += 1;
            }
        }
        else if (y1 == y2)
        {
            int fromX = min(x1, x2);
            int toX = max(x1, x2);

            for (int i = fromX; i <= toX; i++) {
                points[y1 * POINTS_LENGTH + i] += 1;
            }
        }
        else
        {
            // Diagonal line
            int fromX = min(x1, x2);
            int toX = max(x1, x2);
            int steps = toX - fromX;

            int x = x1, y = y1;
            for (int i = 0; i <= steps; i++)
            {
                points[y * POINTS_LENGTH + x] += 1;
                (x1 > x2) ? x-- : x++;
                (y1 > y2) ? y-- : y++;
            }
        }
    }

    int overlapAmount = 0;
    for (int i = 0; i < POINTS_LENGTH * POINTS_LENGTH; i++)
    {
        if (points[i] >= 2) {
            overlapAmount++;
        }
    }

    printf("Overlap points: %d\n", overlapAmount);

    // Cleanup
    free(points);
    fclose(fp);
    return 0;
}
