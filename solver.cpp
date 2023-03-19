/*
    SUDOKU SOLVER - 07/03/2023
    TODO still a segmentation fault bug with certain puzzles, apparently when trying to backtrack more than once in a row
*/


#include <string>
#include <cstring>
#include "checks.cpp"
#include "logger.cpp"
#include "util.cpp"


using namespace std;


const int width = 9;
const int height = 9;
int sudoku[width][height];
int maxTries = 1000000;
bool solved = false;
bool logging = false;


int handleInput(int argc, char* argv[])
{
    if (strcmp(argv[1], "-l") == 0)
        logging = true;

    string digitString = argv[1+logging];
    if (digitString.length() != 81)
    {
        
        cout << "Sudoku puzzle string has to have 81 digits!" << endl << "Yours only has " << strlen(argv[1+logging]) << " digits" << endl << "END" << endl;
        return 1;
    }

    for (int j = 0; j < height; j++)  
    {
        for (int i = 0; i < width; i++)
        {
            int index = i + j * width;
            sudoku[i][j] = int(digitString[index]) - 48;  // -48 due to ASCII value
            if (sudoku[i][j] < 0 || sudoku[i][j] > 9)
            {
                cout << "Digits must be between 0 and 9" << endl << sudoku[i][j] << " is not valid" << endl << "Digit from string was " << int(digitString[index]) << endl << "END" << endl;
                return 2;
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int inputHandling = handleInput(argc, argv);
    if (inputHandling > 0)
        return inputHandling;

    if (logging) logger(sudoku, "ORIGINAL");
    
    int* possibleAnswers = new int[9];

    int tries = 0;
    while (tries < maxTries)  // place numbers without any guesses
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (sudoku[i][j] != 0) continue;

                reset(possibleAnswers);
                checkHorizontal(sudoku, j, possibleAnswers); checkVertical(sudoku, i, possibleAnswers); checkBox(sudoku, i, j, possibleAnswers);
                if (length(possibleAnswers) == 1)
                {
                    sudoku[i][j] = get(possibleAnswers);
                    if (logging) logger(sudoku);
                }
            }
        }
        tries++;
    }

    cout << "Solved without guessing: ";
    solved = checkSolved(sudoku);
    cout << (solved ? "True" : "False") << endl;

    if (!solved)  // with guesses (backtracking)
    {
        tries = 0;
        if (logging) logger(sudoku, "PARTIAL ANSWER");

        int memoryIndex = 0;
        const int memory = 10000000; // remember this amount of "moves"
        int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
        
        int i = 0;
        int j = 0;
        while (!solved && tries < maxTries)
        {
            bool changed = false;

            if (sudoku[i][j] == 0)
            {
                sudoku[i][j] = 1;
                pastIndexes[memoryIndex] = i + j * width;
                memoryIndex++;

                if (logging) 
                {
                    string backtrackIndexString = "Found 0 and added 1 to it at i:" + to_string(i) + " j:" + to_string(j);
                    logger(sudoku, backtrackIndexString);
                }
                
            }

            int* possibleAnswers1 = new int[9]; reset(possibleAnswers1);  // TODO fix this
            int* possibleAnswers2 = new int[9]; reset(possibleAnswers2);  // done just to make sure the possible answers array does not have any -1 at function start
            int* possibleAnswers3 = new int[9]; reset(possibleAnswers3);
            if (!checkHorizontal(sudoku, j, possibleAnswers1) || !checkVertical(sudoku, i, possibleAnswers2) || !checkBox(sudoku, i, j, possibleAnswers3))
            {
                if (logging) 
                {
                    string backtrackIndexString = "ERROR!!!!!!!! AT i:" + to_string(i) + " j:" + to_string(j);
                    logger(sudoku, backtrackIndexString);
                }
                

                if (i + j * width > 0)
                {
                    memoryIndex--;
                    i = pastIndexes[memoryIndex] % width;
                    j = pastIndexes[memoryIndex] / width;
                }
                
                if (sudoku[i][j] < 9)
                {
                    sudoku[i][j] = sudoku[i][j] + 1;
                    if (logging) 
                    {
                        string backtrackIndexString = "Added 1 to current at i:" + to_string(i) + " j:" + to_string(j);
                        logger(sudoku, backtrackIndexString);
                    }
                }
                else
                {
                    sudoku[i][j] = 0;
                    pastIndexes[memoryIndex] = -1;
                    memoryIndex--;
                    i = pastIndexes[memoryIndex] % width;
                    j = pastIndexes[memoryIndex] / width;

                    while (sudoku[i][j] >= 9)
                    {
                        sudoku[i][j] = 0;
                        pastIndexes[memoryIndex] = -1;
                        memoryIndex--;
                        i = pastIndexes[memoryIndex] % width;
                        j = pastIndexes[memoryIndex] / width;
                    }
                    sudoku[i][j] = sudoku[i][j] + 1;

                    if (logging) 
                    {
                        string backtrackIndexString = "Went back to previous at i:" + to_string(i) + " j:" + to_string(j);
                        logger(sudoku, backtrackIndexString);
                    }
                }
                memoryIndex++;

                changed = true;
            }

            // ITERATE
            if (!changed)
            {
                i++;
                if (i > width-1)
                {
                    i = 0;
                    j++;
                }
            }
            
            // SANITY CHECKS
            if (memoryIndex < 0 || memoryIndex > memory-1) 
            {
                cout << "Memory index is either negative or greater than memory array's length" << endl;
                return 4;
            }

            solved = checkSolved(sudoku);
            tries++;
        }

        cout << "Solved with backtracking: ";
        cout << (solved ? "True" : "False") << endl;
    }

    if (tries >= maxTries) cout << "Exceeded maximum amount of tries after " << tries << " tries" << endl;
    
    if (logging)
    {
        logger(sudoku, "FINAL ANSWER");
        endLog();
    }
    printPuzzle(sudoku);

    return 0;
}
