#include <bits/stdc++.h>
using namespace std;

int n, m;

int N, M;
#define MAX_M 100
#define MAX_N 100

int arr[100][100];

int dx[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
int dy[9] = { 0, 0, 0, -1, -1, -1, 1, 1, 1 };


bool isValid(int x, int y)
{
    return (x >= 0 && y >= 0 && x < N && y < M);
}
 
void printGrid(bool grid[MAX_N][MAX_M])
{
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++) {
            if (grid[row][col])
                cout << "x ";
            else
                cout << "_ ";
        }
        cout << endl;
    }
}
 
// Function checks if the cell can have a mine or not
bool isSafe(int arr[MAX_N][MAX_M], int x, int y)
{
 
        if (!isValid(x, y))
        return false;
    for (int i = 0; i < 9; i++) {
 
        if (isValid(x + dx[i], y + dy[i]) && (arr[x + dx[i]][y + dy[i]] - 1 < 0))
            return (false);
    }
 
    for (int i = 0; i < 9; i++) {
        if (isValid(x + dx[i], y + dy[i]))

            arr[x + dx[i]][y + dy[i]]--;
    }
 
    return true;
}
 
bool unvisited(bool visited[MAX_N][MAX_M], int& x, int& y)
{
    for (x = 0; x < N; x++)
        for (y = 0; y < M; y++)
            if (!visited[x][y])
                return (true);
    return (false);
}
 
// Function checks if all the cells are visited or not and the input array is satisfied with the mine assignments
bool isDone(int arr[MAX_N][MAX_M], bool visited[MAX_N][MAX_M])
{
    bool done = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) 
        {
            done= done && (arr[i][j] == 0) && visited[i][j];
        }
    }
 
    return (done);
}
 
// Function to solve the minesweeper matrix
bool SolveMinesweeper(bool grid[MAX_N][MAX_M],int arr[MAX_N][MAX_M],bool visited[MAX_N][MAX_M])
{
    bool done = isDone(arr, visited);
 
    // If the solution exists and all cells are visited
    if (done)
        return true;
 
    int x, y;
 
    // Function call to check if all the cells are visited or not
    if (!unvisited(visited, x, y))
        return false;
 
     visited[x][y] = true;
 
    // Function to check if mine can be in given position
    if (isSafe(arr, x, y)) 
    {
        grid[x][y] = true;
 
        // Recursive call with (x, y) having a mine
        if (SolveMinesweeper(grid, arr, visited))
            return true;
 
        grid[x][y] = false;
        for (int i = 0; i < 9; i++) {
            if (isValid(x + dx[i], y + dy[i]))
                arr[x + dx[i]][y + dy[i]]++;
        }
    }
 
    // Recursive call without (x, y) having a mine
    if (SolveMinesweeper(grid, arr, visited))
 
        // If solution exists then return true
        return true;
 
    // Mark the position as unvisited again
    visited[x][y] = false;
 
    // If no solution exists
    return false;
}
 
void minesweeperOperations(int arr[MAX_N][MAX_N], int N,int M)
{
    bool grid[MAX_N][MAX_M];
    bool visited[MAX_N][MAX_M];

    memset(grid, false, sizeof(grid));
    memset(visited, false, sizeof(visited));
 
    if (SolveMinesweeper(grid, arr, visited)) 
    { 
        printGrid(grid);
    }
    else
        printf("No solution exists\n");
}

// Function to check if the cell location is valid

bool isVal(int x, int y)
{
	return (x >= 0 && y >= 0 && x < n && y < m);
}

// Functions generates a random minesweeper matrix with probability P of a cell being with a mine
void generatemineField(int ROW, int COL, int P)
{
	srand(time(NULL));

	int rand_val;
	int mines[ROW][COL];

	for (int x = 0; x < ROW; x++)
    {
		for (int y = 0; y < COL; y++) 
        {
			rand_val = rand() % 100;
			if (rand_val < P)
            	mines[x][y] = true;
            else
				mines[x][y] = false;
		}
	}

	cout << "Input:"<<endl;
	for (int x = 0; x < ROW; x++) 
    {
		for (int y = 0; y < COL; y++) 
        {
			arr[x][y] = 0;

			for (int k = 0; k < 9; k++) 
            {
				if(isVal(x + dx[k], y + dy[k])	&& (mines[x + dx[k]][y + dy[k]]))
					arr[x][y]++;
			}

			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
}

int main()
{
	n = 8, m = 7;
	int P = 25;
    N=8,M=7;
	generatemineField(n, m, P);
    minesweeperOperations(arr, N, M);
}