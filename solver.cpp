/*
    SUDOKU SOLVER - 07/03/2023
*/


#include <iostream>
#include <cstring>
#include <fstream>  // for logging



const int width = 9;
const int height = 9;
bool debug = false;
std::ofstream out("log.txt");


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
        std::cout <<"DEBUG ON" << std::endl;
    }

    if ((!debug && argc != 82) || (debug && argc != 83))  // only 9x9 sudoku supported
    {
        std::cout << "Sudoku puzzle string has to have 81 digits!" << std::endl << "Yours only has " << argc - 1 << " digits";
        return 1;
    }

    int* sudoku = new int[width * height];
    int offset = (debug) ? 2 : 1;
    for (int i = 0; i < argc-1; i++)
    {
        sudoku[i] = atoi(argv[i+offset]);
        if (sudoku[i] > 9 || sudoku[i] < 0)  // input handling
        {
            std::cout << "Only numbers from 0 to 9 are valid! \"" << argv[i+offset] << "\" is not valid!" << std::endl;
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
                if (debug) std::cout << std::endl << "i: " << i << " j:" << j << std::endl;

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

    std::cout << "Starting backtracking function..." << std::endl;

    int memoryIndex = 0;
    const int memory = 100; // remember 100 "moves"
    int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
    int* pastNumbers = new int[memory]; for (int i = 0; i < memory; i++) pastNumbers[i] = -1;
    
    std::cout << "Started second while loop" << std::endl;
    int index = 0;
    while (!solved)  // guess, with backtracking
    {
        if (sudoku[index] == 0)
        {
            if (debug) std::cout << "Number at index " << index << " is 0" << std::endl;
            for (int num = 1; num < 10; num++)
            {
                if (debug) std::cout << "Trying " << num << std::endl;

                sudoku[index] = num;

                // get 2D i, j from 1D index TODO: test
                int i = index % (width-1);
                int j = index / (width-1);

                // always failing horizontally, others are probably also bugged
                if (_checkHorizontal(sudoku, j) && _checkVertical(sudoku, i) && _checkBox(sudoku, i, j))
                {
                    if (debug) std::cout << "Index: " << index << " num: " << num << std::endl;
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
                            if (debug) std::cout << "Backtracked!" << std::endl;  // segmentation fault apparently
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
                            if (debug) std::cout << "None worked, moving on" << std::endl;
                            index++;
                        }
                        
                    }
                    else continue;
                }
            }
        }
        else
        {
            if (debug) std::cout << "Number at index " << index << " is not 0" << std::endl;
            index++;
        }
        
        // std::cout << "Checking if solved... ";
        // solved = checkSolved(sudoku);
        // std::cout << ((solved) ? "True" : "False") << std::endl;
    }

    printSudoku(sudoku);

    return 0;
}


void print(int* &array)
{
    std::cout << "DEBUG" << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << i << " " << array[i] << " " << std::endl;
    }
    std::cout << std::endl;
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
        if (debug) 
        {
            for (int indice = 0; indice < 9; indice++) 
                std::cout << numbers[indice] << ", "; 
            std::cout << std::endl;
        }
        
        if (debug) std::cout << "Number at index (" << i << ", " << j << ") is " << sudoku[index(i, j)] << std::endl;
        if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] != -1)
        {
            numbers[sudoku[index(i, j)]-1] = -1;
        }
        else if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] == -1)
        {
            if (debug) std::cout << "   Failed horizontally!" << std::endl << std::endl;
            return false;
        }
    }
    if (debug) std::cout << "   It works horizontally!" << std::endl << std::endl;
    return true;
}

bool _checkVertical(int* &sudoku, int i)
{
    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = 0; j < height; j++)
    {
        if (debug) 
        {
            for (int indice = 0; indice < 9; indice++) 
                std::cout << numbers[indice] << ", "; 
            std::cout << std::endl;
        }
        
        if (debug) std::cout << "Number at index (" << i << ", " << j << ") is " << sudoku[index(i, j)] << std::endl;
        if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] != -1)
        {
            numbers[sudoku[index(i, j)]-1] = -1;
        }
        else if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] == -1)
        {
            if (debug) std::cout << "   Failed vertically!" << std::endl << std::endl;
            return false;
        }
    }
    if (debug) std::cout << "   It works vertically!" << std::endl << std::endl;
    return true;
}

