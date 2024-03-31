#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int dp[500001];
int LIS[500001];
struct info
{
    int idx, val;
};
bool cmp(info &a, info &b)
{
    return a.idx < b.idx;
};
info tmp;

int b_search(int r, int v)
{
    int l = 0, mid, result = r;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (dp[mid] >= v)
        {
            result = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << "이진탐색 결과 : " << result << '\n'; 
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int num, a, b, idx = 0;
    vector<info> v;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> a >> b;
        tmp.idx = a;
        tmp.val = b;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end(), cmp);

    dp[0] = v[0].val;
    LIS[0] = 0;

    cout << "v.size() : " << v.size() << '\n';

    for (int i = 1; i < v.size(); i++)
    {
        if (v[i].val > dp[idx])
        {
            dp[++idx] = v[i].val;
            LIS[i] = idx;
        }
        else
        {
            int vv = b_search(idx, v[i].val);
            dp[vv] = v[i].val;
            LIS[i] = vv;
        }
    }
    cout << v.size() - (idx + 1) << '\n';
    int cnt = idx;
    vector<int> temp;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        if (LIS[i] == cnt)
            cnt--;
        else
            temp.push_back(v[i].idx);
    }
    for (int i = temp.size() - 1; i >= 0; i--)
        cout << temp[i] << '\n';
    return 0;
}