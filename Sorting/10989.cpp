#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, tmp;
    cin >> N;
    int arr[10001] = {0};

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        arr[num] += 1;
    }

    for (int i=1; i<10001;i++) {
        while(arr[i] != 0) {
            cout << i << '\n';
            arr[i]--;
        } 
    }

    return 0;
}