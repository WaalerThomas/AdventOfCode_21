#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

typedef struct Board {
    int id;
    char data[25][3];
} Board;

void print_board(Board *boards, const int index)
{
    printf("===== Board %2d =====\n", boards[index].id);
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                printf("%2s ", boards[index].data[y * 5 + x]);
            }
            printf("\n");
        }
}

void remove_board(Board *boards, size_t *size, const int index)
{
    for (int i = index; i < *size; i++) {
        boards[i] = boards[i + 1];
    }
    *size -= 1;;
}

int check_for_bingo(Board *boards, size_t *size)
{
    bool isWinnerFound = false;
    int winnerIndex = -1;
    for (int i = 0; i < *size; i++)
    {
        if (isWinnerFound) { break; }
        
        // Checking columns
        for (int col = 0; col < 5; col++)
        {
            int amountFound = 0;
            for (int element = 0; element < 5; element++)
            {
                if (strcmp(boards[i].data[element * 5 + col], "X") == 0) {
                    amountFound++;
                    continue;
                }
                break;
            }
            
            if (amountFound == 5)
            {
                winnerIndex = i;
                isWinnerFound = true;
                break;
            }
        }
        
        // Checking rows
        for (int row = 0; row < 5; row++)
        {
            int amountFound = 0;
            for (int element = 0; element < 5; element++)
            {
                if (strcmp(boards[i].data[row * 5 + element], "X") == 0) {
                    amountFound++;
                    continue;
                }
                break;
            }
            
            if (amountFound == 5)
            {
                winnerIndex = i;
                isWinnerFound = true;
                break;
            }
        }
    }
    
    return winnerIndex;
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
        printf("Could not open file %s, %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[200];
    // Read the first line with all the numbers to be chosen
    fgets(line, 200, fp);

    char bingoNumbers[100][3] = { 0 };
    char *token = strtok(line, ",");
    while (token != NULL)
    {
        static int numIndex = 0;
        
        strcpy(bingoNumbers[numIndex], token);
        numIndex++;
        token = strtok(NULL, ",");
    }
    
    Board boards[100] = { 0 };
    size_t boardsArraySize = 0;
    while (fgets(line, 200, fp) != NULL)
    {
        static int boardIndex = -1;
        static int boardY = 0;
        
        if (strlen(line) <= 1)
        {
            boardY = 0;
            boardIndex++;
            boardsArraySize++;
            continue;
        }
        
        boards[boardIndex].id = boardIndex; // It will set the id for every line that we read that isnt empty
        sscanf(line, "%s %s %s %s %s", boards[boardIndex].data[boardY * 5 + 0], boards[boardIndex].data[boardY * 5 + 1], boards[boardIndex].data[boardY * 5 + 2], boards[boardIndex].data[boardY * 5 + 3], boards[boardIndex].data[boardY * 5 + 4]);
        boardY++;
    }
    
    // Game loop
    int currentNumber = -1;
    int winningBoardIndex = 0;
    bool isWinnerFound = false;
    while (!isWinnerFound)
    {
        currentNumber++;
        
        // Goes through all the boards
        for (int i = 0; i < boardsArraySize; i++) {
            for (int j = 0; j < 25; j++) {
                if (strcmp(boards[i].data[j], bingoNumbers[currentNumber]) == 0) {
                    strcpy(boards[i].data[j], "X");
                }
            }
        }
        
        // Check if someone has gotten bingo, only check after 5 draws
        if (currentNumber >= 5)
        {
            int checkWin = check_for_bingo(boards, &boardsArraySize);
            if (checkWin != -1)
            {
                winningBoardIndex = checkWin;
                isWinnerFound = true;
            }
            }
    }
    
    printf("Board %d won! Last number being: %s\n", boards[winningBoardIndex].id, bingoNumbers[currentNumber]);
    print_board(boards, winningBoardIndex);
    
    int overallSum = 0;
    int winningNumber = atoi(bingoNumbers[currentNumber]);
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int number = atoi(boards[winningBoardIndex].data[y * 5 + x]);
            overallSum += number;
        }
    }
    printf("Winning board score: %d\n", (overallSum * winningNumber));
    printf("=========================================\n\n");
    
    // Remove the winning board from the list
    remove_board(boards, &boardsArraySize, winningBoardIndex);
    
    while (boardsArraySize != 1)
    {
        currentNumber++;
        
        // Goes through all the boards
        for (int i = 0; i < boardsArraySize; i++) {
            for (int j = 0; j < 25; j++) {
                if (strcmp(boards[i].data[j], bingoNumbers[currentNumber]) == 0) {
                    strcpy(boards[i].data[j], "X");
                }
            }
        }
        
        // Check if someone has gotten bingo, only check after 5 draws
        if (currentNumber >= 5)
        {
            int checkWin;
            while ((checkWin = check_for_bingo(boards, &boardsArraySize)) != -1) {
                remove_board(boards, &boardsArraySize, checkWin);
            }
        }
    }
    isWinnerFound = false;
    while (!isWinnerFound)
    {
        currentNumber++;
        
        for (int j = 0; j < 25; j++) {
                if (strcmp(boards[0].data[j], bingoNumbers[currentNumber]) == 0) {
                    strcpy(boards[0].data[j], "X");
                }
        }
        
        int checkWin = check_for_bingo(boards, &boardsArraySize);
        if (checkWin != -1) {
            isWinnerFound = true;
        }
    }
    
    printf("Worst board %d. Last number being: %s\n", boards[0].id, bingoNumbers[currentNumber]);
    print_board(boards, 0);
    
    overallSum = 0;
    int lastNumber = atoi(bingoNumbers[currentNumber]);
    for (int i = 0; i < 25; i++)
    {
        int number = atoi(boards[0].data[i]);
        overallSum += number;
    }
    printf("Worst board score: %d\n", (overallSum * lastNumber));
    
    // Cleanup
    fclose(fp);
    return 0;
}
