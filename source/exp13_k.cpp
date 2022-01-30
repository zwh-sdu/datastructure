#include<bits/stdc++.h>
using namespace std;

const int N = 500005;
struct Node
{
	int a, b, c; //a,b,c分别是边的起点终点和边的权重
	bool operator < (const Node x) const {
		return c < x.c;
	}
}node[N];

int pre[N];

int find(int x) {
	if (pre[x] == x) {
		return x;
	}
	return pre[x] = find(pre[x]);
}

bool join(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return false;
	pre[x] = y;
	return true;
}

int main()
{
	int n, m, p;
	cin >> n >> m;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		pre[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		cin >> node[cnt].a >> node[cnt].b >> node[cnt].c;
		cnt++;
	}
	sort(node, node + cnt);
	long long ans = 0;
	for (int i = 0; i < cnt; i++) {
		if (join(node[i].a, node[i].b)) {
			ans += node[i].c;
		}
	}
	cout << ans << endl;
    // system("pause");
	return 0;
}
