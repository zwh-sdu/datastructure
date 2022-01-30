#include<bits/stdc++.h>
using namespace std;

template <class T>
class mysort
{
public:
    mysort(){};
    ~mysort(){};

public:
    //名次排序、及时终止的选择排序、及时终止的冒泡排序、插入排序。
    //名次排序
    //计算名次
    void rank(T a[], int n, int r[])
    {
        for (int i = 0; i < n; i++)
        {
            r[i] = 0;
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (a[j] <= a[i])
                    r[i]++;
                else
                    r[j]++;
            }
        }
    }

    void rearrange(T a[], int n)
    {
        cout << "rank sort" << endl;
        int *r = new int[n];
        rank(a, n, r);
        for (int i = 0; i < n; i++)
        {
            while (r[i] != i)
            {
                int t = r[i];
                swap(a[i], a[t]);
                swap(r[i], r[t]);
            }
        }
        delete[] r;
    }

    //及时终止的选择排序
    void selectionsort(T a[], int n)
    {
        cout << "select sort" << endl;
        bool sorted = false;
        for (int size = n; !sorted && (size > 1); size--)
        {
            int indexofmax = 0;
            sorted = true;
            //查找最大元素
            for (int i = 1; i < size; i++)
            {
                if (a[indexofmax] <= a[i])
                    indexofmax = i;
                else
                    sorted = false;
            }
            swap(a[indexofmax], a[size - 1]);
        }
    }

    //及时终止的冒泡排序
    bool bubble(T a[], int n) //把数组a[0;n-1]中的最大的元素移到最右端
    {
        bool swapped = false; //目前为止未交换
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                swapped = true; //交换
            }
        }
        return swapped;
    }
    void bubblesort(T a[], int n) //及时终止的冒泡排序
    {
        cout << "bubble sort" << endl;
        for (int i = n; i > 1 && bubble(a, i); i--)
            ;
    }

    //插入排序
    void insert(T a[], int n, const T &x) //把x插入有序数组a[0,n-1]
    {
        int i;
        for (i = n - 1; i >= 0 && x < a[i]; i--)
        {
            a[i + 1] = a[i];
        }
        a[i + 1] = x;
    }
    void insertsort(T a[], int n) //对数组a[0:n-1]实施插入排序
    {
        cout << "insert sort" << endl;
        for (int i = 1; i < n; i++)
        {
            T t = a[i];
            insert(a, i, t);
        }
    }
};

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    mysort<int> m;
    //m.rearrange(a, n);
    //m.selectionsort(a, n);
    //m.bubblesort(a, n);
    m.insertsort(a, n);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    delete[] a;
    system("pause");
    return 0;
}