#include <iostream>
#include <cmath>
using namespace std;

int Make_Valid_Num(int* unique) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += unique[i] * unique[i];
    }
    return sum % 10;
}

int main() {
    int unique[5];

    for (int i = 0; i < 5; i++) {
        cin >> unique[i];
    }

    int validNum = Make_Valid_Num(unique);
    cout << validNum << endl;
    
    return 0;
}