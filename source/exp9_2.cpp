#include <iostream>
using namespace std;

int preorder[10000], inorder[10000];
void postorder(int pre, int post, int n)
{
    if (n == 1)
    {
        cout << preorder[pre] << " ";
        return;
    }
    if (n == 0)
        return;
    int i = 0;
    for (; preorder[pre] != inorder[post + i]; i++)
        ;
    postorder(pre + 1, post, i);
    postorder(pre + i + 1, post + i + 1, n - i - 1);
    cout << preorder[pre] << " ";
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
    }
    postorder(0, 0, n);
    //system("pause");
    return 0;
}