#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> original, sorted;

    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        original.push_back(tmp);
        sorted.push_back(tmp);
    }

    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    for (int i = 0; i < N; i++) {
        // cout << lower_bound(sorted.begin(), sorted.end(), original[i]) - sorted.begin() << " ";
        auto it = lower_bound(sorted.begin(), sorted.end(), original[i]);
        cout << distance(sorted.begin(), it) << " ";
    }

    return 0;
}