#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<pair<int, int>> road[10001];
long long minTimes[10001][21]; // [도시 수][포장 도로 수]
priority_queue<pair<long long, pair<int , int>>> pq;

long long dijkstra(int st) {
    minTimes[st][0] = 0;
    pq.push(make_pair(0, make_pair(st, 0)));
    while(!pq.empty()) {
        long long currCost = -pq.top().first;
        int curNode = pq.top().second.first;
        int paveCount = pq.top().second.second;
        pq.pop();

        if (currCost > minTimes[curNode][paveCount]) {
            continue;
        }

        for (auto &edge: road[curNode]) {
            int next = edge.first;
            long long nextCost = currCost + edge.second;


            if (paveCount < k) {
                if (minTimes[next][paveCount+1] == LLONG_MAX) {
                    minTimes[next][paveCount+1] = currCost;
                    pq.push(make_pair(-currCost, make_pair(next, paveCount+1)));
                }
                if (minTimes[next][paveCount+1] > currCost){
                    minTimes[next][paveCount+1] = currCost;
                    pq.push(make_pair(-currCost, make_pair(next, paveCount+1)));
                }
            }
            if (nextCost < minTimes[next][paveCount] || minTimes[next][paveCount] == LLONG_MAX) {
                minTimes[next][paveCount] = nextCost;
                pq.push(make_pair(-nextCost, make_pair(next, paveCount)));
            }
        }
    }
    long long minimum = LLONG_MAX;
    for (int i = 1; i <= k; i++) {
        if (minimum > minTimes[n][i] && minTimes[n][i] != LLONG_MAX) {
            minimum = minTimes[n][i];
        }
    }
    return minimum;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int v1, v2, t;
        cin >> v1 >> v2 >> t;
        road[v1].push_back(make_pair(v2, t));
        road[v2].push_back(make_pair(v1, t));
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 21; j++) {
            minTimes[i][j] = LLONG_MAX;
        }
    }

    long long result = dijkstra(1);
    
    cout << result << "\n";
    
    return 0;
}