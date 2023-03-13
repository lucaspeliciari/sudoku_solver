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
            if (sudoku[(i, j)] == 0) return false;
        }
    }
    return true;
}

bool checkHorizontal(int sudoku[9][9], int j, int possibleAnswer[9])  // TODO check if this needs dereferencing (&)
{
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
            else return false;
        }
        
    }
    return true;
}

/*
bool checkVertical(int sudoku[9][9], int i)
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = 0; j < height; j++)
    {
        // if (debug) 
        // {
        //     for (int indice = 0; indice < 9; indice++) 
        //         std::cout << numbers[indice] << ", "; 
        //     std::cout << std::endl;
        // }
        
        // if (debug) std::cout << "Number at index (" << i << ", " << j << ") is " << sudoku[index(i, j)] << std::endl;
        if (sudoku[(i, j)] != 0 && numbers[sudoku[(i, j)]-1] != -1)
        {
            numbers[sudoku[(i, j)]-1] = -1;
        }
        else if (sudoku[(i, j)] != 0 && numbers[sudoku[(i, j)]-1] == -1)
        {
            // if (debug) std::cout << "   Failed vertically!" << std::endl << std::endl;
            return false;
        }
    }
    // if (debug) std::cout << "   It works vertically!" << std::endl << std::endl;
    return true;
}

bool checkBox(int sudoku[9][9], int i, int j)
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;  // TODO try to do it dynamically, something similar to "sizeof(sudoku) / sizeof(sudoku[0])"

    int boxX = i / 3;
    int boxY = j / 3;

    // if (debug) std::cout << "BOX X: " << boxX << " BOX Y: " << boxY << std::endl;
    // if (debug) std::cout << "BOX X: " << boxX << " BOX Y: " << boxY << std::endl;

    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            // if (debug) 
            // {
            //     for (int indice = 0; indice < 9; indice++) 
            //         std::cout << numbers[indice] << ", "; 
            //     std::cout << std::endl;
            // }
            
            // if (debug) std::cout << "Number at index (" << i << ", " << j << ") is " << sudoku[index(i, j)] << std::endl;
            if (sudoku[(i, j)] != 0 && numbers[sudoku[(i, j)]-1] != -1)
            {
                numbers[sudoku[(i, j)]-1] = -1;
            }
            else if (sudoku[(i, j)] != 0 && numbers[sudoku[(i, j)]-1] == -1)
            {
                // if (debug) std::cout << "   Failed boxly!" << std::endl << std::endl;
                return false;
            }
        }
    }

    // if (debug) std::cout << "   It works boxly!" << std::endl << std::endl;
    return true;
}
*/
