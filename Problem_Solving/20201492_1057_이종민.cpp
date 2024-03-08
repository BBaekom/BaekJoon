#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int N, kim, lim;
    //N : 참가자의 수, kim : 김지민의 번호, lim : 임한수의 번호
    cin >> N >> kim >> lim;

    int round = (int)ceil(log2(N));     
    // cout << round << endl;

    for (int i = 1; i <= round; i++) {
        if ((kim+1) / 2 == (lim+1) / 2) {
            cout << i << endl;
            break;
        }
        kim = (kim + 1) / 2;
        lim = (lim + 1) / 2;
    }

    return 0;
}