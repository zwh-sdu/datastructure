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
    void erase(T _element);           //删除函数
    void reverse();                   //逆置函数
    void search(T _element);          //查询函数
    void output();                    //输出函数

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
void chain<T>::erase(T _element)
{
    //要删除的节点
    chainNode<T> *deleteNode;
    if (firstNode->element == _element)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
        delete deleteNode;
        listSize--;
        return;
    }
    for (chainNode<T> *pre = firstNode; pre->next; pre = pre->next)
    {
        if (pre->next->element == _element)
        {
            deleteNode = pre->next;
            pre->next = deleteNode->next;
            delete deleteNode;
            listSize--;
            return;
        }
    }
    cout << -1 << endl;
}

template <class T>
void chain<T>::reverse()
{
    chainNode<T> *pre = firstNode;
    firstNode = firstNode->next;
    pre->next = NULL;
    chainNode<T> *aft = firstNode->next;
    for (int i = 0; i < listSize - 3; i++)
    {
        firstNode->next = pre;
        pre = firstNode;
        firstNode = aft;
        aft = aft->next;
    }
    firstNode->next = pre;
    aft->next = firstNode;
    firstNode = aft;
}

template <class T>
void chain<T>::search(T _element)
{
    //返回_element首次出现的索引
    //若该元素不存在，则返回-1
    chainNode<T> *currentNode = firstNode;
    int pos = 0; //当前节点的索引
    while (currentNode != NULL && currentNode->element != _element)
    {
        //移向下一个节点
        currentNode = currentNode->next;
        pos++;
    }
    //确定是否找到所需的元素
    if (currentNode == NULL)
    {
        cout << -1 << endl;
    }
    else
        cout << pos << endl;
}

template <class T>
void chain<T>::output()
{
    for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
    {
        cout << currentNode->element << " ";
    }
}

int main()
{
    int N, Q, temp;
    cin >> N >> Q;
    chain<int> c;
    for (int i = 0; i < N; i++)
    {
        cin >> temp;
        c.insert(i, temp);
    }
    int op, pos, element;
    for (int i = 0; i < Q; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> pos >> element;
            c.insert(pos, element);
            break;
        case 2:
            cin >> element;
            c.erase(element);
            break;
        case 3:
            c.reverse();
            break;
        case 4:
            cin >> element;
            c.search(element);
            break;
        case 5:
            long long res = 0, index = 0;
            for (chain<int>::iterator iter = c.begin(); iter != c.end(); iter++)
            {
                res += (*iter) ^ (index++);
            }
            cout << res << endl;
            break;
        }
    }
    //system("pause");
    return 0;
}
