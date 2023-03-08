/*
    SUDOKU SOLVER - 07/03/2023

    Works with extremely easy puzzles, gets stuck on harder ones
        It never assumes or tries values, only what is 100% certain
    Suuuuper slow, especially with all the prints
    Add more comments to explain things
    Clean things up
    Use puzzles in files or maybe images instead of typing them as arg
    CHECK IF ANSWERS ARE CORRECT!

    Can solve this sample:  
    0 9 3  1 0 5  6 4 0
    7 0 0  0 0 0  0 0 5
    5 0 1  2 0 9  3 0 7

    2 0 0  0 0 0  0 0 3
    0 3 6  9 0 7  5 2 0
    9 0 0  0 0 0  0 0 1

    3 0 2  4 0 8  1 0 9
    6 0 0  0 0 0  0 0 4
    0 4 7  3 0 2  8 5 0
*/


#include <iostream>
#include <cstring>

using namespace std;


const int width = 9;
const int height = 9;
bool debug = false;


int index(int i, int j);

int length(int* &possibleAnswers);
void reset(int* &possibleAnswers);
int get(int* &possibleAnswers);

void checkHorizontal(int* &sudoku, int i, int j, int* &possibleAnswers);
void checkVertical(int* &sudoku, int i, int j, int* &possibleAnswers);
void checkBox(int* &sudoku, int i, int j, int* &possibleAnswers);
bool checkSolved(int* &sudoku);

void printSudoku(int* &sudoku);

// debug
void printCoordSudoku(int* &sudoku); 
void print(int* &possibleAnswers);



int main(int argc, char* argv[])
{
    // debug mode
    if (strcmp(argv[1], "-d") == 0)  
    {
        debug = true;
        cout <<"DEBUG ON" << endl;
    }

    if ((!debug && argc != 82) || (debug && argc != 83))  // only 9x9 sudoku supported
    {
        cout << "Sudoku puzzle string has to have 81 digits!" << endl << "Yours only has " << argc - 1 << " digits";
        return 1;
    }

    // should return 2 if there are letters or 3 if digits that are not 1-9

    int* sudoku = new int[width * height];
    if (!debug)
    {
        for (int i = 0; i < argc-1; i++)
        {
            sudoku[i] = atoi(argv[i+1]);
        }
    }
    else
    {
        for (int i = 0; i < argc-2; i++)
        {
            sudoku[i] = atoi(argv[i+2]);
        }
    }

    // printCoordSudoku(sudoku);

    bool solved = false;
    int* possibleAnswers = new int[9];
    reset(possibleAnswers);

    while (!solved)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (debug) cout << endl << "i: " << i << " j:" << j << endl;

                reset(possibleAnswers);
                if (sudoku[index(i, j)] == 0)
                {
                    if (length(possibleAnswers) > 1) checkHorizontal(sudoku, i, j, possibleAnswers);

                    if (length(possibleAnswers) == 1)
                    {
                        sudoku[index(i, j)] = get(possibleAnswers);
                        continue;
                    }

                    if (length(possibleAnswers) > 1) checkVertical(sudoku, i, j, possibleAnswers);

                    if (length(possibleAnswers) == 1)
                    {
                        sudoku[index(i, j)] = get(possibleAnswers);
                        continue;
                    }

                    if (length(possibleAnswers) > 1) checkBox(sudoku, i, j, possibleAnswers);

                    if (length(possibleAnswers) == 1)
                    {
                        sudoku[index(i, j)] = get(possibleAnswers);
                        continue;
                    }
                }
                if (debug) print(possibleAnswers);
                if (debug) printSudoku(sudoku);
            }
        }
        solved = checkSolved(sudoku);
    }
    printSudoku(sudoku);

    return 0;
}


void print(int* &array)
{
    cout << "DEBUG" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << i << " " << array[i] << " " << endl;
    }
    cout << endl;
}

int index(int i, int j)
{
    int index = i + j * height;
    return index;
}

void reset(int* &possibleAnswers)
{
    for (int i = 0; i < width; i++) possibleAnswers[i] = i+1;
}

int length(int* &possibleAnswers)
{
    int length = 0;
    for (int i = 0; i < width; i++)
    {
        if (possibleAnswers[i] != 0) length++;
    }
    return length;
}

int get(int* &possibleAnswers)
{
    for (int i = 0; i < width; i++)
    {
        if (possibleAnswers[i] != 0) return possibleAnswers[i];
    }
    return 0;
}

void checkHorizontal(int* &sudoku, int x, int j, int* &possibleAnswers)  // x is probably unnecessary
{
    for (int i = 0; i < width; i++)
    {
        if (i != x && sudoku[index(i, j)] != 0)
        {
            if (debug) cout << "CHECKED HOR: " << sudoku[index(i, j)] << endl;
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (debug) cout << endl;
}

void checkVertical(int* &sudoku, int i, int y, int* &possibleAnswers)  // y is probably unnecessary
{
    for (int j = 0; j < height; j++)
    {
        if (j != y && sudoku[index(i, j)] != 0)
        {
            if (debug) cout << "CHECKED VER: " << sudoku[index(i, j)] << endl;
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (debug) cout << endl;
}


void checkBox(int* &sudoku, int i, int j, int* &possibleAnswers)  // bugged
{
    int boxX = i / 3;
    int boxY = j / 3;

    if (debug) cout << "BOX X: " << boxX << " BOX Y: " << boxY << endl;

    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            if (debug) cout << "(" << i << "," << j << ") ";

            if (sudoku[index(i, j)] != 0)
            {
                if (debug) cout << "CHECKED BOX: " << sudoku[index(i, j)] << endl;
                possibleAnswers[sudoku[index(i, j)]-1] = 0;
            }
        }
        if (debug) cout << endl;
    }

    if (debug) cout << endl;
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

void printSudoku(int* &sudoku)
{
    cout << endl << "ANSWER:" << endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            cout << sudoku[index(i, j)] << " ";
            if (i != 0 && (i+1) % 3 == 0) cout << " ";
        }
        cout << endl;
        if (j != 0 && (j+1) % 3 == 0) cout << endl;
    }
}

void printCoordSudoku(int* &sudoku)
{
    cout << endl << "ANSWER:" << endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            cout << "(" << i+1 << "," << j+1 << ") ";
            if (i != 0 && (i+1) % 3 == 0) cout << " ";
        }
        cout << endl;
        if (j != 0 && (j+1) % 3 == 0) cout << endl;
    }
    cout << endl;
}
