#include <iostream>
#include <vector>
#include <algorithm> // std::max

using namespace std;

int N, M;
vector<vector<int>> MAP;
vector<vector<bool>> VISIT;
int MAX = 1;

// {서 북 동 남}의 상대적 위치
int dy[] = {0, -1, 0, 1};
int dx[] = {-1, 0, 1, 0};
int wall[] = {1, 2, 4, 8};

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

// 방의 넓이 반환
int DFS(int y, int x) {
    VISIT[y][x] = true;
    int cnt = 0;
    int wallValue = MAP[y][x];
    for (int next = 0; next < 4; next++) {
        int r = wallValue % 2; wallValue /= 2;
        if (r == 0) {
            int ty = y + dy[next], tx = x + dx[next];
            if (inRange(ty, tx) && !VISIT[ty][tx]) {
                cnt += DFS(ty, tx);
            }
        }
    }
    return 1 + cnt;
}

// 방의 개수 반환
int DFSAll() {
    VISIT.assign(N, vector<bool>(M, false));
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!VISIT[i][j]) {
                MAX = max(MAX, DFS(i, j));
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
    MAP.assign(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
        }
    }
    
    cout << DFSAll() << '\n';
    cout << MAX << '\n';
    MAX = 1;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 서 북 동 남순으로 벽을 부술 수 있으면 하나 씩 부수면서 시도
            for (int b = 0; b < 4; b++) {
                if (MAP[i][j] - wall[b] >= 0) {
                    MAP[i][j] -= wall[b];
                    DFSAll();
                    MAP[i][j] += wall[b];
                }
            }
        }
    }
    
    cout << MAX << '\n';

    return 0;
}
