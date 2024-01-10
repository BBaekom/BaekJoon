#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct coordinate {
    int x;
    int y;
};

bool compare(coordinate a, coordinate b) {
    if (a.x == b.x) {
        return a.y < b.y;
    } else {
        return a.x < b.x;
    }
}

int main() {

    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    int N;
    cin >> N; // 점의 개수

    coordinate arr[N];

    for (int i = 0; i < N; i++) {
        cin >> arr[i].x >> arr[i].y;
    }

    sort (arr, arr + N, compare);

    for (int i = 0; i < N; i++) {
        cout << arr[i].x << " " << arr[i].y << '\n';
    }

    return 0;
}