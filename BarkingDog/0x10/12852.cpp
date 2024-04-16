#include <iostream>
using namespace std;
int N;
int dp[1000001]; // d[i] = i를 1로 만들기 위해 필요한 최소 계산 횟수 
int back[1000001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	cin >> N;
	
	dp[1] = 0;
	
	for (int i = 2; i <= N; i++) {
		dp[i] = dp[i-1] + 1;
		back[i] = i - 1; // i번째에 그 전에 계산되었던 인덱스가 저장됨
		if (i % 2 == 0 && dp[i] > dp[i/2]+1) { // back에 넣어주는 조건으로 만족해야하기 때문에 
			dp[i] = dp[i/2] + 1;
			back[i] = i / 2;
		}
		if (i % 3 == 0 && dp[i]> dp[i/3] + 1) {
			dp[i] = dp[i/3] + 1;
			back[i] = i / 3;
		}
	}
	
	cout << dp[N] << '\n';
	int idx = N;
	while (idx != 1) {
		cout << idx << " ";
		idx = back[idx];
	}
	
	cout << idx << '\n';
	
	return 0;
}