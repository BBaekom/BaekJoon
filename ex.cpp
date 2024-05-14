#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int N, M;
int map[1001][1001];
bool visited[1001][1001];

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool compare(int x, int y) {
    return x > 0 && x <= N && y > 0 && y <= M;
}

int bfs(int ni, int nj) {
    queue<pair<int, int>> q;
    q.push(make_pair(ni, nj));
    visited[ni][nj] = true;
    int cnt = 1;
    while (!q.empty()) {
        int tmpx = q.front().first;
        int tmpy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = tmpx + dx[i];
            int y = tmpy + dy[i];
            if (compare(x, y) && map[x][y] == 0 && visited[x][y] == false) {
                visited[x][y] = true;
                q.push(make_pair(x, y));
                cnt++;
            }
        }
    }
    
    return cnt;
}

void bfs_all() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 1) {
                memset(visited, false, sizeof(visited));
                map[i][j] = bfs(i, j);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << map[i][j] % 10;
        }
        cout << "\n";
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        string temp;
        cin >> temp;
        for (int j = 1; j <= M; j++) {
            map[i][j] = temp[j-1] - '0';
        }
    }

    bfs_all();

    return 0;
}