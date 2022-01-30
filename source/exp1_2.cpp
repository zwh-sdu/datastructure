#include <bits/stdc++.h>
using namespace std;

int ans = 0;

template <class T>
void permutation(T a[], int dep, int n)
{
    if (dep == n)
    {
        //找到了一种排列方式
        int temp = 0;
        for (int i = 0; i < n; i++)
        {
            temp += a[i] ^ (i + 1);
        }
        ans |= temp;
    }
    else
    {
        for (int j = dep; j < n; j++)
        {
            swap(a[j], a[dep]);
            permutation(a, dep + 1, n);
            swap(a[j], a[dep]);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    permutation(a, 0, n);
    cout << ans << endl;
    system("pause");
    return 0;
}