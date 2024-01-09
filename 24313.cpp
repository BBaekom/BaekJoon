#include <iostream>
using namespace std;

int f(int n, int a1, int a0) {
    return a1 * n + a0;
}

int g(int n) {
    return n;
}

int decide(int n0, int a1, int a0, int c) {
    for (n0; n0 <= 100; n0++) {
        if (f(n0, a1, a0) > c * g(n0)) {
            return 0;
        }
    }
    return 1;
}


int main() {
    int a1, a0;
    cin >> a1 >> a0;

    int c;
    cin >> c;
    
    int n0;
    cin >> n0;

    int decidedNum = decide(n0, a1, a0, c);

    cout << decidedNum << endl;

    return 0;
}