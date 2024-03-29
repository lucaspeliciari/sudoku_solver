/*
    Saves strings to a log.txt file
*/


#include <fstream>


std::ofstream file("log.txt");

// TODO support variable width and height
void logger(int sudoku[9][9], std::string title="") 
{
    int width = sizeof(sudoku[0]) / sizeof(sudoku[0][0]);
    int height = 9;

    if (title.length() > 0) file << title << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            file << sudoku[i][j] << " ";
            if (i != 0 && (i+1) % 3 == 0) file << " ";
        }
        file << std::endl;
        if (j != 0 && (j+1) % 3 == 0) file << std::endl;
    }
    std::string separator("-------------------");
    file << separator << std::endl << std::endl;
}

void loggerArray(int* &array, int memoryIndex)
{
    for (int i = 0; i < 9; i++)
    {       
        file << array[i] << " ";
    }
    file << "index:" << memoryIndex;
    file << std::endl;
}

void endLog()
{
    std::string separator("-------------------");
    file << separator;
    file.close();
}