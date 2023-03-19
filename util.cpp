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
/*
void printText()
{
    cout << ;
    cout << endl;
}
*/

void printArray(int* &array)
{
    for (int i = 0; i < 9; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int countFilledSpaces(int (*sudoku)[9])
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] > 0 && sudoku[i][j] < 10) count++;
        }
    }
    return count;
}
