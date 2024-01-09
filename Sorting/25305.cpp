#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int N, k;
    cin >> N >> k;

    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    for (int i = N - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << arr[k - 1] << endl;

    return 0;
}