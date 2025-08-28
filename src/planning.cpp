#include "planning.h"
#include <cmath>
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

struct Node {
    int x, y;
    double f, g, h;
    Node *parent;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f; // min-heap based on f score
    }
};

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid) {
    rows = grid.size();
    cols = grid[0].size();
}

bool Planner::isvalid(int x, int y) const {
    return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}

double Planner::heuristic(int x1, int y1, int x2, int y2) const {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<pair<int, int>> Planner::pathplanning(pair<int, int> start,
                                             pair<int, int> goal) {
    vector<pair<int, int>> path;
    
    // 8 possible moves (N, S, E, W, diagonals)
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

    // Open list (priority queue)
    priority_queue<Node*, vector<Node*>, Compare> openList;

    // Store visited nodes
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    // Start node
    Node* startNode = new Node{start.first, start.second, 0.0, 0.0,
                               heuristic(start.first, start.second, goal.first, goal.second),
                               nullptr};
    startNode->f = startNode->h;
    openList.push(startNode);

    Node* goalNode = nullptr;

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        // Mark as visited
        closed[current->x][current->y] = true;

        // Check goal
        if (current->x == goal.first && current->y == goal.second) {
            goalNode = current;
            break;
        }

        // Explore neighbors
        for (int i = 0; i < 8; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isvalid(nx, ny) || closed[nx][ny])
                continue;

            double g_new = current->g + ((i < 4) ? 1.0 : sqrt(2)); // cost (1 for straight, √2 for diagonal)
            double h_new = heuristic(nx, ny, goal.first, goal.second);
            double f_new = g_new + h_new;

            Node* neighbor = new Node{nx, ny, f_new, g_new, h_new, current};
            openList.push(neighbor);
        }
    }

    // Reconstruct path
    if (goalNode) {
        Node* temp = goalNode;
        while (temp != nullptr) {
            path.push_back({temp->x, temp->y});
            temp = temp->parent;
        }
        reverse(path.begin(), path.end());
    }

    return path;
}
