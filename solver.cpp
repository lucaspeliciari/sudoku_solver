/*
    SUDOKU SOLVER - 07/03/2023
*/


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>



const int width = 9;
const int height = 9;
bool debug = false;
std::ofstream out("log.txt");


int index(int i, int j);

int length(int* &possibleAnswers);
void reset(int* &possibleAnswers);
int get(int* &possibleAnswers);

bool compareHorizontal(int* &sudoku, int j, int* &possibleAnswers);
bool compareVertical(int* &sudoku, int i, int* &possibleAnswers);
bool compareBox(int* &sudoku, int i, int j, int* &possibleAnswers);
bool checkSolved(int* &sudoku);

void printSudoku(int* &sudoku);

bool checkHorizontal(int* &sudoku, int j);
bool checkVertical(int* &sudoku, int i);
bool checkBox(int* &sudoku, int i, int j);

// debug
void logSudoku(int* &sudoku, std::string title="");
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

    logSudoku(sudoku);

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
                reset(possibleAnswers);
                if (sudoku[index(i, j)] == 0)
                {
                    if (compareHorizontal(sudoku, j, possibleAnswers) | compareVertical(sudoku, i, possibleAnswers) | compareBox(sudoku, i, j, possibleAnswers))
                    {
                        sudoku[index(i, j)] = get(possibleAnswers);
                        tries = 0;
                    }
                }
            }
            tries++;
        }
    }

    

    std::cout << "Solved... ";
    solved = checkSolved(sudoku);
    std::cout << ((solved) ? "True" : "False") << std::endl;

    if (solved)
    {
        logSudoku(sudoku);
    }
    else
    {
        logSudoku(sudoku, "PARTIAL ANSWER WITH NO GUESSES");
    

        std::cout << "Starting backtracking function..." << std::endl;

        int memoryIndex = 0;
        const int memory = 100; // remember 100 "moves"
        int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
        int* pastNumbers = new int[memory]; for (int i = 0; i < memory; i++) pastNumbers[i] = -1;
        
        std::cout << "Started second while loop" << std::endl;
        int index = 0;
        int backtrackCount = 0;
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
                    if (checkHorizontal(sudoku, j) && checkVertical(sudoku, i) && checkBox(sudoku, i, j))
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
                                logSudoku(sudoku, "Backtrack #" + std::to_string(backtrackCount));
                                backtrackCount++;
                                std::cout << "Backtracked!" << std::endl;
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
            
            std::cout << "Solved... ";
            solved = checkSolved(sudoku);
            std::cout << ((solved) ? "True" : "False") << std::endl;
            std::cout << "Index is " << index << std::endl;  // program ends when index = 268475675
        }
    }

    std::cout << std::endl << "Script over" << std::endl;

    logSudoku(sudoku, "FINAL ANSWER");
    printSudoku(sudoku);
    
    out.close();
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

bool checkHorizontal(int* &sudoku, int j)
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

bool checkVertical(int* &sudoku, int i)
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

bool checkBox(int* &sudoku, int i, int j)
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
}

bool compareHorizontal(int* &sudoku, int j, int* &possibleAnswers)
{
    for (int i = 0; i < width; i++)
    {
        if (sudoku[index(i, j)] != 0)
        {
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (length(possibleAnswers) == 1) return true;
    else return false;
}

bool compareVertical(int* &sudoku, int i, int* &possibleAnswers)
{
    for (int j = 0; j < height; j++)
    {
        if (sudoku[index(i, j)] != 0)
        {
            possibleAnswers[sudoku[index(i, j)]-1] = 0;
        }
    }
    if (length(possibleAnswers) == 1) return true;
    else return false;
}


bool compareBox(int* &sudoku, int i, int j, int* &possibleAnswers)
{
    int boxX = i / 3;
    int boxY = j / 3;

    for (int j = boxY * 3; j < boxY * 3 + 3; j++)
    {
        for (int i = boxX * 3; i < boxX * 3 + 3; i++)
        {
            if (sudoku[index(i, j)] != 0)
            {
                possibleAnswers[sudoku[index(i, j)]-1] = 0;
            }
        }
    }

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

void logSudoku(int* &sudoku, std::string title)
{
    if (title.length() > 0) out << title << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            out << sudoku[index(i, j)] << " ";
            if (i != 0 && (i+1) % 3 == 0) out << " ";
        }
        out << std::endl;
        if (j != 0 && (j+1) % 3 == 0) out << std::endl;
    }
    std::string separator("-------------------");
    out << separator << std::endl << std::endl;
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
