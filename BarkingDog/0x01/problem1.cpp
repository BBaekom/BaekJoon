#include <iostream>
#include <cmath>
using namespace std;

int N;

int func1(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    return sum;
}

int func2(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] + arr[j] == 100) return 1;
        }
    }
    return 0;
}

int func3(int N) {
    int root = sqrt(N);
    if (root * root == N) {
        return 1;
    }
    return 0;
}

int func4(int N) {
    int val = 1;
    while (2 * val <= N) {
        val *= 2;
    }
    return val;
}

int main() {
    cin >> N;
    
    cout << func4(N) << '\n';

}