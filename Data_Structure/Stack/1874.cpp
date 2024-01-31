#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin >> n;
    int sequence[n];
    int num = 1;
    string answer = "";
    stack<int> stack;
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }
    for (int i = 0; i < n; i++) {
        if (stack.empty()) {
            for (num; num <= sequence[i]; num++) {
                stack.push(num);
                answer += "+\n";
            }
            stack.pop();
            answer += "-\n";
        } else {
            if (sequence[i] < stack.top()) {
                while(!stack.empty()) {
                    stack.pop();
                }
                cout << "NO" << '\n';
                break;
            }
            if (sequence[i] == stack.top()) {
                stack.pop();
                answer += "-\n";
            } else {
                for (num; num <= sequence[i]; num++) {
                    stack.push(num);
                    answer += "+\n";
                }
                stack.pop();
                answer += "-\n";
            }
        }
        if (i == n-1) {
            cout << answer;
        }
    }
    

    return 0;
}