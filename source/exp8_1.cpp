#include <iostream>
#include <string>
using namespace std;

template <class T>
class Hash;
template <>
class Hash<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template <class K, class E>
class hashTable
{
public:
    hashTable(int theDivisor = 16);
    ~hashTable() { delete[] table; }
    int search(const K &) const;
    void find(const K &) const;
    void insert(const pair<const K, E> &);
    void output();
    void erase(K &);

private:
    pair<const K, E> **table; //散列表
    Hash<K> hash;             //把类型K映射到一个非负整数
    int dSize;                //字典中数对个数
    int divisor;              //散列函数除数
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;
    //分配和初始化散列表数组
    table = new pair<const K, E> *[divisor];
    for (int i = 0; i < divisor; i++)
    {
        table[i] = NULL;
    }
}

template <class K, class E>
int hashTable<K, E>::search(const K &theKey) const
{
    int i = (int)hash(theKey) % divisor;
    int j = i;
    do
    {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    } while (j != i);
    return j;
}

template <class K, class E>
void hashTable<K, E>::find(const K &theKey) const
{
    //如果没找到就输出-1，找到了就输出下标索引
    int b = search(theKey);
    if (table[b] == NULL || table[b]->first != theKey)
    {
        cout << -1 << endl;
        return;
    }

    cout << b << endl;
    return;
}

template <class K, class E>
void hashTable<K, E>::insert(const pair<const K, E> &thepair)
{
    int b = search(thepair.first);
    if (table[b] == NULL) //当前位置没有pair，直接放到这个位置即可
    {
        table[b] = new pair<const K, E>(thepair);
        dSize++;
        cout << b << endl;
    }
    else if (table[b]->first == thepair.first)
    {
        cout << "Existed" << endl;
    }
    else
    {
        cout << "表满，插入失败" << endl;
    }
}

template <class K, class E>
void hashTable<K, E>::output()
{
    for (int i = 0; i < divisor; i++)
    {
        if (table[i] == NULL)
            cout << "NULL" << endl;
        else
            cout << table[i]->first << " " << table[i]->second << endl;
    }
}

template <class K, class E>
void hashTable<K, E>::erase(K &theKey)
{
    int b = search(theKey);
    if (table[b] == NULL || table[b]->first != theKey)
        cout << "Not Found" << endl;
    else
    {
        table[b] = NULL;
        dSize--;
        int res = 0;
        int emp = b, x = b, want;
        //emp是删除元素空出来的位置；
        //x走在最前面，向前找到需要移动的元素；
        //want是x找到的需要移动的元素本来应该在的位置
        do
        {
            x = (x + 1) % divisor;
            if (table[x] == NULL)
                break;
            want = table[x]->first % divisor;
            if ((emp < x && want > x) || (want > x && emp >= want) || (emp < x && emp >= want))
            {
                table[emp] = table[x];
                table[x] = NULL;
                emp = x;
                res++;
            }
        } while (table[(x + 1) % divisor] != NULL && x != b);
        cout << res << endl;
    }
}

int main()
{
    int D, m;
    cin >> D >> m;
    hashTable<int, int> h(D);
    pair<int, int> p;
    while (m--)
    {
        int opt, x;
        cin >> opt >> x;
        switch (opt)
        {
        case 0:
            p = make_pair(x, x);
            h.insert(p);
            break;
        case 1:
            h.find(x);
            break;
        case 2:
            h.erase(x);
        }
    }
    //system("pause");
    return 0;
}