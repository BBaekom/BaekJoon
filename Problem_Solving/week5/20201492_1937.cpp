#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int n;
int x, y;
int largest_move;
int bamboo[502][502];
int dp[502][502];

int panda(int dpi, int dpj) {
    if (dp[dpi][dpj] != 0) {
        return dp[dpi][dpj];
    }
    dp[dpi][dpj] = 1;
    for (int i = 0; i < 4; i++) {
        if (i == 0) { // 상
            if (bamboo[dpi][dpj] < bamboo[dpi-1][dpj]) {
                dp[dpi][dpj] = max(dp[dpi][dpj], panda(dpi-1, dpj) + 1);
            }
        } else if (i == 1) { // 하
            if (bamboo[dpi][dpj] < bamboo[dpi+1][dpj]) {
                dp[dpi][dpj] = max(dp[dpi][dpj], panda(dpi+1, dpj) + 1);
            }
        } else if (i == 2) { // 좌
            if (bamboo[dpi][dpj] < bamboo[dpi][dpj-1]) {
                dp[dpi][dpj] = max(dp[dpi][dpj], panda(dpi, dpj-1) + 1);
            }
        } else { // 우
            if (bamboo[dpi][dpj] < bamboo[dpi][dpj+1]) {
                dp[dpi][dpj] = max(dp[dpi][dpj], panda(dpi, dpj+1) + 1);
            }
        }
    }

    return dp[dpi][dpj];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> bamboo[i][j];
        }
    }

    largest_move = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            largest_move = max(largest_move, panda(i, j));
        }
    }

    cout << largest_move << '\n';


    return 0;
}   