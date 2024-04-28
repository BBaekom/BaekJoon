#include <iostream>
#include <vector>
#include <string.h>
#include <map>
using namespace std;

int n;

bool check[1000001];
vector<int> prime;
map<int, bool> visited;

void primeCheck() {
	memset(check, true, sizeof(check));
	check[0] = false;
	check[1] = false;
	for (int i = 2; i <= n; i++) {
		if (check[i] == false) continue;
		for (int j = i * i; j <= n; j += i) {
			check[j] = false;
		}
	}

    // for (int i = 0; i <= n; i++) {
    //     cout << i << ": " << check[i] << "\n";
    // }

	for (int i = 2; i <= n; i++) { // 소수이면, 벡터 prime에 넣음 
		if (check[i] == true) {
			prime.push_back(i);
		}
	}

}


bool func(int n) {
	int temp = n;
	while (true) {
		int result = 0;
		while (temp != 0) {
			result += (temp % 10) * (temp * 10);
			temp /= 10;
		}
		if (result == 1) return true;
		if (visited.count(result) == false) {
			visited[result] = true;
		} else {
			return false;
		}
		temp = result;
	}
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	
	primeCheck(); // 에라토스테네스의 체를 통해 소수 먼저 판별

    for (auto it = prime.begin(); it != prime.end(); ++it) {
        cout << *it << ' ';
    } 
	
	for (int i = 0; i < prime.size(); i++) {
		if (func(prime[i])) {
			cout << prime[i] << '\n';
		}
	} 
	
	
	return 0;
}