#include <bits/stdc++.h>
using namespace std;
#define MAX 100001

int N, M, x, y, w;
int parent[MAX];
long long total, result;
int setNum[MAX];
int mod = 1e9;

vector<pair<pair<int, int>, int>> edge;

bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    return a.second > b.second;
}

int find(int x) {
    if (x == parent[x]) {
        return x;
    }
    parent[x] = find(parent[x]);
    return parent[x];
}

void Union(int pN1, int pN2) {
    parent[pN2] = pN1;
    setNum[pN1] += setNum[pN2];
    setNum[pN2] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;

    for (int i = 0; i <= N; i++) {
        parent[i] = i;
        setNum[i] = 1;
    }

    for (int i = 0; i < M; i++) {
        cin >> x >> y >> w;
        edge.push_back(make_pair(make_pair(x, y), w));
        total += w;
    }

    sort(edge.begin(), edge.end(), compare); // 내림차순 정렬

    for (int i = 0; i < M; i++) {
        int parNum1 = find(edge[i].first.first);
        int parNum2 = find(edge[i].first.second);
        if (parNum1 != parNum2) { // 같으면 모두 합쳐진 것
            result += (total * setNum[parNum1] * setNum[parNum2]) % mod;
            result %= mod;
            Union(parNum1, parNum2);
        }
        total -= edge[i].second;
    }

    cout << result <<'\n';

    return 0;
}