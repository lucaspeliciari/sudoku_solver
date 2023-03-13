/*
    Functions that check lines or boxes for repeat numbers
*/
#include "printer.cpp"
bool checkSolved(int sudoku[9][9])
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (sudoku[(i, j)] == 0) return false;
        }
    }
    return true;
}

bool checkHorizontal(int (*sudoku)[9], int j, int* &possibleAnswer)  // TODO check if this needs dereferencing (&)
{
    // std::cout << "HORIZONTAL" << std::endl; for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;
    
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    for (int i = 0; i < width; i++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else // TODO test this new if
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
            // else return false;
        }
        
    }
    // for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;
    return true;
}


bool checkVertical(int (*sudoku)[9], int i, int* &possibleAnswer)
{
    // std::cout << "VERTICAL" << std::endl; for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;

    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    for (int j = 0; j < height; j++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else // TODO test this new if
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
            // else return false;
        }
        
    }
    // for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;
    return true;
}

bool checkBox(int (*sudoku)[9], int i, int j, int* &possibleAnswer)
{
    // std::cout << "BOX" << std::endl; for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;

    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    int boxX = i / 3;
    int boxY = j / 3;

    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            if (sudoku[i][j] == 0)
            {
                continue;
            }
            else // TODO test this new if
            {
                if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
                // else return false;
            }
        }
    }
    // for (int i = 0; i < 9; i++) std::cout << possibleAnswer[i] << " "; std::cout << std::endl;
    return true;
}

