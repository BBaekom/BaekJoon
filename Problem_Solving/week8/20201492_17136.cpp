#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int map[10][10];
int paper[] = {0, 5, 5, 5, 5, 5};
int ans = INT_MAX;

void DFS(int x, int y, int cnt);

void attach(int x, int y, int size, int state) {
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            map[i][j] = state;
        }
    }
}

bool isAttach(int x, int y, int size) {
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if (i < 0 || i >= 10 || j < 0 || j >= 10) {
                return false;
            }

            if (map[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> map[i][j];
        }
    }

    DFS(0, 0, 0);

    if (ans == INT_MAX) {
        ans = -1;
    }

    cout << ans << "\n";

    return 0;
}

void DFS(int x, int y, int cnt) {
    if (x >= 9 && y > 9) {
        ans = min(ans, cnt);
        return;
    }

    if (ans <= cnt) {
        return;
    }

    if (y > 9) {
        DFS(x + 1, 0, cnt);
        return;
    }

    if (map[x][y] == 1) {
        for (int i = 5; i >= 1; i--) {
            if (paper[i] > 0 && isAttach(x, y, i)) {
                attach(x, y, i, 0); 
                paper[i]--;
                DFS(x, y + 1, cnt + 1);
                attach(x, y, i, 1);
                paper[i]++;
            }
        }
    } else { 
        DFS(x, y + 1, cnt);
    }
}
