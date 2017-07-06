#include <iostream>
#include <vector>
#include <cmath>

//just for unassigned location
enum
{
    UNASSIGNED = 0,
};

//for display shit
void printGrid( const std::vector< std::vector<int> > & GRID , int size)
{
    for(int i =0; i<size; ++i)
    {
        for(int j=0; j<size; ++j)
            std::cout<<GRID[i][j] << " ";
        std::cout << std::endl;
    }
}

// search the whole grid to find the unassigned location -> if found, row and col are set -> row,col referenced parameter
bool findUnassignedLocation(const std::vector<std::vector<int> > & GRID, int size, int & row, int & col)
{
    for(row=0; row<size; ++row)
        for(col=0; col<size; ++col)
            if(GRID[row][col] == UNASSIGNED)
                return true;
    return false;
}

// search in the row specified -> if num is already in the row then return true -> used up
bool usedInRow(const std::vector<std::vector<int> > & GRID, int size,int row, int num)
{
    for(int col=0; col<size; ++col)
        if(GRID[row][col] == num)
            return true;
    return false;
}

// search in the col specified -> if num is already in the col then return true -> used up
bool usedInCol(const std::vector<std::vector<int> > & GRID, int size, int col, int num)
{
    for(int row=0; row<size; ++row)
        if(GRID[row][col] == num)
            return true;
    return false;
}

// search in 3x3 sub grid -> if found return true -> used up
bool usedInBox(const std::vector<std::vector<int> > & GRID, int size, int startr, int startcol, int num)
{
    int n = sqrt(size);
    for(int row=0; row<n; ++row)
        for(int col=0; col<n; ++col)
            if(GRID[row+startr][col+startcol] == num)
                return true;
    return false;
}

// is inserting the num in row,col possible ???
bool isSafe(const std::vector<std::vector<int> > & GRID, int size, int row, int col, int num)
{
    int n = sqrt(size);
    return (!usedInRow(GRID, size, row, num) &&
            !usedInCol(GRID, size, col, num) &&
            !usedInBox(GRID, size, row - row%n, col-col%n, num));
}

// recursively solve the grid
bool solve(std::vector<std::vector<int> > & GRID, int size)
{
    int row, col;
    //if no location is UNASSIGNED -> GRID full -> return true;
    if(!findUnassignedLocation(GRID,size, row, col))
        return true;
    // now try to fill in -> 1 to 9 shit
    for(int num = 1; num<=9; ++num)
    {
        // if the insertion is possible @ row,col -> if safe -> no number exist in same row,col, subgrid
        if(isSafe(GRID,size,  row, col, num))
        {
            //assign the number
            GRID[row][col] = num;
            // recursion thing
            if(solve(GRID, size))
                return true;
            // else discard the assigned number -> make it UNASSGNED
            GRID[row][col] = UNASSIGNED;
        }
    }
    //if cant solve
    return false;
}

int main()
{
    std::vector<std::vector<int> > grid = { {5,3,0,0,7,0,0,0,0},
                                            {6,0,0,1,9,5,0,0,0},
                                            {0,9,8,0,0,0,0,6,0},
                                            {8,0,0,0,6,0,0,0,3},
                                            {4,0,0,8,0,3,0,0,1},
                                            {7,0,0,0,2,0,0,0,6},
                                            {0,6,0,0,0,0,2,8,0},
                                            {0,0,0,4,1,9,0,0,5},
                                            {0,0,0,0,8,0,0,7,9},
                                            };
    printGrid(grid,9);
    std::cout << "--------------------------------" << std::endl;
    solve(grid, 9);
    printGrid(grid,9);
    return 0;
}
