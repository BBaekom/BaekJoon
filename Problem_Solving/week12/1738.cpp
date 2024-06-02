#include <bits/stdc++.h>
#define MAX 101

using namespace std;

int n, m;
vector<vector<int>> edges;
int dist[MAX];
int pre[MAX];
bool visited[MAX];

void init() {
    edges.resize(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    fill(dist, dist + MAX, INT_MIN);
    fill(pre, pre + MAX, -1);
    dist[1] = 0;
}

void bellmanFord() {
    for (int i = 0; i < n - 1; i++) {
        for (const auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            if (dist[from] == INT_MIN) continue;
            if (dist[to] < dist[from] + weight) {
                dist[to] = dist[from] + weight;
                pre[to] = from;
            }
        }
    }
}

bool isCycle(int from, int to, int weight) {
    return dist[to] < dist[from] + weight;
}

bool bfs(int target) {
    fill(visited, visited + MAX, false);
    queue<int> q;
    q.push(target);
    visited[target] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (const auto& edge : edges) {
            int from = edge[0];
            int to = edge[1];
            if (from == current && !visited[to]) {
                visited[to] = true;
                q.push(to);
            }
        }
    }
    return visited[n];
}

void Print() {
    vector<int> path;
    for (int index = n; index != -1; index = pre[index]) {
        path.push_back(index);
    }
    reverse(path.begin(), path.end());
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    init();
    bellmanFord();

    if (dist[n] == INT_MIN) {
        cout << -1 << endl;
        return 0;
    }

    for (const auto& edge : edges) {
        int from = edge[0];
        int to = edge[1];
        int weight = edge[2];
        if (dist[from] == INT_MIN) continue;
        if (isCycle(from, to, weight) && bfs(to)) {
            cout << -1 << endl;
            return 0;
        }
    }

    Print();
    return 0;
}
