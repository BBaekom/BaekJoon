#include <iostream>
using namespace std;
int T;

int dp[41][2]; // dp[i][0] = i번째까지 왔을 때 0을 호출한 횟수 , dp[i][1] = i번째까지 왔을 때 1을 호출한 횟수

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	int arrN[T+1];
	for (int i = 1; i <= T; i++) {
		cin >> arrN[i];
	}
	
	dp[0][0] = 1;
	dp[1][1] = 1;
	
	for (int i = 1; i <= T; i++) {
		if (arrN[i] == 0) {
			cout << 1 << " " << 0 << '\n';
			continue;
		}
		if (arrN[i] == 1) {
			cout << 0 << " " << 1 << '\n';
			continue;
		}
		for (int j = 2; j <= arrN[i]; j++) {
			dp[j][0] = dp[j-1][0] + dp[j-2][0];
			dp[j][1] = dp[j-1][1] + dp[j-2][1];
		}
		cout << dp[arrN[i]][0] << " " << dp[arrN[i]][1] << "\n";
	}
	
	
	
	return 0;
}