/*
    Functions that check lines or boxes for repeat numbers
*/


bool checkSolved(int sudoku[9][9])
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (sudoku[i][j] == 0) return false;
        }
    }
    return true;
}

bool checkHorizontal(int (*sudoku)[9], int j, int* &possibleAnswer, int setNumber = 0)  // TODO check if this needs dereferencing (&)
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    if (setNumber > 0) possibleAnswer[setNumber-1] = -1;

    for (int i = 0; i < width; i++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else // TODO test this new if
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
        }
        
    }
    return true;
}


bool checkVertical(int (*sudoku)[9], int i, int* &possibleAnswer, int setNumber = 0)
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    if (setNumber > 0) possibleAnswer[setNumber-1] = -1;

    for (int j = 0; j < height; j++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else // TODO test this new if
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
        }
        
    }
    return true;
}

bool checkBox(int (*sudoku)[9], int i, int j, int* &possibleAnswer, int setNumber = 0)
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    int boxX = i / 3;
    int boxY = j / 3;

    if (setNumber > 0) possibleAnswer[setNumber-1] = -1;

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
            }
        }
    }
    return true;
}

