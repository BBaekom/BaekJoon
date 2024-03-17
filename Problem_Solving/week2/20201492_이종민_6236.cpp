#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int usingMoney[n] = {0};
    int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> usingMoney[i];
        sum += usingMoney[i];
    }

    int k; // 이분탐색으로 구해야 하는 것
    int left = 1, right = sum;
    while (left <= right) {
        int count = 1;
        bool isNotOk = false;
        int mid = (left + right) / 2;  // 출금금액
        int restMoney = mid; // 남은 금액
        for (int i = 0; i < n; i++) {
            if (mid < usingMoney[i]) {
                isNotOk = true;
                left = mid + 1;
                break;
            }
            if (restMoney < usingMoney[i]) {
                restMoney = mid;
                count++;
            }
            restMoney -= usingMoney[i];
        }

        if (isNotOk) continue;

        if (count > m) {
            left = mid + 1;
        } else {
            right = mid - 1;
            k = mid;
        }
    }

    cout << k << '\n';


    return 0;
}