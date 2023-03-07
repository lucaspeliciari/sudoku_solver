#include <iostream>

using namespace std;


const int width = 9;
const int height = 9;

int index(int i, int j);
bool checkHorizontal(int* &sudoku, int i, int j);
bool checkVertical(int* &sudoku, int i, int j);
bool checkBox(int* &sudoku, int i, int j);
bool checkSolved(int* &sudoku);


int main(int argc, char* argv[])
{
    int* sudoku = new int[width * height];
    for (int i = 0; i < argc; i++)
    {
        sudoku[i] = atoi(argv[i+1]);
    }

    bool solved = false;
    while (!solved)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                // cout << index(i, j) << ": " << sudoku[index(i, j)] << endl;
                if (sudoku[index(i, j)] == 0)
                {
                    checkHorizontal(sudoku, i, j);
                    checkVertical(sudoku, i, j);
                    checkBox(sudoku, i, j);
                }
            }
        }
        solved = checkSolved(sudoku);
    }
    





    return 0;
}


int index(int i, int j)
{
    int index = i + j * height;
    return index;
}

bool checkHorizontal(int* &sudoku, int x, int j)
{
    for (int i = 0; i < width; i++)
    {
        if (i != x && sudoku[index(i, j)])
        {
            
        }
    }
    return true;
}


bool checkVertical(int* &sudoku, int i, int j)
{

}


bool checkBox(int* &sudoku, int i, int j)
{

}

bool checkSolved(int* &sudoku)
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (sudoku[index(i, j)] == 0) return false;
        }
    }
    return true;
}

