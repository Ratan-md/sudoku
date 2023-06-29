
#include <bits/stdc++.h>
 
using namespace std;

 
// 2D matrix os size n*n
#define n 9
 
void print(int arr[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " | ";
            
        }
        cout << endl;
    }
}
 
// checking if it is possible to assign a value of num to grid[row][col]
bool isSafe(int grid[n][n], int row,
                       int col, int num)
{
     
    // Checking if there is aldredy a num present in the row
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;
 
    // Checking if there is aldredy a num present in the column
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;
 
    // Checking if there is aldredy a num present in the 3x3 subgrid 
    int startRow = row - row % 3,
            startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                            startCol] == num)
                return false;
 
    return true;
}
 
// the below function takes a partially filled grid and tries to complete it
bool solve1(int grid[n][n], int row, int col)
{
    // Checking if we reached the last position on the grid. If we reached this position that means we finished solving the sudoku
    if (row == n - 1 && col == n)
        return true;
 
    if (col == n) {
        row++;
        col = 0;
    }
   
    //If a number is aldredy allocated to a certain position then we move to the next column
    if (grid[row][col] > 0)
        return solve1(grid, row, col + 1);
 
    for (int num = 1; num <= n; num++)
    {
         
        // Checking if we can place num in grid[row][col]. If possible we move on to the next column
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solve1(grid, row, col + 1))
                return true;
        }
       
        // If at any point later the solution returned a false i.e. the assumed value of num is incorrect then we replace grid[row][col] with its original value
        grid[row][col] = 0;
    }
    return false;
}
 
int main()
{
    int grid[n][n] = { { 5, 1, 0, 0, 7, 0, 4, 9, 2 },
                       { 0, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 4, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 2, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 0, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 0, 8, 9, 0, 0, 2, 0, 6 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 4 },
                       { 7, 0, 5, 2, 0, 6, 3, 0, 8 } };
 
    if (solve1(grid, 0, 0))
        print(grid);
    else
        cout << "solution does not exist" << endl;
 
    return 0;
}