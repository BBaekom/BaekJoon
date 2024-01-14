#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T; // 테스트 개수

    while(T--) {
        stack<char> stack;
        string bracket;
        cin >> bracket;

        while (!stack.empty()) {
            stack.pop();
        }

        for (int i = 0; i < bracket.length(); i++) {
            if (stack.empty()) {
                stack.push(bracket[i]);
            } else {
                if (bracket[i] == ')' && stack.top() == '('){
                    stack.pop();
                } else {
                    stack.push(bracket[i]);
                }
            }
        }

        if (stack.empty()) {
            cout << "YES" << endl;;
        } else {
            cout << "NO" << endl;
        }

    }
    return 0;
}