bool _checkBox(int* &sudoku, int i, int j)  // bugged
{
    int boxX = i / 3;
    int boxY = j / 3;

    // if (debug) std::cout << "BOX X: " << boxX << " BOX Y: " << boxY << std::endl;
    if (debug) std::cout << "BOX X: " << boxX << " BOX Y: " << boxY << std::endl;

    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            if (debug) 
            {
                for (int indice = 0; indice < 9; indice++) 
                    std::cout << numbers[indice] << ", "; 
                std::cout << std::endl;
            }
            
            if (debug) std::cout << "Number at index (" << i << ", " << j << ") is " << sudoku[index(i, j)] << std::endl;
            if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] != -1)
            {
                numbers[sudoku[index(i, j)]-1] = -1;
            }
            else if (sudoku[index(i, j)] != 0 && numbers[sudoku[index(i, j)]-1] == -1)
            {
                if (debug) std::cout << "   Failed boxly!" << std::endl << std::endl;
                return false;
            }
        }
    }
    if (debug) std::cout << "   It works boxly!" << std::endl << std::endl;
    return true;



    /*
    int* numbers = new int[9]; for (int i = 0; i < width; i++) numbers[i] = i+1;
    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            // if (debug) std::cout << "(" << i << "," << j << ") ";

            if (numbers[sudoku[index(i, j)]-1] != 0)
            {
                numbers[sudoku[index(i, j)]-1] = 0;
            }
            else
            {
                std::cout << "Failed boxly" << std::endl;
                return false;  // more than one of the same number
            }
        }
        // if (debug) std::cout << std::endl;
    }*/

    // if (debug) std::cout << std::endl;

    std::cout << "It works boxly" << std::endl;
    return true;
}





// rename these
bool checkHorizontal(int* &sudoku, int x, int j, int* &possibleAnswers)  // x is probably unnecessary
{
    for (int i = 0; i < width; i++)
    {
        if (i != x && sudoku[index(i, j)] != 0)
        {
            if (debug) std::cout << "CHECKED HOR: " << sudoku[index(i, j)] << std::endl;
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (debug) std::cout << std::endl;

    if (length(possibleAnswers) == 1) return true;
    else return false;
}

bool checkVertical(int* &sudoku, int i, int y, int* &possibleAnswers)  // y is probably unnecessary
{
    for (int j = 0; j < height; j++)
    {
        if (j != y && sudoku[index(i, j)] != 0)
        {
            if (debug) std::cout << "CHECKED VER: " << sudoku[index(i, j)] << std::endl;
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (debug) std::cout << std::endl;

    if (length(possibleAnswers) == 1) return true;
    else return false;
}


bool checkBox(int* &sudoku, int i, int j, int* &possibleAnswers)  // bugged
{
    int boxX = i / 3;
    int boxY = j / 3;

    if (debug) std::cout << "BOX X: " << boxX << " BOX Y: " << boxY << std::endl;

    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            if (debug) std::cout << "(" << i << "," << j << ") ";

            if (sudoku[index(i, j)] != 0)
            {
                if (debug) std::cout << "CHECKED BOX: " << sudoku[index(i, j)] << std::endl;
                possibleAnswers[sudoku[index(i, j)]-1] = 0;
            }
        }
        if (debug) std::cout << std::endl;
    }

    if (debug) std::cout << std::endl;

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
    std::cout << std::endl << "ANSWER:" << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << sudoku[index(i, j)] << " ";
            if (i != 0 && (i+1) % 3 == 0) std::cout << " ";
        }
        std::cout << std::endl;
        if (j != 0 && (j+1) % 3 == 0) std::cout << std::endl;
    }
}

void printCoordSudoku(int* &sudoku)
{
    std::cout << std::endl << "ANSWER:" << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            std::cout << "(" << i+1 << "," << j+1 << ") ";
            if (i != 0 && (i+1) % 3 == 0) std::cout << " ";
        }
        std::cout << std::endl;
        if (j != 0 && (j+1) % 3 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}
