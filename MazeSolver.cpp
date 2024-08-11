
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <random>
#include <ctime>

const int INF = std::numeric_limits<int>::max();

class Maze {
public:
    std::vector<std::vector<char>> grid;
    int rows, cols;

    Maze(int r, int c) : rows(r), cols(c), grid(r, std::vector<char>(c, '1')) {}

    void generateMaze() {
        std::srand(std::time(nullptr));
        carvePassage(0, 0);
        grid[0][0] = '0'; // Start
        grid[rows - 1][cols - 1] = '0'; // End
    }

    void displayMaze() const {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    void carvePassage(int r, int c) {
        static const std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        std::vector<std::pair<int, int>> shuffled_directions = directions;
        std::random_shuffle(shuffled_directions.begin(), shuffled_directions.end());

        for (const auto &dir : shuffled_directions) {
            int nr = r + dir.first * 2, nc = c + dir.second * 2;
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
    std::vector<std::vector<std::pair<int, int>>> adjList;
    int nodes;

    Graph(int numNodes) : nodes(numNodes) {
        adjList.resize(numNodes);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(nodes, INF);
        dist[start] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto &edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
};

std::vector<int> getPath(const std::vector<int> &dist, const std::vector<int> &prev, int target) {
    std::vector<int> path;
    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
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
            if (maze.grid[i][j] == '1') continue; // Wall
            if (i > 0 && maze.grid[i - 1][j] != '1') graph.addEdge(index(i, j), index(i - 1, j), 1);
            if (i < rows - 1 && maze.grid[i + 1][j] != '1') graph.addEdge(index(i, j), index(i + 1, j), 1);
            if (j > 0 && maze.grid[i][j - 1] != '1') graph.addEdge(index(i, j), index(i, j - 1), 1);
            if (j < cols - 1 && maze.grid[i][j + 1] != '1') graph.addEdge(index(i, j), index(i, j + 1), 1);
        }
    }

    std::vector<int> dist = graph.dijkstra(start);

    if (dist[end] == INF) {
        std::cout << "No path found from start to end." << std::endl;
        return 1;
    }

    std::vector<int> prev(rows * cols, -1);
    std::vector<int> path = getPath(dist, prev, end);

    std::cout << "Shortest path from start to end:" << std::endl;
    for (int node : path) {
        int row = node / cols;
        int col = node % cols;
        std::cout << "(" << row << ", " << col << ") ";
    }
    std::cout << std::endl;

    return 0;
}
