/*
    SUDOKU SOLVER - 07/03/2023
    TODO only log to txt if -l is present
*/


#include <iostream>
#include <string>
#include <cstring>
#include "checks.cpp"
#include "logger.cpp"
#include "util.cpp"


using namespace std;


const int width = 9;
const int height = 9;
int sudoku[width][height];
int maxTries = 10;
bool solved = false;
bool logging = false;


void handleInput(int argc, char* argv[])
{
    if (strcmp(argv[1], "-l") == 0)
        logging = true;

    if ((!logging && argc != 82) || (logging && argc != 83))  // only 9x9 sudoku supported
    {
        std::cout << "Sudoku puzzle string has to have 81 digits!" << std::endl << "Yours only has " << argc - 1 << " digits" << std::endl;
        exit;  // TODO does not work, replace with "return 1;"
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
                exit;  // TODO does not work, replace with return 3;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    handleInput(argc, argv);

    logger(sudoku, "ORIGINAL");
    
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
                    logger(sudoku);
                }
            }
        }
        tries++;
    }

    std::cout << "Solved without guessing: ";
    solved = checkSolved(sudoku);
    std::cout << (solved ? "True" : "False") << std::endl;

    if (!solved)  // with guesses (backtracking)
    {
        logger(sudoku, "PARTIAL ANSWER");

        int memoryIndex = 0;
        const int memory = 1000; // remember this amount of "moves"
        int* pastIndexes = new int[memory]; for (int i = 0; i < memory; i++) pastIndexes[i] = -1;
        
        while (!solved)
        {
            for (int j = 0; j < height; j++)
            {
                for (int i = 0; i < width; i++)
                {
                    if (!checkHorizontal(sudoku, j, possibleAnswers) || 
                        !checkVertical(sudoku, i, possibleAnswers) || 
                        !checkBox(sudoku, i, j, possibleAnswers))
                    {
                        i = memoryIndex % width;  
                        j = memoryIndex / width;
                        if (sudoku[i][j] < 9)
                        {
                            sudoku[i][j] = sudoku[i][j] + 1;
                        }
                        else
                        {
                            sudoku[i][j] = 0;
                            pastIndexes[memoryIndex] = -1;
                            memoryIndex--;
                            i = memoryIndex % width;  
                            j = memoryIndex / width;
                        }
                    }
                    else if (sudoku[i][j] == 0)
                    {
                        sudoku[i][j] = 1;
                        pastIndexes[memoryIndex] = i + j * width;
                    }

                    string backtrackIndexString = "Backtracking  i:" + to_string(i) + " j:" + to_string(j);
                    logger(sudoku, backtrackIndexString);
                }
            }

            std::cout << "Solved with backtracking: ";
            solved = checkSolved(sudoku);
            std::cout << (solved ? "True" : "False") << std::endl;
        }
    }

    logger(sudoku, "FINAL ANSWER");
    endLog();
    cout << "END" << endl;
    return 0;
}
