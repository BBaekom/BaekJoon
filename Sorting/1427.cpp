#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N, tmp, digit = 0;
    cin >> N;
    tmp = N;
    while (tmp != 0) {
        tmp /= 10;
        digit++; // N의 자릿수
    }

    int * arr = new int[digit];

    for (int i = 0; i < digit; i++) {
        arr[i] = N % 10;
        N /= 10;
    }


    for (int i = digit-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }

    for (int i = 0; i < digit; i++) {
        cout << arr[i];
    }

    return 0;
}