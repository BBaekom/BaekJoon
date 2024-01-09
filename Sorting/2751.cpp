#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int N, tmp;
    cin >> N;
    vector<int> arr;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        arr.push_back(tmp);
    }

    sort(arr.begin(), arr.end());

    for (int i = 0; i < N; i++) {
        cout << arr[i] << '\n';
    }

    return 0;
}