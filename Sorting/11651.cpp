#include <iostream>
#include <algorithm>
using namespace std;

struct coordinate {
    int x;
    int y;
};

bool compare(coordinate a, coordinate b) {
    if (a.y == b.y) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    int N;
    cin >> N;

    coordinate arr[N];

    for (int i = 0; i < N; i++) {
        cin >> arr[i].x >> arr[i].y;
    }

    sort(arr, arr+N, compare);

    for (int i = 0; i < N; i++) {
        cout << arr[i].x << " " << arr[i].y << '\n';
    }

    return 0;
}