#include <iostream>
using namespace std;

struct Stack {
    int arr[10001]; // 명령의 수(N)가 최대 10000이기 때문에
    int top = -1;

    void push(int data) {
        arr[++top] = data;
    }

    int pop() {
        if (top == -1) {
            return top;
        }
        return arr[top--];
    }

    int size() {
        return top + 1;
    }

    int empty() {
        if (top < 0) {
            return 1;
        } else {
            return 0;
        }
    }

    int topNum() {
        if (top == -1) {
            return -1;
        } 
        return arr[top];
    }
};

int main() {
    int N;
    cin >> N;
    Stack stack;
    string order;
    for (int i = 0; i < N; i++) {
        cin >> order;
        if (order == "push") {
            int data;
            cin >> data;
            stack.push(data);
        } else if (order == "pop") {
            cout << stack.pop() << endl;
        } else if (order == "size") {
            cout << stack.size() << endl;
        } else if (order == "empty") {
            cout << stack.empty() << endl;
        } else if (order == "top") {
            cout << stack.topNum() << endl;
        }
    }
    
    return 0;
}