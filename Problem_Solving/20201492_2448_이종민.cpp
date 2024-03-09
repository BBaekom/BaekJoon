#include <iostream>
using namespace std;

void fill_Star(int, int, int, char**);

int main() {
    int N;
    cin >> N;

    char** star;
    star = new char *[N];
    for (int i = 0; i < N; i++) {
        star[i] = new char[N*2-1];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N*2-1; ++j) {
            star[i][j] = ' ';
        }
    }

    fill_Star(N, 0, N-1, star);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2*N-1; j++) {
            cout << star[i][j];
        }
        cout << '\n';
    }

    for (int i = 0; i < N; i++) {
        delete[] star[i];
    }
    delete[] star;

    return 0;
}


void fill_Star(int N, int x, int y, char** star) {
    if (N == 3) {
        star[x][y] = '*';
        star[x+1][y-1] = '*';
        star[x+1][y+1] = '*';
        for (int i = y-2; i <= y+2; i++) {
            star[x+2][i] = '*';
        }
    } else {
        fill_Star(N/2, x, y, star);
        fill_Star(N/2, x+N/2, y-N/2, star);
        fill_Star(N/2, x+N/2, y+N/2, star);
    }
}