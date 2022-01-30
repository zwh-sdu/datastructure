#include <iostream>
using namespace std;

//为实现层次遍历的操作，要使用队列，自定义一个Queue的类
template <class T>
class Queue
{
public:
    Queue(int initialCapacity = 16)
    {
        length = initialCapacity;
        queue = new T[length];
        thefront = 0;
        theback = 0;
    }
    ~Queue() { delete[] queue; }
    bool empty() const { return thefront == theback; }
    int size() const
    {
        return (theback - thefront + length) % length;
    }
    T &front()
    {
        return queue[(thefront + 1) % length];
    }
    T &back()
    {
        return queue[theback];
    }
    void pop()
    {
        thefront = (thefront + 1) % length;
        queue[thefront].~T();
    }
    void push(const T &x)
    {
        //如果需要，则增加数组长度
        if ((theback + 1) % length == thefront) //加倍数组长度
        {
            //分配新的数组空间
            T *newqueue = new T[2 * length];
            //把原数组复制到新数组
            int start = (thefront + 1) % length;
            if (start < 2)
            {
                //没有形成环
                copy(queue + start, queue + start + length - 1, newqueue);
            }
            else
            {
                //队列形成环
                copy(queue + start, queue + length, newqueue);
                copy(queue, queue + theback + 1, newqueue + length - start);
            }
            //这是新的队列的首和尾的元素位置
            thefront = 2 * length - 1;
            theback = length - 2;
            length *= 2;
            delete[] queue;
            queue = newqueue;
        }
        theback = (theback + 1) % length;
        queue[theback] = x;
    }

private:
    int thefront;
    int theback;
    int length;
    T *queue;
};

template <class T>
class binaryTree
{
public:
    virtual ~binaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*)(T *)) = 0;
    virtual void inOrder(void (*)(T *)) = 0;
    virtual void postOrder(void (*)(T *)) = 0;
    virtual void levelOrder(void (*)(T *)) = 0;
};

template <class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T> *leftChild, *rightChild;
    BinaryTreeNode()
    {
        leftChild = NULL;
        right = NULL;
    }
    BinaryTreeNode(const T &theElement)
    {
        element = theElement;
        leftChild = NULL;
        rightChild = NULL;
    }
    BinaryTreeNode(const T &theElement, BinaryTreeNode *theLeftChild, BinaryTreeNode *theRightChild)
    {
        element = theElement;
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template <class E>
class linkedBinaryTree : public binaryTree<BinaryTreeNode<E>>
{
public:
    linkedBinaryTree()
    {
        root = NULL;
        treeSize = 0;
    }
    ~linkedBinaryTree() { erase(); }
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    void preOrder(void (*theVisit)(BinaryTreeNode<E> *))
    {
        visit = theVisit;
        preOrder(root);
    }
    void inOrder(void (*theVisit)(BinaryTreeNode<E> *))
    {
        visit = theVisit;
        inOrder(root);
    }
    void postOrder(void (*theVisit)(BinaryTreeNode<E> *))
    {
        visit = theVisit;
        postOrder(root);
    }
    void levelOrder(void (*theVisit)(BinaryTreeNode<E> *))
    {
        visit = theVisit;
        levelOrder(root);
    }
    void erase()
    {
        dispose(root);
        root = NULL;
        treeSize = 0;
    }
    int height() const { return height(root); }
    void preOrderOutput()
    {
        preOrder(output);
        cout << endl;
    }
    void inOrderOutput()
    {
        inOrder(output);
        cout << endl;
    }
    void postOrderOutput()
    {
        postOrder(output);
        cout << endl;
    }
    void levelOrderOutput()
    {
        levelOrder(output);
        cout << endl;
    }
    void makeTree(const E &element, linkedBinaryTree<E> &l, linkedBinaryTree<E> &r)
    {
        root = new BinaryTreeNode<E>(element, l.root, r.root);
        treeSize = l.treeSize + r.treeSize + 1;
    }

private:
    BinaryTreeNode<E> *root;                   //指向根的指针
    int treeSize;                              //数的节点数
    static void (*visit)(BinaryTreeNode<E> *); //访问函数
    static void preOrder(BinaryTreeNode<E> *t);
    static void inOrder(BinaryTreeNode<E> *t);
    static void postOrder(BinaryTreeNode<E> *t);
    static void levelOrder(BinaryTreeNode<E> *t);
    static void dispose(BinaryTreeNode<E> *t) { delete t; }
    static int height(BinaryTreeNode<E> *t);
    static void output(BinaryTreeNode<E> *t)
    {
        if (t != NULL)
        {
            cout << t->element << " ";
        }
    }
};

template <class T>
void (*linkedBinaryTree<T>::visit)(BinaryTreeNode<T> *);

template <class T>
void linkedBinaryTree<T>::preOrder(BinaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        linkedBinaryTree<T>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::inOrder(BinaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        linkedBinaryTree<T>::visit(t);
        inOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::postOrder(BinaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<T>::visit(t);
    }
}

template <class T>
void linkedBinaryTree<T>::levelOrder(BinaryTreeNode<T> *t)
{
    Queue<BinaryTreeNode<T> *> q;
    while (t != NULL)
    {
        linkedBinaryTree<T>::visit(t);
        //将t的孩子插入队列
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);
        //提取下一个要访问的节点
        if (q.empty())
            return;
        t = q.front();
        q.pop();
    }
}

template <class T>
int linkedBinaryTree<T>::height(BinaryTreeNode<T> *t) //返回根为*t的树的高度
{
    if (t == NULL)
        return 0;                   //空树
    int hl = height(t->leftChild);  //左树高
    int hr = height(t->rightChild); //右树高
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

int a[10001], b[10001], h[10001], s[10001];
linkedBinaryTree<int> t[10001];
int main()
{
    linkedBinaryTree<int> non;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = n; i > 0; i--)
    {
        if (a[i] != -1 && b[i] != -1)
        {
            t[i].makeTree(i, t[a[i]], t[b[i]]);
        }
        if (a[i] != -1 && b[i] == -1)
        {
            t[i].makeTree(i, t[a[i]], non);
        }
        if (a[i] == -1 && b[i] != -1)
        {
            t[i].makeTree(i, non, t[b[i]]);
        }
        if (a[i] == -1 && b[i] == -1)
        {
            t[i].makeTree(i, non, non);
        }
        h[i]=t[i].height();
        s[i]=t[i].size();
    }
    t[1].levelOrderOutput();
    for (int i = 1; i <= n; i++)
    {
        cout << t[i].size() << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << t[i].height() << " ";
    }
    cout << endl;
    //system("pause");
    return 0;
}