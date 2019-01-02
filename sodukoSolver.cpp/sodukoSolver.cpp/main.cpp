#include <iostream>

using namespace std;

#define UNASSIGNED 0
#define N 9
int GRID[N][N];

bool findUnassignedLocation(int & row, int & col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (GRID[row][col] == UNASSIGNED)
                return true;
    return false;
}

bool usedInRow(int row, int num)
{
    for (int col = 0; col < N; col++)
        if (GRID[row][col] == num)
            return true;
    return false;
}


bool usedInCol(int col, int num)
{
    for (int row = 0; row < N; row++)
        if (GRID[row][col] == num)
            return true;
    return false;
}

bool usedInBox(int boxStartRow, int boxStartCol, int num)
{
    for(int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (GRID[boxStartRow + i][boxStartCol + j] == num)
                return true;
    return false;
}

bool isSafe(int row, int col, int num)
{
    
    return !usedInCol(col, num) && !usedInRow(row, num) && !usedInBox(row - row % 3, col - col % 3, num) && GRID[row][col] == UNASSIGNED;
}


void printGrid()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << GRID[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool SolveSudoku()
{
    int row, col;
    if (!findUnassignedLocation(row, col))
    {
        return true;
    }
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num))
        {
            GRID[row][col] = num;
            if (SolveSudoku())
            {
                return true;
            }
            GRID[row][col] = UNASSIGNED;
        }
    }
    return false;
}


int main()
{
    cout << "  SUDOKU SOLVER" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> GRID[i][j];
        }
    }
    cout << "\n    SOLUTION" << endl;
    cout << "   ---------" << endl;
    if (SolveSudoku())
    {
        printGrid();
    }
    else cout << "The solution does not exist" << endl;
}






/*
 0 7 0 0 0 0 5 0 0
 0 6 0 5 0 0 0 0 1
 0 9 0 0 2 7 3 0 0
 0 0 2 7 5 0 0 0 0
 0 3 0 0 0 2 0 4 0
 0 0 0 0 3 1 2 0 0
 0 0 9 2 1 0 0 8 0
 5 0 0 0 0 9 0 3 0
 0 0 8 0 0 0 0 5 0   */

/*
 4 9 0 0 0 0 1 0 0
 0 0 0 7 0 2 8 0 3
 8 0 7 0 0 0 0 0 0
 0 0 0 0 2 5 0 0 9
 0 0 8 0 0 0 6 0 0
 7 0 0 4 3 0 0 0 0
 0 0 0 0 0 0 4 0 6
 2 0 3 8 0 4 0 0 0
 0 0 1 0 0 0 0 2 8
 */

