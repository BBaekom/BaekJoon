#include <iostream>
using namespace std;
int n, cnt; // 삼각형의 크기(1<=n<=500)
int dp[501][501]; 
int tri[501][501];                                 

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			cin >> tri[i][j];
		}
	}
	
	dp[1][1] = tri[1][1];
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			dp[i][j] = tri[i][j] + max(dp[i-1][j-1], dp[i-1][j]); 
		}                
	}
	
	int result = dp[n][1];
	for (int i = 1; i <= n; i++) {
		if (result < dp[n][i]) {
			result = dp[n][i];
		}
	}
	
	cout << result << '\n';
		
	return 0;
}