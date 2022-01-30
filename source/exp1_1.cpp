#include<bits/stdc++.h>
using namespace std;

int ans = 0; //最终输出的答案

template <class T>
void sub(T a[], int n, int dep, bool visit[])
{
    //对当前子集进行value计算并异或求和
    if (dep == n)
    {
        int temp = 0;
        for (int i = 0, j = 1; i < n; i++)
        {
            if (visit[i])
            {
                temp += a[i] * j;
                j++;
            }
        }
        ans ^= temp;
    }
    else
    {
        visit[dep] = true;
        sub(a, n, dep + 1, visit);
        visit[dep] = false;
        sub(a, n, dep + 1, visit);
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    bool visit[n] = {false};//visit数组表示当前子集是否包含某一个元素，visit[i]=1表示包含，0表示不包含
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sub(a, n, 0, visit);
    cout << ans << endl;
    system("pause");
    return 0;
}