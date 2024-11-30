#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

const int INF = numeric_limits<int>::max();

class Maze {
public:
    vector<vector<char>> grid;
    int rows, cols;

    Maze(int r, int c) : rows(r), cols(c), grid(r, vector<char>(c, '1')) {}

    void generateMaze() {
        srand(time(nullptr));
        carvePassage(0, 0);
        grid[0][0] = '0';           // Start point
        grid[rows - 1][cols - 1] = '0'; // End point
    }

    void displayMaze() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

private:
    void carvePassage(int r, int c) {
        static const vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        vector<pair<int, int>> shuffled_directions = directions;
        random_shuffle(shuffled_directions.begin(), shuffled_directions.end());

        for (const auto& dir : shuffled_directions) {
            int nr = r + dir.first * 2;
            int nc = c + dir.second * 2;
            if (isInBounds(nr, nc) && grid[nr][nc] == '1') {
                grid[r + dir.first][c + dir.second] = '0';
                grid[nr][nc] = '0';
                carvePassage(nr, nc);
            }
        }
    }

    bool isInBounds(int r, int c) const {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }
};

class Graph {
public:
    vector<vector<pair<int, int>>> adjList;
    int nodes;

    Graph(int numNodes) : nodes(numNodes), adjList(numNodes) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    vector<int> dijkstra(int start, vector<int>& prev) {
        vector<int> dist(nodes, INF);
        dist[start] = 0;
        prev[start] = -1;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& edge : adjList[u]) {
                int v = edge.first, weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
};

vector<int> getPath(const vector<int>& prev, int target) {
    vector<int> path;
    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int rows = 21, cols = 21;
    Maze maze(rows, cols);
    maze.generateMaze();
    maze.displayMaze();

    int start = 0, end = rows * cols - 1;
    Graph graph(rows * cols);

    auto index = [cols](int row, int col) { return row * cols + col; };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze.grid[i][j] == '1') continue; // Skip walls
            if (i > 0 && maze.grid[i - 1][j] == '0') graph.addEdge(index(i, j), index(i - 1, j), 1);
            if (i < rows - 1 && maze.grid[i + 1][j] == '0') graph.addEdge(index(i, j), index(i + 1, j), 1);
            if (j > 0 && maze.grid[i][j - 1] == '0') graph.addEdge(index(i, j), index(i, j - 1), 1);
            if (j < cols - 1 && maze.grid[i][j + 1] == '0') graph.addEdge(index(i, j), index(i, j + 1), 1);
        }
    }

    vector<int> prev(rows * cols, -1);
    vector<int> dist = graph.dijkstra(start, prev);

    if (dist[end] == INF) {
        cout << "No path found from start to end." << endl;
        return 1;
    }

    vector<int> path = getPath(prev, end);

    cout << "Shortest path from start to end:" << endl;
    for (int node : path) {
        int row = node / cols;
        int col = node % cols;
        cout << "(" << row << ", " << col << ") ";
    }
    cout << endl;

    return 0;
}
