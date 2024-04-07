#include <iostream>
using namespace std;

int R,C;
char ch;
int n;
int dp[1502][1502];
int appleNum[1502][1502];
int bananaNum[1502][1502];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> R >> C;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> ch >> n;
            if (ch == 'A') {
                appleNum[i][j] = n;
            } else if (ch == 'B'){
                bananaNum[i][j] = n;
            }
        }
    }


    // 누적합 구하기
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            appleNum[i][j] += appleNum[i][j-1];
            bananaNum[i][j] += bananaNum[i][j-1];
        }
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            appleNum[i][j] += appleNum[i-1][j];
            bananaNum[i][j] += bananaNum[i-1][j];
        }
    }



    for (int i = 1; i <= C; i++) {
        dp[1][i] = appleNum[R][i] - appleNum[1][i];
    }
    for (int i = 1; i <= R; i++) {
        dp[i][1] = appleNum[R][1] - appleNum[i][1];
    }


    for (int i = 2; i <= R; i++) {
        for (int j = 2; j <= C; j++) {
            dp[i][j] = max(dp[i][j], dp[i][j-1] + appleNum[R][j] - appleNum[R][j-1] - appleNum[i][j] + appleNum[i][j-1] + bananaNum[i-1][j] - bananaNum[i-1][j-1]);
            
            dp[i][j] = max(dp[i][j], dp[i-1][j] - (appleNum[i][j] - appleNum[i][j-1] - appleNum[i-1][j] + appleNum[i-1][j-1]));

            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + appleNum[R][j] - appleNum[R][j-1] - appleNum[i][j] + appleNum[i][j-1] + bananaNum[i-1][j] - bananaNum[i-1][j-1]);
        }
    }

    cout << dp[R][C] << '\n';
    

    return 0;
}