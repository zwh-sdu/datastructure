#include <bits/stdc++.h>
using namespace std;

int ans;
string s;
map<char, int> mp;                                //每个字符出现的频率
priority_queue<int, vector<int>, greater<int>> q; //存储字符权重(频率)的优先队列

int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        mp[s[i]]++;
    }
    for (auto iter = mp.begin(); iter != mp.end(); iter++)
    {
        q.push(iter->second);
    }
    while (q.size() > 1)
    {
        int x, y, z;
        x = q.top();
        q.pop();
        y = q.top();
        q.pop();
        z = x + y;
        q.push(z);
        ans += z;
    }
    cout << ans << endl;
    //system("pause");
    return 0;
}