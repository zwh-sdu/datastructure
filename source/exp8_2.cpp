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

//链表的节点，二元组的形式
template <class K, class E>
struct pairNode
{
    pair<K, E> element;
    pairNode<K, E> *next;
    pairNode(const pair<K, E> &thepair) { element = thepair; }
    pairNode(const pair<K, E> &thepair, pairNode<K, E> *thenext)
    {
        element = thepair;
        next = thenext;
    }
};

template <class K, class E>
class sortedChain
{
public:
    //构造函数
    sortedChain()
    {
        firstNode = NULL;
        dSize = 0;
    }
    //析构函数
    ~sortedChain();
    pair<K, E> *find(const K &thekey) const;
    bool insert(const pair<const K, E> &thepair);
    void erase(const K &thekey);
    int size() { return dSize; }

private:
    pairNode<K, E> *firstNode;
    int dSize;
};

template <class K, class E>
sortedChain<K, E>::~sortedChain()
{
    while (firstNode != NULL)
    {
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class K, class E>
pair<K, E> *sortedChain<K, E>::find(const K &thekey) const //返回匹配的数对的指针，如果不存在，则返回NULL
{
    pairNode<K, E> *currentNode = firstNode;
    //搜索关键字为thekey的数对
    while (currentNode != NULL && currentNode->element.first != thekey)
    {
        currentNode = currentNode->next;
    }
    //判断是否匹配
    if (currentNode != NULL && currentNode->element.first == thekey) //找到匹配对
    {
        cout << dSize << endl;
        return &currentNode->element;
    }

    //无匹配的数对
    return NULL;
}

template <class K, class E>
bool sortedChain<K, E>::insert(const pair<const K, E> &thepair) //往字典中插入thepair，覆盖已经存在的匹配的数对
{
    pairNode<K, E> *p = firstNode, *tp = NULL;
    //移动指针tp，使thepair可以插在tp后面
    while (p != NULL && p->element.first < thepair.first)
    {
        tp = p;
        p = p->next;
    }
    //检查是否有匹配的数对
    if (p != NULL && p->element.first == thepair.first)
    {
        cout << "Existed" << endl;
        return false;
    }
    //无匹配的数对，为thepair建立新的节点
    pairNode<K, E> *newNode = new pairNode<K, E>(thepair, p);
    //在tp之后插入新节点
    if (tp == NULL)
        firstNode = newNode;
    else
        tp->next = newNode;
    dSize++;
    return true;
}

template <class K, class E>
void sortedChain<K, E>::erase(const K &thekey)
{
    //删除关键字为thekey的数对
    pairNode<K, E> *p = firstNode, *tp = NULL;
    //搜索关键字为thekey的数对
    while (p != NULL && p->element.first < thekey)
    {
        tp = p;
        p = p->next;
    }
    //确定是否匹配
    if (p != NULL && p->element.first == thekey)
    {
        //找到一个匹配的数对
        if (tp == NULL)
            firstNode = p->next;
        else
            tp->next = p->next;
        delete p;
        dSize--;
        cout << dSize << endl;
        return;
    }
    //没找到匹配的数对
    cout << "Delete Failed" << endl;
}

template <class K, class E>
class hashChains
{
public:
    hashChains(int thedivisor);
    ~hashChains() { delete[] table; }
    int size() { return dSize; }
    void find(const K &) const;
    void insert(const pair<const K, E> &thepair);
    void erase(const K &thekey);

private:
    sortedChain<K, E> *table;
    Hash<K> hash; //把类型K映射到一个非负整数
    int dSize;    //字典中数对个数
    int divisor;  //散列函数除数
};

template <class K, class E>
hashChains<K, E>::hashChains(int thedivisor)
{
    dSize = 0;
    divisor = thedivisor;
    table = new sortedChain<K, E>[divisor];
}

template <class K, class E>
void hashChains<K, E>::find(const K &thekey) const
{
    if (table[hash(thekey) % divisor].find(thekey) == NULL)
    {
        cout << "Not Found" << endl;
    }
}

template <class K, class E>
void hashChains<K, E>::insert(const pair<const K, E> &thepair)
{
    if (table[(int)hash(thepair.first) % divisor].insert(thepair))
        dSize++;
}

template <class K, class E>
void hashChains<K, E>::erase(const K &thekey)
{
    table[hash(thekey) % divisor].erase(thekey);
}

int main()
{
    int D, m;
    cin >> D >> m;
    pair<int, int> p;
    hashChains<int, int> h(D);
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