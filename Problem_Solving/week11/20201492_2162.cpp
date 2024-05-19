#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 3001
using namespace std;

int N, ix1, iy1, ix2, iy2;
pair<pair<int, int>, pair<int, int>> line[MAX];
int groupNum[MAX];
int longest;
int gNum;
int parent[MAX];

int find(int x) {
    if (x == parent[x]) {
        return x;
    }
    parent[x] = find(parent[x]);
    return parent[x];
}

void Union(int pN1, int pN2) {
    pN1 = find(pN1);
    pN2 = find(pN2);
    if (pN1 < pN2) {
        parent[pN2] = pN1;
    } else {
        parent[pN1] = pN2;
    }
}

int ccw(pair<int, int>p1, pair<int, int>p2, pair<int, int>p3) {
    long long s = (long long)(p1.first * p2.second + p2.first * p3.second + p3.first * p1.second) - (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);

    if (s > 0) { return 1; }
    else if (s == 0) { return 0; }
    else { return -1; } 
}

bool isIntersect(pair<pair<int, int>, pair<int, int>> l1, pair<pair<int, int>, pair<int, int>> l2) {
    if (ccw(l1.first, l1.second, l2.first)*ccw(l1.first, l1.second, l2.second) <= 0 && 
        ccw(l2.first, l2.second, l1.first)*ccw(l2.first, l2.second, l1.second) <= 0) {
        int x1 = l1.first.first; int y1 = l1.first.second; int x2 = l1.second.first; int y2 = l1.second.second;
        int x3 = l2.first.first; int y3 = l2.first.second; int x4 = l2.second.first; int y4 = l2.second.second;
        if ((x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) || (x3 > x1 && x3 > x2 && x4 > x1 && x4 > x2)) {
            return false;
        } else if ((y1 > y3 && y1 > y4 && y2 > y3 && y2 > y4) || (y3 > y1 && y3 > y2 && y4 > y1 && y4 > y2)) {
            return false;
        }
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> ix1 >> iy1 >> ix2 >> iy2;
        line[i] = make_pair(make_pair(ix1, iy1), make_pair(ix2, iy2));
        parent[i] = i;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (isIntersect(line[i], line[j])) {
                Union(i, j);
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        groupNum[find(i)]++;
    }

    for (int i = 1; i <= N; i++) {
        if (groupNum[i] != 0) {
            gNum++;
        }
        longest = max(longest, groupNum[i]);
    }

    cout << gNum << '\n';
    cout << longest << '\n';

    return 0;
}