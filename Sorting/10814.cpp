#include <iostream>
#include <algorithm>
using namespace std;

struct members {
    int age;
    string name;
};

bool compare(members a, members b) {
    return a.age < b.age;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    int N;
    cin >> N; // 온라인 저지에 가입한 사람 수

    members arr[N];

    for (int i = 0; i < N; i++) {
        cin >> arr[i].age >> arr[i].name;
    }

    stable_sort(arr, arr+N, compare);

    for (int i = 0; i < N; i++) {
        cout << arr[i].age << " " << arr[i].name << '\n';
    }

    return 0;
}