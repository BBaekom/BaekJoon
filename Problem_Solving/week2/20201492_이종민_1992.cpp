#include <iostream>
#include <vector>
using namespace std;

void compress_BWImage(vector<vector<char>>& bwImage, int x, int y, int N) {
    bool all_zero_one = true;
    // 탐색
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (bwImage[x][y] != bwImage[x+i][y+j]) {
                all_zero_one = false;
                break;
            }
        }
        if (all_zero_one == false) break;
    }

    if (all_zero_one == true) {
        cout << bwImage[x][y];
    } else {

        cout << '(';

        compress_BWImage(bwImage, x, y, N/2);
        compress_BWImage(bwImage, x, y+N/2, N/2);
        compress_BWImage(bwImage, x+N/2, y, N/2);
        compress_BWImage(bwImage, x+N/2, y+N/2, N/2);

        cout << ')';
    }
    
}

int main() {
    int N;
    cin >> N;

    vector<string> strArr(N);

    for (int i = 0; i < N; i++) {
        cin >> strArr[i];
    }

    vector<vector<char>> bwImage(N, vector<char>());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < strArr[i].size(); j++) {
            bwImage[i].push_back(strArr[i][j]);
        }
    }

    compress_BWImage(bwImage, 0, 0, N);


    return 0;
}