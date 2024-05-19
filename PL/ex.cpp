#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 3001;

typedef struct _Line {
    int x1, y1, x2, y2;
} Line;

int N;
Line line[MAX];
int parent[MAX];
int groupNum[MAX];

int find(int a) {
    if (a == parent[a]) return parent[a];
    return parent[a] = find(parent[a]);
}

void Union(int pN1, int pN2) {
    pN1 = find(pN1);
    pN2 = find(pN2);
    if (pN1 < pN2) {
        parent[pN2] = pN1;
        groupNum[pN1] += groupNum[pN2];
    } else {
        parent[pN1] = pN2;
        groupNum[pN2] += groupNum[pN1];
    }
}

int CCW(int x1, int y1, int x2, int y2, int x3, int y3) {
    long long temp = (x1 * y2 + x2 * y3 + x3 * y1) - (y1 * x2 + y2 * x3 + y3 * x1);
    if (temp < 0) return -1;
    else if (temp > 0) return 1;
    return 0;
}

bool isCross(Line L1, Line L2) {
    int x1 = L1.x1, y1 = L1.y1, x2 = L1.x2, y2 = L1.y2;
    int x3 = L2.x1, y3 = L2.y1, x4 = L2.x2, y4 = L2.y2;

    if (CCW(x1, y1, x2, y2, x3, y3) * CCW(x1, y1, x2, y2, x4, y4) <= 0 &&
        CCW(x3, y3, x4, y4, x1, y1) * CCW(x3, y3, x4, y4, x2, y2) <= 0) {
        if ((x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) ||
            (x3 > x1 && x3 > x2 && x4 > x1 && x4 > x2)) return false;
        else if ((y1 > y3 && y1 > y4 && y2 > y3 && y2 > y4) ||
            (y3 > y1 && y3 > y2 && y4 > y1 && y4 > y2)) return false;
        return true;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> line[i].x1 >> line[i].y1 >> line[i].x2 >> line[i].y2;
        parent[i] = i;
        groupNum[i] = 1;  // 초기 각 집합의 크기는 1
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (isCross(line[i], line[j])) {
                Union(i, j);
            }
        }
    }

    int gCount = 0;
    int Max = 0;
    for (int i = 1; i <= N; i++) {
        if (find(i) == i) {
            gCount++;
            Max = max(Max, groupNum[i]);
        }
    }

    cout << gCount << '\n';
    cout << Max << '\n';

    return 0;
}
