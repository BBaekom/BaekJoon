#include <bits/stdc++.h>
using namespace std;

int N, M;
int arrN[100001];
int arrM[100001][3];

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++) {
		cin >> arrN[i];
	}
	
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 2; j++) {
			cin >> arrM[i][j];
		}
	}
	
	
	for (int i = 2; i <= N; i++) {
		arrN[i] += arrN[i-1];
	}
	
	
	for (int i = 1; i <= M; i++) { // arrM[k][1]부터 arrM[k][2]까지의 합이 출력돼야함. 
		int ni = arrM[i][1];
		int nj = arrM[i][2];
		cout << arrN[nj] - arrN[ni-1] << '\n';
	}
	return 0;
}