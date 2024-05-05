#include <iostream>
#include <vector>
using namespace std;

int sdk[9][9];
vector<pair<int, int>> zeroC;
bool res;

// 0 일 때, 가로, 세로, 3X3 정사각형 안에 있는 숫자인지 검사해줘야함.
bool check(int seq) {
    for (int i = 0; i < 9; i++) {
        if (sdk[i][zeroC[seq].second] == sdk[zeroC[seq].first][zeroC[seq].second] && i != zeroC[seq].first) {
            return false;
        }
        if (sdk[zeroC[seq].first][i] == sdk[zeroC[seq].first][zeroC[seq].second] && i != zeroC[seq].second) {
            return false;
        }
    }
    int x = (zeroC[seq].first / 3) * 3;
    int y = (zeroC[seq].second / 3) * 3;

    for (int i = x; i < x + 3; i++) {
        for (int j = y; j < y + 3; j++) {
            if (sdk[i][j] == sdk[zeroC[seq].first][zeroC[seq].second] && i != zeroC[seq].first && j != zeroC[seq].second) {
                    return false;
            }
        }
    }
    return true;
}


bool sudoku(int seq) {
    if (seq == zeroC.size()) {
        res = true;
        return res;
    }
    for (int i = 1; i <= 9; i++) {
        sdk[zeroC[seq].first][zeroC[seq].second] = i;
        if (check(seq)) {
            sudoku(seq+1);
        }
        if (res) {
            return true;
        }
    }
    sdk[zeroC[seq].first][zeroC[seq].second] = 0;
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sdk[i][j];
            if (sdk[i][j] == 0) {
                zeroC.push_back(make_pair(i,j)); // 0인 좌표를 저장함
            }
        }
    } 

    // cout << "\n";
    if (sudoku(0)) {
         for(int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << sdk[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}