#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string str;
char strArr[2501];
int dp[2501][2501];
int result[2501];
#define INT_MAX 91283921;

int isPalinedrome(int front, int end) {
    int middle = (front + end) / 2;
    int i = 0;
    while ((front + i) <= middle) {
        if(str[front+i] != str[end-i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> str;
    str.insert(0, " ");
    for (int i = 1; i < str.length(); i++) {
        for (int j = i; j < str.length(); j++) {
            if (i == j) { 
                dp[i][j] = 1;
                continue;    
            }
            dp[i][j] = isPalinedrome(i, j);
        }
    }
    for (int i = 1; i < str.length(); i++) {
        result[i] = INT_MAX;
        for (int j = 1; j <= i; j++) {
            if (dp[j][i]) { 
                result[i] = min(result[i], result[j-1] + 1);
            }
        }      
    }    
    cout << result[str.length() - 1] << '\n';
    return 0;
}