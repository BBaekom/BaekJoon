#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
using namespace std;

int candy[10001];
long long dp[500001];
bool check[500001]; //소수인지 체크하는 배열
int n, zeroCnt, maxPrice;
long long sum;
vector<int> price;

void primeDef() {
    memset(check, true, sizeof(check));
    check[0] = false;
    check[1] = false;
    for (long long i = 2; i <= sum; i++) {
        if (check[i] == false) continue;
        for (long long j = i * i;  j <= sum; j += i) {
            check[j] = false;
        }
    }
}


long long solve() {
    // sum에서 부터 탑 다운 방식으로 dp적용 dp[n] += dp[n - 가격 * 개수]
    // 가격 -> 가격을 담는 배열, 개수 ->candy 필요함.
    long long result = 0;
    
    dp[0] = 1;
    int num = (int)price.size();

    for (int s = 0; s < num; s++) {
        int p = price[s];
        for (long long i = sum; i >= 0; i--) {
            for (int j = 1; j <= candy[p]; j++) { // 개수
                if (i < j * p) { break; } 
                dp[i] += dp[i - j * p];
            }
        }
    }

    primeDef();

    for (long long i = 0; i <= sum; i++) {
        if (check[i] == false) { continue; }
        result += dp[i];
    }

    result = result * (zeroCnt + 1);

    return result;
}

int main() {
    cin >> n;
    zeroCnt = 0;
    sum = 0;
    maxPrice = 0;

    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (tmp == 0) {
            zeroCnt++;
            continue;
        }
        candy[tmp]++;
        sum += tmp;
        if (maxPrice < tmp) { maxPrice = tmp; }
    }

    for (int i = 0; i <= maxPrice; i++) {
        if (candy[i] != 0) {
            // 사탕 종류별로 다 들어가있음(중복도) <- 사실상 0이 아닌 tmp를 저장한 것
            price.push_back(i); 
        }
    }   


    long long result = solve();

    cout << result;

    return 0;
}