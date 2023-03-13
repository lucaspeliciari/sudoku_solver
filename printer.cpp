/*
    Use this for anything that uses cout
    Maybe don't even use this and just use logger
*/


#include <iostream>
using namespace std;


// print entire puzzle
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



// print coordinates to help with debugging
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
