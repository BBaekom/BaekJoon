#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int beadsNum[n]; // 구슬이 담긴 배열
    int left = 0; // 그룹의 개수가 N일 때, 가장 큰 수
    int right = 0; // 그룹의 개수가 1일 때, 가장 큰수 = N개 수의 합
    int result = 100000;
    for (int i = 0; i < n; i++) {
        cin >> beadsNum[i];
        right += beadsNum[i];
        if (left < beadsNum[i]) left = beadsNum[i];
    }

    // result 구하기
    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 1;
        int sum = 0, groupNum = 0;
        bool isNotOK = false;
        for (int i = 0; i < n; i++) {
            // 이진 탐색
            if (mid < beadsNum[i]) {
                left = mid + 1;
                isNotOK = true;
                break;
            }
            //정상 실행일 때
            sum += beadsNum[i];
            if (sum > mid) {
                count++;
                sum = beadsNum[i];
            }
        }

        if (isNotOK) continue;
        if (count > m) { 
            left = mid + 1; 
        } else {
            right = mid - 1;
            if (result > mid) {
                result = mid; // 최댓값들 중에서 최소 찾기
            } 
        }
    }

    cout << result << '\n';

    // 그룹 당 포함하는 원소 개수 구하기
    int sum2 = 0, count2 = 0, maxCount = m;
    for (int i = 0; i < n; i++) {
        sum2 += beadsNum[i];
        if (sum2 > result || maxCount > n - i) {
            cout << count2 << " ";
            sum2 = beadsNum[i];
            count2 = 0;
            maxCount--;
        }
        count2++;
    }
    cout << count2 << " ";

    return 0;
}