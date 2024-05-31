#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct State {
    int x, y, dir, turns, time;
};

const int MAX_N = 20;
const int MAX_M = 20;
const int MAX_K = 20;

const int dx[] = { 0, 1, 0, -1 }; // направления: север, восток, юг, запад
const int dy[] = { -1, 0, 1, 0 }; // направления: север, восток, юг, запад

bool isValid(int x, int y, int N, int M, int grid[MAX_N][MAX_M]) {
    return x >= 0 && x < N && y >= 0 && y < M && grid[x][y] != 1;
}

int minTimeToDestination(int N, int M, int grid[MAX_N][MAX_M], int K) {
    int startX, startY, endX, endY;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 2) {
                startX = i;
                startY = j;
            }
            else if (grid[i][j] == 3) {
                endX = i;
                endY = j;
            }
        }
    }

    queue<State> q;
    bool visited[MAX_N][MAX_M][4][MAX_K + 1] = { false };
    for (int d = 0; d < 4; ++d) {
        q.push({ startX, startY, d, K, 0 });
        visited[startX][startY][d][K] = true;
    }

    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        int x = cur.x, y = cur.y, dir = cur.dir, turns = cur.turns, time = cur.time;

        if (x == endX && y == endY) {
            return time;
        }

        for (int d = -1; d <= 1; ++d) {
            int newDir = (dir + d + 4) % 4;
            int newX = x + dx[newDir];
            int newY = y + dy[newDir];
            int newTurns = turns - (d == 1 ? 1 : 0);

            if (isValid(newX, newY, N, M, grid) && newTurns >= 0 && !visited[newX][newY][newDir][newTurns]) {
                visited[newX][newY][newDir][newTurns] = true;
                q.push({ newX, newY, newDir, newTurns, time + 1 });
            }
        }
    }

    return -1;
}

int main() {
    ifstream inputFile("INPUT.txt");
    ofstream outputFile("OUTPUT.txt");
    int N, M, K;
    inputFile >> N >> M;
    int grid[MAX_N][MAX_M];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            inputFile >> grid[i][j];
        }
    }
    inputFile >> K;

    int result = minTimeToDestination(N, M, grid, K);
    outputFile << result << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
