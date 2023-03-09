/*
    SUDOKU SOLVER - 07/03/2023
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

bool checkHorizontal(int* &sudoku, int i, int j, int* &possibleAnswers);
bool checkVertical(int* &sudoku, int i, int j, int* &possibleAnswers);
bool checkBox(int* &sudoku, int i, int j, int* &possibleAnswers);
bool checkSolved(int* &sudoku);

void printSudoku(int* &sudoku);

bool _checkHorizontal(int* &sudoku, int j);
bool _checkVertical(int* &sudoku, int i);
bool _checkBox(int* &sudoku, int i, int j);

// debug
void printCoordSudoku(int* &sudoku); 
void print(int* &possibleAnswers);



int main(int argc, char* argv[])
{
    if (strcmp(argv[1], "-d") == 0)  // if debug mode
    {
        debug = true;
        cout <<"DEBUG ON" << endl;
    }

    if ((!debug && argc != 82) || (debug && argc != 83))  // only 9x9 sudoku supported
    {
        cout << "Sudoku puzzle string has to have 81 digits!" << endl << "Yours only has " << argc - 1 << " digits";
        return 1;
    }

    int* sudoku = new int[width * height];
    int offset = (debug) ? 2 : 1;
    for (int i = 0; i < argc-1; i++)
    {
        sudoku[i] = atoi(argv[i+offset]);
        if (sudoku[i] > 9 || sudoku[i] < 0)  // input handling
        {
            cout << "Only numbers from 0 to 9 are valid! \"" << argv[i+offset] << "\" is not valid!" << endl;
            return 3;
        }
    }

    // printCoordSudoku(sudoku);

    bool solved = false;
    int* possibleAnswers = new int[9];
    reset(possibleAnswers);

    int tries = 0;
    while (tries < 10)  // place numbers without any guesses
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (debug) cout << endl << "i: " << i << " j:" << j << endl;

                reset(possibleAnswers);
                if (sudoku[index(i, j)] == 0)
                {
                    if (checkHorizontal(sudoku, i, j, possibleAnswers) | checkVertical(sudoku, i, j, possibleAnswers) | checkBox(sudoku, i, j, possibleAnswers))
                    {
                        sudoku[index(i, j)] = get(possibleAnswers);
                        tries = 0;
                    }
                }
                
                if (debug) print(possibleAnswers);
                if (debug) printSudoku(sudoku);
            }
            tries++;
        }
    }

    printSudoku(sudoku);

    cout << "Starting backtracking function..." << endl;

    int memoryIndex = 0;
    const int memory = 100; // remember 100 "moves"
    int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
    int* pastNumbers = new int[memory]; for (int i = 0; i < memory; i++) pastNumbers[i] = -1;
    
    cout << "Started while loop" << endl;
    int index = 0;
    while (!solved)  // guess, with backtracking
    {
        if (sudoku[index] == 0)
        {
            cout << "Number at index " << index << " is 0" << endl;
            for (int num = 1; num < 10; num++)
            {
                cout << "Trying " << num << endl;

                sudoku[index] = num;

                // get 2D i, j from 1D index TODO: test
                int i = index % width-1;
                int j = index / width-1;

                // always failing horizontally, others are probably also bugged
                if (_checkHorizontal(sudoku, j) && _checkVertical(sudoku, i) && _checkBox(sudoku, i, j))
                {
                    cout << "Index: " << index << " num: " << num << endl;
                    pastIndexes[memoryIndex] = index;
                    pastNumbers[memoryIndex] = num;
                    memoryIndex++;
                    index++;
                    break;
                }
                else 
                {
                    if (num == 9)  // backtrack
                    {
                        if (index > 0)
                        {
                            cout << "Backtracked!" << endl;
                            sudoku[index] = 0;
                            index--;
                            memoryIndex--;
                            num = pastNumbers[memoryIndex];
                            index = pastIndexes[memoryIndex];

                            pastNumbers[memoryIndex] = -1;
                            pastIndexes[memoryIndex] = -1;
                        }
                        else
                        {
                            cout << "None worked, moving on" << endl;
                            index++;
                        }
                        
                    }
                    else continue;
                }
            }
        }
        else
        {
            cout << "Number at index " << index << " is not 0" << endl;
            index++;
        }
        
        // cout << "Checking if solved... ";
        // solved = checkSolved(sudoku);
        // cout << ((solved) ? "True" : "False") << endl;
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

bool _checkHorizontal(int* &sudoku, int j)  // VERY bugged
{
    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int i = 0; i < width; i++)
    {
        cout << "Number at index " << index << " is " << sudoku[index(i, j)] << endl;
        if (numbers[sudoku[index(i, j)]-1] != -1 && numbers[sudoku[index(i, j)]-1] != 0)
        {
            cout << "Number at index " << index << " is was replaced by -1" << endl;
            numbers[sudoku[index(i, j)]-1] = -1;
        }
        else
        {
            cout << "Failed horizontally" << endl;
            return false;  // more than one of the same number
        }
    }
    cout << "It works horizontally" << endl;
    return true;
}

bool _checkVertical(int* &sudoku, int i)
{
    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = 0; j < height; j++)
    {
        if (numbers[sudoku[index(i, j)]-1] != -1 && numbers[sudoku[index(i, j)]-1] != 0)
        {
            numbers[sudoku[index(i, j)]-1] = -1;
        }
        else
        {
            cout << "Failed vertically" << endl;
            return false;  // more than one of the same number
        }
    }
    cout << "It works vertically" << endl;
    return true;
}

bool _checkBox(int* &sudoku, int i, int j)  // bugged
{
    int boxX = i / 3;
    int boxY = j / 3;

    // if (debug) cout << "BOX X: " << boxX << " BOX Y: " << boxY << endl;

    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            // if (debug) cout << "(" << i << "," << j << ") ";

            if (numbers[sudoku[index(i, j)]-1] != 0)
            {
                numbers[sudoku[index(i, j)]-1] = 0;
            }
            else
            {
                cout << "Failed boxly" << endl;
                return false;  // more than one of the same number
            }
        }
        // if (debug) cout << endl;
    }

    // if (debug) cout << endl;

    cout << "It works boxly" << endl;
    return true;
}





// rename these
bool checkHorizontal(int* &sudoku, int x, int j, int* &possibleAnswers)  // x is probably unnecessary
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

    if (length(possibleAnswers) == 1) return true;
    else return false;
}

bool checkVertical(int* &sudoku, int i, int y, int* &possibleAnswers)  // y is probably unnecessary
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

    if (length(possibleAnswers) == 1) return true;
    else return false;
}


bool checkBox(int* &sudoku, int i, int j, int* &possibleAnswers)  // bugged
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

    if (length(possibleAnswers) == 1) return true;
    else return false;
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
