#include <iostream>
#include <vector>
#include <queue>


using namespace std;

// Define the state representation for the maze
struct State {
    int x, y; // Coordinates in the maze

    // Constructor
    State(int x, int y) : x(x), y(y) {}
};
// Maze size
const int rows = 5;
const int cols = 5;

// Maze represented by a 2D grid
int maze[rows][cols] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0}
};

// Goal coordinates
int goalX;
int goalY;

// Define a comparison function for the priority queue
struct CompareStates {
    bool operator()( State& a, State& b)  {
        // Use a simple Manhattan distance as the heuristic
        return (abs(a.x - goalX) + abs(a.y - goalY)) > (abs(b.x - goalX) + abs(b.y - goalY));
    }
};



// Greedy Best-First Search Algorithm
void greedyBestFirstSearch(State& startState) {
    priority_queue<State, vector<State>, CompareStates> pq;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    pq.push(startState);

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        // Check if the current state is the goal state
        if (current.x == goalX && current.y == goalY) {
            cout << "Goal reached! Path found." << endl;
            return;
        }
        // Expand the current state and enqueue its successors
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = current.x + dx;
                int newY = current.y + dy;
                cout << "I am visiting': (" << current.x << "," << current.y << ")" << endl;

                // Check if the new coordinates are within the maze boundaries
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] == 0 && !visited[newX][newY]) {
                    pq.push(State(newX, newY));
                    visited[newX][newY] = true;
                    cout <<  newX << "," << newY << ") are within the maze boundaries"<< endl;
                }
            }
        }
    }

    // If the queue becomes empty and goal state is not reached, no solution is found
    cout << "No solution found." << endl;
}

int main() {
    // Start coordinates
    cout << "Enter start coordinates"<< endl;
    int sx, sy;
    cin >> sx >> sy;
    State startState(sx, sy);

    //Goal coordinates
    cout << "Enter goal coordinates"<< endl;
    int golx, goly;
    cin>> golx >> goly;
        goalX = golx;
        goalY = goly;

    // Perform Greedy Best-First Search
    greedyBestFirstSearch(startState);

    return 0;
}
