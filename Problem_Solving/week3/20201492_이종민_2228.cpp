#include <iostream>
#include <algorithm>
using namespace std;

int DP(int n, int m, int array[101], int dp[101][51]) {
    if (m == 0) { return 0; }
    if (n <= 0) { return -1000000; }
    if (dp[n][m] != -1) { return dp[n][m]; }
    
    int sum = 0;
    dp[n][m] = DP(n-1, m, array, dp);
    for (int i = n; i > 0; i--) {
        int tmp = 0;
        sum += array[i];
        tmp =  DP(i-2, m-1, array, dp) + sum;
        dp[n][m] = max(dp[n][m], tmp);
    }

    return dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    int array[101] = {0}, dp[101][51] = {0};
    for (int i = 1; i <= n; i++) {
        cin >> array[i];
    }

    fill(&dp[0][0], &dp[0][0] + 101 * 51, -1);

    int result = DP(n, m, array, dp);

    cout << result;
    return 0;
}