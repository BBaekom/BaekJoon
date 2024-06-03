#include <bits/stdc++.h>

using namespace std;

int R, C;
vector<string> parking_lot;
vector<pair<int, int>> cars;
vector<pair<int, int>> parks;
int dist[51][51];
int matching[101];
bool visited[101];
int car_to_park_dist[101][101];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool compare(int x, int y) {
    return x >= 0 && x < R && y >= 0 && y < C;
}

void bfs(int sx, int sy, int car_idx) {
    for (int i = 0; i < 51; i++) {
        fill(dist[i], dist[i] + 51, -1);
    }
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;
    
    while (!q.empty()) {
        int x, y;
        x = q.front().first;
        y = q.front().second;
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (compare(nx, ny) && parking_lot[nx][ny] != 'X' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    
    for (int i = 0; i < parks.size(); i++) {
        int px = parks[i].first;
        int py = parks[i].second;
        car_to_park_dist[car_idx][i] = dist[px][py];
    }
}

bool can_match(int car, int limit, vector<vector<int>>& v) {
    for (int park : v[car]) {
        if (visited[park]) { 
            continue; 
        }
        visited[park] = true;
        if (matching[park] == -1 || can_match(matching[park], limit, v)) {
            matching[park] = car;
            return true;
        }
    }
    return false;
}

bool check(int limit, vector<vector<int>>& v) {
    fill(matching, matching + parks.size(), -1);
    for (int car = 0; car < cars.size(); car++) {
        fill(visited, visited + parks.size(), false);
        if (!can_match(car, limit, v)) { 
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> R >> C;
    parking_lot.resize(R);
    for (int i = 0; i < R; i++) {
        cin >> parking_lot[i];
        for (int j = 0; j < C; j++) {
            if (parking_lot[i][j] == 'C') {
                cars.push_back(make_pair(i, j));
            }
            if (parking_lot[i][j] == 'P') {
                parks.push_back(make_pair(i, j));
            }
        }
    }

    if (cars.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 0; i < cars.size(); i++) {
        bfs(cars[i].first, cars[i].second, i);
    }

    vector<vector<int>> adj(cars.size());
    
    for (int i = 0; i < cars.size(); i++) {
        for (int j = 0; j < parks.size(); j++) {
            if (car_to_park_dist[i][j] != -1) {
                adj[i].push_back(j);
            }
        }
    }

    int left = 0; 
    int right = R * C;
    int result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        vector<vector<int>> limited_adj(cars.size());
        for (int i = 0; i < cars.size(); i++) {
            for (int j : adj[i]) {
                if (car_to_park_dist[i][j] <= mid) {
                    limited_adj[i].push_back(j);
                }
            }
        }

        if (check(mid, limited_adj)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << result << '\n';
    return 0;
}
