#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAX 10001
int N, M, S, T;
vector<vector<int>> orig(MAX); // 원래 그래프
vector<vector<int>> scc(MAX); // 인덱스(그룹 number) -> 어떤 노드가 있는지
int node_scc[MAX]; // 각 노드가 어느 그룹에 속하는지
int disc[MAX]; // 인덱스(노드) -> discovery value
int sccNum[MAX];
bool finished[MAX];
int discNum = 1; // discovery value 
int groupCnt; // 속하는 그룹 number
stack<int> node_stack; 

int dfs(int node) {
    disc[node] = discNum++;
    int val = disc[node];
    node_stack.push(node);
    for (int next:orig[node]) {
        if (finished[next]) continue;
        if (disc[next] == 0) {
            val = min(val, dfs(next));
        } else {
            val = min(val, disc[next]);
        }
    }
    if (val == disc[node]) {
        scc.push_back(vector<int>());
        while (true) {
            int target = node_stack.top();
            node_stack.pop();
            node_scc[target] = groupCnt;
            scc[groupCnt].push_back(target);
            sccNum[groupCnt]++;
            finished[target] = true;
            if (target == node) { 
                break; 
            }
        }
        groupCnt++;
    }
    return val;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> S >> T;

    for (int i = 0; i < M; i++) {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        orig[tmp1].push_back(tmp2); // 그래프 형태로 입력받음
    }

    dfs(S);

    int DP[groupCnt];

    DP[groupCnt-1] = sccNum[groupCnt-1];

    for (int i = groupCnt-1; i >= 0; i--) {
        for (int j = 0; j < scc[i].size(); j++) {
            int tmp = scc[i][j];
            for (int k = 0; k < orig[tmp].size(); k++) {
                int next = orig[tmp][k];
                if (node_scc[next]!=i) {
                    DP[node_scc[next]] = max(DP[node_scc[next]], DP[i] + sccNum[node_scc[next]]);
                }
            }
        }
    }


    if (disc[T]) {
        cout << DP[node_scc[T]] << '\n';
    } else {
        cout << 0 << '\n';
    }
    
    return 0;
}