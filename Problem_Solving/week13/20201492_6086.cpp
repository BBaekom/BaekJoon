#include <bits/stdc++.h>
#define MAX 53
using namespace std;

int N;
int INF = 1e9;
int c[MAX][MAX];
int f[MAX][MAX];
int d[MAX];

vector<int> nodes[MAX];

char char_to_int(char c) {
    if (c >= 'A' && c <= 'Z') { // A~Z : 0~25
        return c - 'A';
    }
    return c - 'a' + 26; // a~z : 26~51
}

int maxFlow(int start, int end) {
    int result = 0;
    while (true) {
        fill(d, d + MAX, -1);
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0 ; i < nodes[x].size(); i++) {
                int y = nodes[x][i];
                if (c[x][y] - f[x][y] > 0 && d[y] == -1) {
                    q.push(y);
                    d[y] = x; // 경로를 기억함.
                    if (y == end) { break; }
                }
            }
        }

        if (d[end] == -1) { break; }

        int flow = INF;
        for (int i = end; i != start; i = d[i]) {
            flow = min(flow, c[d[i]][i] - f[d[i]][i]);
        }
        for (int i = end; i != start; i = d[i]) {
            f[d[i]][i] += flow;
            f[i][d[i]] -= flow;
        }
        result += flow;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    char a, b;
    int F;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> a >> b >> F;

        int tmp1 = char_to_int(a);
        int tmp2 = char_to_int(b);

        c[tmp1][tmp2] += F;
        c[tmp2][tmp1] += F;

        nodes[tmp1].push_back(tmp2);
        nodes[tmp2].push_back(tmp1);
    }


    cout << maxFlow(char_to_int('A'), char_to_int('Z')) << '\n';

    return 0;
}