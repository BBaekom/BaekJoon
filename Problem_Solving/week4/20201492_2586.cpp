#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n; 
int tmp1, tmp2, idx, result = 0, cnt;
int dp[500001];
int LIS[500001];
vector<pair<int, int>> connectedWire;
vector<int> uselessWire;

bool comparePairs(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

int binarySearch(int left, int right, int secondValue) {
    int mid, res = 0;
    while (left <= right) {
        mid = (right - left) / 2 + left;
        if (dp[mid] >= secondValue) {
            res = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    idx = 0; 
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp1 >> tmp2;
        connectedWire.push_back(make_pair(tmp1, tmp2));
    }

    sort(connectedWire.begin(), connectedWire.end(), comparePairs);

    dp[0] = connectedWire[0].second;
    LIS[0] = 0;
    for (int i = 1; i < connectedWire.size(); i++) {
        if (connectedWire[i].second > dp[idx]) {
            dp[idx+1] = connectedWire[i].second;
            idx++;
            LIS[i] = idx;
        } else {
            int lastIndex = binarySearch(0, idx, connectedWire[i].second);
            dp[lastIndex] = connectedWire[i].second;
            LIS[i] = lastIndex;
        }
    }


    result = connectedWire.size() - (idx + 1);

    cout << result << '\n';
    cnt = idx;

    for (int i = connectedWire.size() - 1; i >= 0; i--) {
        if (LIS[i] == cnt) {
            cnt--;
        } else {
            uselessWire.push_back(connectedWire[i].first);
        }
    }

    for (int i = uselessWire.size() - 1; i >= 0; i--) {
        cout << uselessWire[i] << '\n';
    }

    return 0;
}