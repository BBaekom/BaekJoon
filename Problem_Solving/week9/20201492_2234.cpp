#include <iostream>
#include <algorithm>
#include <cstring> 
using namespace std;

int N, M;
int map[50][50];
bool visited[50][50];
int max_result = 1;

int dy[] = {0, -1, 0, 1};
int dx[] = {-1, 0, 1, 0};
int wall[] = {1, 2, 4, 8};

bool compare(int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < M;
}

int dfs(int y, int x) {
    visited[y][x] = true;
    int cnt = 0;
    int wallValue = map[y][x];
    for (int next = 0; next < 4; next++) {
        int temp; 
        temp = wallValue % 2; 
        wallValue /= 2;
        if (temp == 0) {
            int ty = y + dy[next];
            int tx = x + dx[next];
            if (compare(ty, tx) && !visited[ty][tx]) {
                cnt += dfs(ty, tx);
            }
        }
    }
    return cnt + 1;
}

int dfs_all() {
    memset(visited, false, sizeof(visited));
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                max_result = max(max_result, dfs(i, j));
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    
    cout << dfs_all() << '\n';
    cout << max_result << '\n';
    max_result = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int b = 0; b < 4; b++) {
                if (map[i][j] - wall[b] >= 0) {
                    map[i][j] -= wall[b];
                    dfs_all();
                    map[i][j] += wall[b];
                }
            }
        }
    }
    
    cout << max_result << '\n';

    return 0;
}
