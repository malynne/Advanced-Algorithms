#include<bits/stdc++.h>
using namespace std;

void printGrid(vector<vector<int>> grid);
bool safeMove(vector<vector<int>> grid, vector<vector<bool>> visited, int x, int y);
vector<vector<int>> moves(vector<vector<int>> &mat, vector<vector<bool>> &visited, int i, int j, int x, int y, int &min_dist, int dist);
void shortPath(vector<vector<int>> &grid, int &x, int &y, int &destX, int &destY);

int main()
{
	vector<vector<int>> grid =  {{1,1,1,1,1},
                                {1,1,0,0,1},
                                {1,1,1,1,1},
                                {0,1,0,1,0},
                                {1,1,0,1,1}};
    int x = 0;
    int y = 0;
    int destX = 4;
    int destY = 4;

    cout << "\nGrid original:\n" << endl;
    printGrid(grid);
    cout << "\nSoluciones posibles:\n" << endl;
    shortPath(grid, x, y, destX, destY);

}

void printGrid(vector<vector<int>> grid) 
{
    int i, j;
    int rows = grid.size();
    int cols = grid[0].size();

    for(i=0; i<rows; i++) 
    {
        cout << "\t";
        for(j=0; j<cols; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    } 
}
void printSolutions(vector<vector<int>> grid, vector<vector<bool>> visited, int destX, int destY) 
{
    int i, j;
    int rows = grid.size();
    int cols = grid[0].size();

    grid[destX][destY] = 2;

    for(i=0; i<rows; i++) 
    {
        for(j=0; j<cols; j++)
        {
            if(visited[i][j] == 1)
            {
                grid[i][j] = 2;
            }

        }
    }
    printGrid(grid);
    cout << endl;
} 

bool safeMove(vector<vector<int>> grid, vector<vector<bool>> visited, int x, int y) 
{
    return (x >= 0 && x < grid.size()) &&  // X 
            (y >= 0 && y < grid[0].size()) && // Y 
			grid[x][y] == 1 && !visited[x][y];  // Grid
}

vector<vector<int>> moves(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y, int destX, int destY, int &min_dist, int dist)
{
	if (x == destX && y == destY)
    {
		min_dist = min(dist, min_dist);
        if(min_dist == dist) 
            printSolutions(grid, visited, destX, destY);
		return grid;
	}

	visited[x][y] = true;
	
	if (safeMove(grid, visited, x + 1, y)) 
		grid = moves(grid, visited, x + 1, y, destX, destY, min_dist, dist + 1);
	if (safeMove(grid, visited, x, y + 1)) 
		grid = moves(grid, visited, x, y + 1, destX, destY, min_dist, dist + 1);
	if (safeMove(grid, visited, x - 1, y)) 
		grid = moves(grid, visited, x - 1, y, destX, destY, min_dist, dist + 1);
	if (safeMove(grid, visited, x, y - 1))
		grid = moves(grid, visited, x, y - 1, destX, destY, min_dist, dist + 1);

	visited[x][y] = false;
    return grid;
}

void shortPath(vector<vector<int>> &grid, int &x, int &y, int &destX, int &destY)
{
	if (grid.size() == 0 || grid[x][y] == 0 || grid[destX][destY] == 0) return;
	
	int rows = grid.size();
	int cols = grid[0].size();
	int min_dist;

	vector<vector<bool>> visited;
	visited.resize(rows, vector<bool>(cols));

	grid = moves(grid, visited, x, y, destX, destY, min_dist, 0);
}