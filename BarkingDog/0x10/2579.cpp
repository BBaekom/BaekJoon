#include <bits/stdc++.h>
using namespace std;
int n; // 계단의 수 300 이하의 자연수
int dp[305][3]; 
// dp[i][j] => 현재까지 j개의 계단을 연속해서 밟고 i번째 계단까지 올라섰을 때 점수 합의 최댓값. 
//단 i번째 계단은 반드시 밟아야함.
int stair[305];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> stair[i];
    }

    dp[1][1] = stair[1];
    dp[2][1] = stair[2];
    dp[2][2] = stair[1] + stair[2];

    for (int i = 3; i <= n; i++) {
        dp[i][1] = stair[i] + max(dp[i-2][1], dp[i-2][2]);
        dp[i][2] = stair[i] + dp[i-1][1];
    }

    cout << max(dp[n][1], dp[n][2]) << '\n';

    return 0;
}