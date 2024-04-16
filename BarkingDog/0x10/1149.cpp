#include <bits/stdc++.h>
using namespace std;
int N; // 집의 수
int price[1001][4];
int dp[1001][4];

int main() {
    cin >> N;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 3; j++) {
            cin >> price[i][j];
            // cout << price[i][j] << " ";
        }
        // cout << '\n';
    }

    dp[1][1] = price[1][1];
    dp[1][2] = price[1][2];
    dp[1][3] = price[1][3];

    for (int i = 2; i <= N; i++) {
        dp[i][1] = min(dp[i-1][2], dp[i-1][3]) + price[i][1];
        dp[i][2] = min(dp[i-1][1], dp[i-1][3]) + price[i][2];
        dp[i][3] = min(dp[i-1][1], dp[i-1][2]) + price[i][3];
    }

    int result = dp[N][1];
    for (int i = 1; i <= 3; i++) {
        if (result > dp[N][i]) {
            result = dp[N][i];
        }
    }

    cout << result << '\n';

    return 0;
}