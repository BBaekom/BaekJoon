#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
int N, M;
int MAP[1001][1001];
int mapAreaNum[1001][1001];
bool visited[1001][1001];
map<int, int> m;
int areaNum = 0;
vector<int> v;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool compare(int x, int y) {
    return x > 0 && x <= N && y > 0 && y <= M;
}

int bfs(int ni, int nj) {
    queue<pair<int, int>> q;
    q.push(make_pair(ni, nj));
    visited[ni][nj] = true;
    mapAreaNum[ni][nj] = areaNum;
    int cnt = 1;
    while (!q.empty()) {
        int tmpx = q.front().first;
        int tmpy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = tmpx + dx[i];
            int y = tmpy + dy[i];
            if (compare(x, y) && MAP[x][y] == 0 && visited[x][y] == false) {
                visited[x][y] = true;
                q.push(make_pair(x, y));
                cnt++;
                mapAreaNum[x][y] = areaNum;
            }
        }
    }
    return cnt;
}

void bfs_all() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (MAP[i][j] == 0 && visited[i][j] == false) {
                m.insert({areaNum, bfs(i, j)});
                areaNum++;
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (MAP[i][j] == 1) {
                v.clear();
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (compare(x, y) && MAP[x][y] == 0) {
                        v.push_back(mapAreaNum[x][y]);
                    }
                }

                sort(v.begin(), v.end());
                
                int before = -1;
                for (int k = 0; k < v.size(); k++) {
                    if (before != v[k]) {
                        MAP[i][j] += m[v[k]];
                    }
                    before = v[k];
                }
            }
        }
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        string temp;
        cin >> temp;
        for (int j = 1; j <= M; j++) {
            MAP[i][j] = temp[j-1] - '0';
        }
    }

    memset(mapAreaNum, -1, sizeof(mapAreaNum));

    bfs_all();

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << MAP[i][j] % 10;
        }
        cout << "\n";
    }

    return 0;
}