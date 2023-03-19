#include <iostream>


void reset(int* &possibleAnswers)
{
    for (int i = 0; i < 9; i++) possibleAnswers[i] = i+1;
    return;
}

int length(int* &possibleAnswers)
{
    int length = 0;
    for (int i = 0; i < 9; i++) 
        if (possibleAnswers[i] != -1) 
            length++;
    return length;
}

int get(int* &possibleAnswers, int randomIndex = -1)
{
    int currentIndex = 0;
    for (int i = 0; i < 9; i++) 
        if (possibleAnswers[i] != -1) 
        {
            if (randomIndex == -1)
                return possibleAnswers[i];
            else
            {
                if (currentIndex == randomIndex) return possibleAnswers[i];
                else currentIndex++;
            }
        }
            
    return 0;
}

void printPuzzle(int sudoku[9][9]) 
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;

    std::cout << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << sudoku[i][j] << " ";
            if (i != 0 && (i+1) % 3 == 0) std::cout << " ";
        }
        std::cout << std::endl;
        if (j != 0 && (j+1) % 3 == 0) std::cout << std::endl;
    }
}
