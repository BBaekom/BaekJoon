#include <bits/stdc++.h>
using namespace std;
int T, cnt, n;
int dp[15]; // dp[i] => i일 때 1, 2, 3의 합으로 나타내는 방법의 수

int main() {
    // dp[1] = 1;
    // dp[2] -> 1+1, 2
    // dp[3] -> 1+1+1, 1+2, 2+1, 3
    // dp[4] -> 1+1+1+1, 1+1+2, 1+2+1, 2+1+1, 2+2, 1+3, 3+1
    // 1+1+1 +1, 1+2 +1, 2+1 +1, 3 +1 <- dp[3]으로 dp[4]를 만드는 방법 수
    // 1+1 +2, 2 +2 <- dp[2]로 dp[4]를 만드는 방법 수
    // 1 +3 <- dp[1]로 dp[4]를 만드는 방법 수
    // 세 경우를 다 더하면 되기 때문에 dp[i] = dp[i-1] + dp[i-2] + dp[i-3]

    // 초기값 잡기 : dp[1] = 1, dp[2] = 2, dp[3] = 4
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    int result[T];
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 0; i < T; i++) {
        cin >> n;
        for (int j = 4; j <= n; j++) {
            dp[j] = dp[j-1] + dp[j-2] + dp[j-3];
        }
        result[i] = dp[n];
    }

    for (int i = 0; i < T; i++) {
        cout << result[i] <<'\n';
    }
    


    return 0;
}