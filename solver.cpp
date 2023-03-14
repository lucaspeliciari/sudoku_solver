/*
    SUDOKU SOLVER - 07/03/2023
*/


#include <iostream>
#include <string>
#include <cstring>
#include "checks.cpp"
#include "logger.cpp"
// #include "printer.cpp"


const int width = 9;
const int height = 9;
int sudoku[width][height];
int maxTries = 10;
bool solved = false;
bool logging = false;


int length(int* &possibleAnswers);
void reset(int* &possibleAnswers);
int get(int* &possibleAnswers);

// bool compareHorizontal(int* &sudoku, int j, int* &possibleAnswers);
// bool compareVertical(int* &sudoku, int i, int* &possibleAnswers);
// bool compareBox(int* &sudoku, int i, int j, int* &possibleAnswers);
// bool checkSolved(int* &sudoku);


void handleInput(int argc, char* argv[])
{
    if (strcmp(argv[1], "-l") == 0)
        logging = true;

    if ((!logging && argc != 82) || (logging && argc != 83))  // only 9x9 sudoku supported
    {
        std::cout << "Sudoku puzzle string has to have 81 digits!" << std::endl << "Yours only has " << argc - 1 << " digits" << std::endl;
        exit;  // TODO replace with "return 1;"
    }

    for (int j = 0; j < height; j++)  
    {
        for (int i = 0; i < width; i++)
        {
            int index = 1 + i + (j * width) + int(logging);  // 1 to skip first argv (path)
            sudoku[i][j] = atoi(argv[index]);
            if (sudoku[i][j] > 9 || sudoku[i][j] < 0)
            {
                std::cout << "Only numbers from 0 to 9 are valid! \"" << argv[index] << "\" is not valid!" << std::endl;
                exit;  // TODO replace with return 3;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    handleInput(argc, argv);

    log(sudoku, "ORIGINAL");
    
    int* possibleAnswers = new int[9];

    int tries = 0;
    while (tries < maxTries)  // place numbers without any guesses
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (sudoku[i][j] != 0) continue;

                reset(possibleAnswers);  // TODO can probably merge all 3 check functions
                if (checkHorizontal(sudoku, j, possibleAnswers) && checkVertical(sudoku, i, possibleAnswers) && checkBox(sudoku, i, j, possibleAnswers))
                {
                    if (length(possibleAnswers) == 1)
                    {
                        sudoku[i][j] = get(possibleAnswers);
                        log(sudoku);
                    }
                }
            }
        }
        tries++;
    }

    std::cout << "Solved... ";
    solved = checkSolved(sudoku);
    std::cout << ((solved) ? "True" : "False") << std::endl;

    if (!solved)  // all empty spaces have been successfully filled
    {
        log(sudoku, "PARTIAL ANSWER");

        int memoryIndex = 0;
        const int memory = 1000; // remember this amount of "moves"
        int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
        int* pastNumbers = new int[memory]; for (int i = 0; i < memory; i++) pastNumbers[i] = -1;
        
        // int backtrackCount = 0;
        while (!solved)
        {
            for (int j = 0; j < height; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    if (sudoku[i][j] != 0) continue;
                    
                    
                }
            }

            std::cout << "Solved... ";
            solved = checkSolved(sudoku);
            std::cout << ((solved) ? "True" : "False") << std::endl;
        }
    }

    log(sudoku, "ANSWER");
    endLog();
    cout << "END" << endl;
    return 0;
}


void reset(int* &possibleAnswers)
{
    for (int i = 0; i < width; i++) possibleAnswers[i] = i+1;
}

int length(int* &possibleAnswers)
{
    int length = 0;
    for (int i = 0; i < width; i++) 
        if (possibleAnswers[i] != -1) 
            length++;
    return length;
}

int get(int* &possibleAnswers)
{
    for (int i = 0; i < width; i++) 
        if (possibleAnswers[i] != -1) 
            return possibleAnswers[i];
    return 0;
}

/*bool compareHorizontal(int* &sudoku, int j, int* &possibleAnswers)
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
}*/
