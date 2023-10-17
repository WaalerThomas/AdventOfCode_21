#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/*
DATA:
    101011111001
    111111011110
    010000111100
    101000010000
    011101100010
*/

typedef struct Rating
{
    unsigned int num_zero;
    unsigned int num_one;
} Rating;

int BinToDec(const char *bin)
{
    // Every input binary is going to be 12-bits
    float sum = 0.0f, exponent = 11.0f;
    for (int i = 0; i < 12; i++)
    {
        int number = (int)bin[i] - '0';
        if (number)
            sum += powf(2, exponent) * number;
        exponent--;
    }
    return sum;
}

Rating GetCommunality(char list[][13], size_t listSize, unsigned int index)
{
    Rating rating = (Rating){ 0, 0 };
    for (size_t i = 0; i < listSize; i++)
    {
        int number = (int)list[i][index] - '0';
        if (number) { rating.num_one++; }
        else        { rating.num_zero++; }
    }
    return rating;
}

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
        printf("Could not open %s, %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char dataGeneratorArray[1000][13] = { 0 };
    char dataScrubberArray[1000][13] = { 0 };
    size_t dataGeneratorArraySize = 0;
    size_t dataScrubberArraySize = 0;
    int listIndex = 0;
    int numZero[12] = { 0 };
    int numOne[12]  = { 0 };

    char line[200];
    while (fgets(line, 200, fp) != NULL)
    {
        // Go through every bit in the string
        for (int i = 0; i < 12; i++)
        {
            int number = (int)line[i] - '0';
            if (number) { numOne[i]++; }
            else        { numZero[i]++; }
        }

        // Make file into a list
        line[12] = '\0';
        strcpy(dataGeneratorArray[listIndex], line);
        strcpy(dataScrubberArray[listIndex], line);
        dataGeneratorArraySize++;
        dataScrubberArraySize++;
        listIndex++;
    }

    char gammaRate[12] = "";
    char epsilonRate[12] = "";
    for (int i = 0; i < 12; i++)
    {
        // Check if 0 is the most common
        if (numZero[i] > numOne[i]) {
            gammaRate[i] = '0';
            epsilonRate[i] = '1';
        }
        // Check if 1 is the most common
        else if (numOne[i] > numZero[i]) {
            gammaRate[i] = '1';
            epsilonRate[i] = '0';
        }
    }

    int gammaValue = BinToDec(gammaRate);
    int epsilonValue = BinToDec(epsilonRate);
    printf("Gamma Rate: %d, Epsilon Rate: %d | Power consumption: %d\n", gammaValue, epsilonValue, (gammaValue * epsilonValue));

    // Calculate generator
    char generatorRating = '0';
    char generatorStr[13] = { 0 };
    for (int i = 0; i < 12; i++)
    {
        Rating rating = GetCommunality(dataGeneratorArray, dataGeneratorArraySize, i);

        if (rating.num_zero > rating.num_one)       { generatorRating = '0'; }
        else if (rating.num_one > rating.num_zero)  { generatorRating = '1'; }
        else if (rating.num_one == rating.num_zero) { generatorRating = '1'; }

        for (int j = dataGeneratorArraySize - 1; j >= 0; j--) {
            if (dataGeneratorArray[j][i] != generatorRating) {
                for (int k = j; k < dataGeneratorArraySize; k++) {
                    strcpy(dataGeneratorArray[k], dataGeneratorArray[k + 1]);
                }
                dataGeneratorArraySize--;
            }
        }

        // Check if we are done
        if (dataGeneratorArraySize == 1) {
            strcpy(generatorStr, dataGeneratorArray[0]);
            break;
        }
    }

    int generatorValue = BinToDec(generatorStr);
    printf("Generator Value: %s | %d\n", generatorStr, generatorValue);

    // Calculate scrubber
    char scrubberRating = '0';
    char scrubberStr[13] = { 0 };
    for (int i = 0; i < 12; i++)
    {
        Rating rating = GetCommunality(dataScrubberArray, dataScrubberArraySize, i);

        if (rating.num_zero > rating.num_one)       { scrubberRating = '1'; }
        else if (rating.num_one > rating.num_zero)  { scrubberRating = '0'; }
        else if (rating.num_one == rating.num_zero) { scrubberRating = '0'; }

        for (int j = dataScrubberArraySize - 1; j >= 0; j--) {
            if (dataScrubberArray[j][i] != scrubberRating) {
                for (int k = j; k < dataScrubberArraySize; k++) {
                    strcpy(dataScrubberArray[k], dataScrubberArray[k + 1]);
                }
                dataScrubberArraySize--;
            }
        }

        // Check if we are done
        if (dataScrubberArraySize == 1) {
            strcpy(scrubberStr, dataScrubberArray[0]);
            break;
        }
    }

    int scrubberValue = BinToDec(scrubberStr);
    printf("Scrubber Value: %s | %d\n", scrubberStr, scrubberValue);
    printf("Life support Rating: %d\n", (generatorValue * scrubberValue));

    // Cleanup
    fclose(fp);
    return 0;
}
