#include <iostream>
#include <string>
#include <stack>
using namespace std;

int lcs[1001][1001];
string str1, str2, tmp1, tmp2;
string result;
int row, col;

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    cin >> tmp1 >> tmp2;

    stack<char> result;

    str1 = tmp1.insert(0, "0");
    str2 = tmp2.insert(0, "0");


    for (int i = 0; i < str1.length(); i++) {
        for (int j = 0; j < str2.length(); j++) {
            if (i == 0 || j == 0) { continue; }
            if (str1[i] == str2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            } else {
                if (lcs[i-1][j] < lcs[i][j-1]) {
                    lcs[i][j] = lcs[i][j-1];
                } else {
                    lcs[i][j] = lcs[i-1][j];
                }
            }
        }
    }


    row = str1.length() - 1;
    col = str2.length() - 1;

    while(lcs[row][col] != 0) {
        if (lcs[row][col] == lcs[row - 1][col]) {
            row--;
        } else if (lcs[row][col] == lcs[row][col - 1]) {
            col--;
        } else {
            result.push(str1[row]);
            row--;
            col--;
        }
    }


    cout << lcs[str1.length() - 1][str2.length() - 1] << '\n';
    while(!result.empty()) {
        cout << result.top();
        result.pop();
    }

    cout << '\n';

    return 0;
}