#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T; // 테스트 개수 T

    string sentence;
    stack<char> stack;

    cin.ignore();

    for (int i = 0; i < T; i++) {
        getline(cin, sentence);
        for (int j = 0; j < sentence.size(); j++) {
            if (sentence[j] == ' ') {
                while (!stack.empty()) {
                    cout << stack.top();
                    stack.pop();
                }
                cout << ' ';
            } else {
                stack.push(sentence[j]);
            }
        }
        if (!stack.empty()) {
            while (!stack.empty()) {
                cout << stack.top();
                stack.pop();
            }
        }
        cout << '\n';
    }

    return 0;
}