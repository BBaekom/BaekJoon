#include <iostream>
#include <queue>
using namespace std;

int board[102];
bool visited[102];

void game(int x, int c) {
    queue<pair<int, int>> q;
    q.push(make_pair(x, c));
    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        for (int i = 1; i <= 6; i++) {
            int nextx = cur + i;
            if (nextx == 100) {
                cout << cnt + 1;
                return;
            } else if (nextx < 100) {
                while(board[nextx] != 0) {
                    nextx = board[nextx];
                }
                if (!visited[nextx]) {
                    q.push(make_pair(nextx, cnt+1));
                    visited[nextx] = true;
                } 
            }
        }
    }
}

int main() {
    int N, M;
    int tmp1, tmp2;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> tmp1 >> tmp2;
        board[tmp1] = tmp2;
    }

    for (int i = 0; i < M; i++) {
        cin >> tmp1 >> tmp2;
        board[tmp1] >> tmp2;
    }

    game(1, 0);
    
    return 0;
}