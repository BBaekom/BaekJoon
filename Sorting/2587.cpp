#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int arr[5];
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    int avg = 0;
    for (int i = 0 ; i < 5; i++) {
        avg += arr[i];
    }
    avg /= 5;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }

    cout << avg << endl << arr[2] << endl;

    return 0;
}