/*
    Saves strings to a log.txt file
*/

#include <fstream>


std::ofstream file("log.txt");

void log(int sudoku[9][9], std::string title)  // TODO support variable width and height
{
    int width = sizeof sudoku / sizeof sudoku[0];
    int height = sizeof sudoku / sizeof(int);

    
    if (title.length() > 0) file << title << std::endl;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            file << sudoku[i, j] << " ";
            if (i != 0 && (i+1) % 3 == 0) file << " ";
        }
        file << std::endl;
        if (j != 0 && (j+1) % 3 == 0) file << std::endl;
    }
    std::string separator("-------------------");
    file << separator << std::endl << std::endl;
}

void finish()
{
    file.close();
}