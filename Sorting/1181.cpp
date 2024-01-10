#include <iostream>
#include <algorithm>
using namespace std;

bool compare (string a, string b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    } else {
        return a < b;
    }
}

int main() {
    int N;
    cin >> N; // 단어의 개수

    string arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sort(arr, arr+N, compare);

    for (int i = 0; i < N; i++) {
        if (i == N-1) {
            cout << arr[N-1] << '\n';
            break;
        }
        if (arr[i].compare(arr[i+1])) {
            cout << arr[i] << '\n';
        }
    }

    return 0;
}