/*
    Functions that check lines or boxes for repeat numbers
    TODO can probably merge all 3 check functions, with maxI and maxJ as arguments
*/


bool checkHorizontal(int (*sudoku)[9], int j, int* &possibleAnswer, int setNumber = 0)
{
    bool isValid = true;

    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    if (setNumber > 0) possibleAnswer[setNumber-1] = -1;

    for (int i = 0; i < width; i++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
            else if (possibleAnswer[sudoku[i][j]-1] == -1) 
            {
                isValid = false;
            }
        }
        
    }
    return isValid;
}

bool checkVertical(int (*sudoku)[9], int i, int* &possibleAnswer, int setNumber = 0)
{
    bool isValid = true;

    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    if (setNumber > 0) possibleAnswer[setNumber-1] = -1;

    for (int j = 0; j < height; j++)
    {
        if (sudoku[i][j] == 0)
        {
            continue;
        }
        else
        {
            if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
            else if (possibleAnswer[sudoku[i][j]-1] == -1) 
            {
                isValid = false;
            }
        }
        
    }
    return isValid;
}

bool checkBox(int (*sudoku)[9], int i, int j, int* &possibleAnswer, int setNumber = 0)
{
    bool isValid = true;

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
            else
            {
                if (possibleAnswer[sudoku[i][j]-1] != -1) possibleAnswer[sudoku[i][j]-1] = -1;
                else if (possibleAnswer[sudoku[i][j]-1] == -1) 
                {
                    isValid = false;
                }
            }
        }
    }
    return isValid;
}

bool checkSolved(int sudoku[9][9])
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int* defaultArray = new int[9]; for (int i = 0; i < 9; i++) defaultArray[i] = i+1;
            if (sudoku[i][j] == 0)           
            {
                return false;
            }
            if (!checkHorizontal(sudoku, j, defaultArray))
            {
                return false;
            }
            defaultArray = new int[9]; for (int i = 0; i < 9; i++) defaultArray[i] = i+1;
            if (!checkVertical(sudoku, i, defaultArray))
            {
                return false;
            }
            defaultArray = new int[9]; for (int i = 0; i < 9; i++) defaultArray[i] = i+1;
            if (!checkBox(sudoku, i, j, defaultArray))
            {
                return false;
            }
            defaultArray = new int[9]; for (int i = 0; i < 9; i++) defaultArray[i] = i+1;
        }
    }
    return true;
}
