#include <iostream>
#include <algorithm>
using namespace std;

void bubble_sort(int *arr, int N)
{
    for (int j = N - 1; j > 0; j--)
    {
        for (int i = 0; i < j; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
            }
        }
    }
}

void select_sort(int *arr, int N)
{
    for (int j = 0; j < N - 1; j++)
    {
        for (int i = j + 1; i < N; i++)
        {
            if (arr[j] > arr[i])
            {
                swap(arr[j], arr[i]);
            }
        }
    }
}

void insert_sort(int *arr, int N)
{
    for (int i = 1; i < N; i++)
    {
        int key = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[key] < arr[j])
            {
                swap(arr[key], arr[j]); // 2 3 1 4 5
                key--;
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    // bubble_sort(arr, N);
    // select_sort(arr, N);
    insert_sort(arr, N);
    // cout << endl;

    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}