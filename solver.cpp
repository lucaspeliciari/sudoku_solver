/*
    SUDOKU SOLVER - 07/03/2023

    Works with extremely easy puzzles, not so much with harder ones
        It never assumes or tries values, only what is 100% certain
    Suuuuper slow, especially with all the prints
    Add more comments to explain things
    Clean things up

    Sample: 
    0 9 3 1 0 5 6 4 0
    7 0 0 0 0 0 0 0 5
    5 0 1 2 0 9 3 0 7
    2 0 0 0 0 0 0 0 3
    0 3 6 9 0 7 5 2 0
    9 0 0 0 0 0 0 0 1
    3 0 2 4 0 8 1 0 9
    6 0 0 0 0 0 0 0 4
    0 4 7 3 0 2 8 5 0




    GETS STUCK ON THIS:
    8 9 3  1 7 5  6 4 2
    7 2 4  0 0 0  9 0 5
    5 6 1  2 4 9  3 8 7

    2 0 0  0 0 0  0 0 3
    4 3 6  9 1 7  5 2 8
    9 0 0  0 0 0  0 0 1

    3 0 2  4 0 8  1 0 9  
    6 0 0  0 0 0  0 0 4
    1 4 7  3 9 2  8 5 6
*/


#include <iostream>

using namespace std;


const int width = 9;
const int height = 9;

void debugPrint(int* &sudoku, int* &answer);

int index(int i, int j);
int length(int* &answer);
void resetAnswer(int* &answer);
int get(int* &answer);
void checkHorizontal(int* &sudoku, int i, int j, int* &answer);
void checkVertical(int* &sudoku, int i, int j, int* &answer);
void checkBox(int* &sudoku, int i, int j, int* &answer);
bool checkSolved(int* &sudoku);
void printSudoku(int* &sudoku);
void printCoordSudoku(int* &sudoku);  // debug

int main(int argc, char* argv[])
{
    // cout << "\033[2J\033[1;1H";  // should be clear screen

    if (argc != 82)
    {
        cout << "Sudoku puzzle string has to have 81 digits!" << endl << "Yours only has " << argc - 1 << " digits";
        return 1;
    }

    int* sudoku = new int[width * height];
    for (int i = 0; i < argc; i++)
    {
        sudoku[i] = atoi(argv[i+1]);
    }

    // printCoordSudoku(sudoku); return 0;  // DEBUG

    bool solved = false;
    int* answer = new int[9];
    resetAnswer(answer);

    debugPrint(sudoku, answer);  // DEBUG

    while (!solved)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                cout << endl << "i: " << i << " j:" << j << endl;

                resetAnswer(answer);
                if (sudoku[index(i, j)] == 0)
                {
                    if (length(answer) > 1) checkHorizontal(sudoku, i, j, answer);

                    if (length(answer) == 1)
                    {
                        sudoku[index(i, j)] = get(answer);
                        continue;
                    }

                    if (length(answer) > 0) checkVertical(sudoku, i, j, answer);

                    if (length(answer) == 1)
                    {
                        sudoku[index(i, j)] = get(answer);
                        continue;
                    }

                    if (length(answer) > 0) checkBox(sudoku, i, j, answer);

                    if (length(answer) == 1)
                    {
                        sudoku[index(i, j)] = get(answer);
                        continue;
                    }
                }
                debugPrint(sudoku, answer);
                cout << sudoku[index(0, 0)] << endl;
                printSudoku(sudoku);
                // return 0;

                // if (i == 8 && j == 8) return 0; // DEBUG
            }
        }
        solved = checkSolved(sudoku);
    }
    printSudoku(sudoku);

    return 0;
}


void debugPrint(int* &sudoku, int* &answer)
{
    cout << "DEBUG" << endl;
    // for (int i = 0; i < height * width; i++)
    // {
    //     cout << i << " " << sudoku[i] << endl;
    // }
    for (int i = 0; i < 9; i++)
    {
        cout << i << " " << answer[i] << " " << endl;
    }
    cout << endl;
}

int index(int i, int j)
{
    int index = i + j * height;
    return index;
}

void resetAnswer(int* &answer)
{
    for (int i = 0; i < width; i++) answer[i] = i+1;
}

int length(int* &answer)
{
    int length = 0;
    for (int i = 0; i < width; i++)
    {
        if (answer[i] != 0) length++;
    }
    return length;
}

int get(int* &answer)
{
    for (int i = 0; i < width; i++)
    {
        if (answer[i] != 0) return answer[i];
    }
    return 0;
}

void checkHorizontal(int* &sudoku, int x, int j, int* &answer)  // x is probably unnecessary
{
    for (int i = 0; i < width; i++)
    {
        if (i != x && sudoku[index(i, j)] != 0)
        {
            cout << "CHECKED HOR: " << sudoku[index(i, j)] << endl;
            answer[sudoku[index(i, j)]-1] = 0;
        }
    }
    cout << endl;
}

void checkVertical(int* &sudoku, int i, int y, int* &answer)  // y is probably unnecessary
{
    for (int j = 0; j < height; j++)
    {
        if (j != y && sudoku[index(i, j)] != 0)
        {
            cout << "CHECKED VER: " << sudoku[index(i, j)] << endl;
            answer[sudoku[index(i, j)]-1] = 0;
        }
    }
    cout << endl;
}


void checkBox(int* &sudoku, int i, int j, int* &answer)  // test this a lot
{
    int boxX = i / 3;
    int boxY = j / 3;
    cout << "BOX X: " << boxX << " BOX Y: " << boxY << endl;

    for (int j = boxY * 3; j < 3; j++)
    {
        for (int i = boxX * 3; i < 3; i++)
        {
            // cout << "(" << i << "," << j << ") ";  // DEBUG

            if (sudoku[index(i, j)] != 0)
            {
                cout << "CHECKED BOX: " << sudoku[index(i, j)] << endl;
                answer[sudoku[index(i, j)]-1] = 0;
            }
        }
        // cout << endl;  // DEBUG
    }

    cout << endl;
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
    cout << endl;
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
