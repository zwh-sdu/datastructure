#include <iostream>
using namespace std;

template <class T>
struct chainNode
{
    //数据成员
    T element;
    chainNode<T> *next;

    //方法
    chainNode() {}
    chainNode(const T &element) { this->element = element; }
    chainNode(const T &element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};

template <class T>
class chain
{
public:
    chain()
    {
        firstNode = NULL;
        listSize = 0;
    }                                 //构造函数
    ~chain();                         //析构函数
    void insert(int pos, T _element); //插入函数
    void sort();                      //排序函数
    void merge(chain &a, chain &b);   //合并函数
    void output();

    //迭代器
    class iterator;
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(NULL); }

    // iterator for chain
    class iterator
    {
    public:
        //构造函数
        iterator(chainNode<T> *theNode = NULL)
        {
            node = theNode;
        }

        //解引用操作
        T &operator*() const { return node->element; }
        T *operator->() const { return &node->element; }

        //迭代器加法操作
        iterator &operator++() //前加
        {
            node = node->next;
            return *this;
        }
        iterator operator++(int) //后加
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        //相等检验
        bool operator!=(const iterator right) const
        {
            return node != right.node;
        }
        bool operator==(const iterator right) const
        {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    };

protected:
    chainNode<T> *firstNode; //指向链表第一个节点的指针
    int listSize;            //线性表的元素个数
};

template <class T>
void chain<T>::insert(int pos, T _element)
{
    //在pos位置上插入一个_element元素
    if (pos < 0 || pos > listSize)
    { //无效索引
        cout << "无效索引" << endl;
        return;
    }

    if (pos == 0)
    { //在链表头插入
        firstNode = new chainNode<T>(_element, firstNode);
    }
    else
    {
        //寻找新元素前驱
        chainNode<T> *p = firstNode;
        for (int i = 0; i < pos - 1; i++)
        {
            p = p->next;
        }
        //在p之后插入
        p->next = new chainNode<T>(_element, p->next);
    }
    listSize++;
}

template <class T>
chain<T>::~chain()
{
    //链表析构函数，删除链表的所有节点
    while (firstNode != NULL)
    {
        //删除首节点
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void chain<T>::output()
{
    for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
    {
        cout << currentNode->element << " ";
    }
    cout << endl;
}

template <class T>
void chain<T>::sort()
{
    //排序方法是每次把最小的数移动到最左边,左边界a不断右移
    if (listSize < 1)
        return;
    chainNode<T> *a = NULL;
    chainNode<T> *b = NULL;
    for (a = firstNode; a != NULL; a = a->next)
    {
        for (b = a->next; b != NULL; b = b->next)
        {
            if (a->element > b->element)
            {
                T tmp = b->element;
                b->element = a->element;
                a->element = tmp;
            }
        }
    }
}

template <class T>
void chain<T>::merge(chain &a, chain &b)
{
    //使用迭代器实现两个有序链表的合并
    int i = 0;
    chain::iterator iter1 = a.begin(), iter2 = b.begin();
    while (iter1 != NULL && iter2 != NULL)
    {
        if (*iter1 < *iter2)
        {
            insert(i++, *iter1);
            iter1++;
        }
        else if (*iter1 > *iter2)
        {
            insert(i++, *iter2);
            iter2++;
        }
        else
        {
            insert(i++, *iter1);
            insert(i++, *iter2);
            iter1++;
            iter2++;
        }
    }
    if (iter1 != NULL)
    {
        while (iter1 != NULL)
        {
            insert(i++, *iter1);
            iter1++;
        }
    }
    if (iter2 != NULL)
    {
        while (iter2 != NULL)
        {
            insert(i++, *iter2);
            iter2++;
        }
    }
}

int main()
{
    int N, M, temp;
    cin >> N >> M;
    chain<int> a, b, c;
    for (int i = 0; i < N; i++)
    {
        cin >> temp;
        a.insert(i, temp);
    }
    for (int i = 0; i < M; i++)
    {
        cin >> temp;
        b.insert(i, temp);
    }
    a.sort();
    b.sort();
    c.merge(a, b);
    int res = 0, index = 0;
    for (chain<int>::iterator iter = a.begin(); iter != a.end(); iter++)
    {
        res += (*iter) ^ (index++);
    }
    cout << res << endl;
    res = 0;
    index = 0;
    for (chain<int>::iterator iter = b.begin(); iter != b.end(); iter++)
    {
        res += (*iter) ^ (index++);
    }
    cout << res << endl;
    res = 0;
    index = 0;
    for (chain<int>::iterator iter = c.begin(); iter != c.end(); iter++)
    {
        res += (*iter) ^ (index++);
    }
    cout << res << endl;
    system("pause");
    return 0;
}