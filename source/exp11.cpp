#include <iostream>
using namespace std;

template <class T>
struct BinaryTreeNode
{
    T element;
    BinaryTreeNode<T> *leftChild, *rightChild;
    int leftSize; //该节点左子树节点的个数，用于按名次查找和删除操作
    // BinaryTreeNode()
    // {
    //     leftChild = NULL;
    //     rightChild = NULL;
    //     leftSize = 0;
    // }
    BinaryTreeNode(const T &theElement)
    {
        element = theElement;
        leftChild = NULL;
        rightChild = NULL;
        leftSize = 0;
    }
    BinaryTreeNode(const T &theElement, BinaryTreeNode *theLeftChild, BinaryTreeNode *theRightChild, int theleftSize)
    {
        element = theElement;
        leftChild = theLeftChild;
        rightChild = theRightChild;
        leftSize = theleftSize;
    }
};

template <class T>
class binarySearchTree
{
public:
    binarySearchTree() //构造函�??
    {
        root = NULL;
        treeSize = 0;
    }
    // ~binarySearchTree() { delete[] root; } //析构函数
    int find(const T &theKey);             //查找函数
    int insert(const T &theKey);           //插入函数
    int erase(const T &theKey);            //删除函数
    int find_rank(int rank);               //按名次查找函�??
    int erase_rank(int rank);              //按名次删除函数s
    void output(BinaryTreeNode<T> *t);
    BinaryTreeNode<T> *getroot()
    {
        return root;
    }

private:
    BinaryTreeNode<T> *root; //数的根节�??
    int treeSize;            //数的节点个数
};

template <class T>
int binarySearchTree<T>::find(const T &theKey)
{
    int res = 0;
    BinaryTreeNode<T> *p = root;
    //p从根节点开始搜索，寻找关键字等于theKey的一个元�??
    while (p != NULL)
    {
        res ^= p->element;
        if (p->element == theKey)
            break;
        //检查元素p->element
        if (theKey < p->element)
            p = p->leftChild;
        else if (theKey > p->element)
            p = p->rightChild;
    }
    if (p == NULL)
    { //没找�??
        return 0;
    }
    return res;
}

template <class T>
int binarySearchTree<T>::insert(const T &theKey)
{
    int res = 0;
    //寻找插入位置
    BinaryTreeNode<T> *p = root, *pp = NULL;
    while (p != NULL)
    {
        res ^= p->element;
        //检查元素p->element
        pp = p;
        //p移动到它的一个孩子结�??
        if (theKey < p->element)
        {
            p = p->leftChild;
        }
        else if (theKey > p->element)
        {
            p = p->rightChild;
        }
        else if (theKey == p->element) //已经存在�??
            return 0;
    }
    //建立一个新节点，然后与pp链接
    BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(theKey);
    if (pp != NULL) //树不�??
    {
        if (theKey < pp->element)
            pp->leftChild = newNode;
        else if (theKey > pp->element)
            pp->rightChild = newNode;
    }
    else
        root = newNode; //插入空树
    treeSize++;

    //因为插入了一个节点，所以要更新leftSize
    p = root;
    while (p->element != theKey)
    {
        if (p->element < theKey)
        {
            p = p->rightChild;
        }
        else if (p->element > theKey)
        {
            p->leftSize++; //左子树数�??+1
            p = p->leftChild;
        }
    }
    return res;
}

template <class T>
int binarySearchTree<T>::erase(const T &theKey)
{
    int res = 0;
    //查找关键字为theKey的节�??
    BinaryTreeNode<T> *p = root, *pp = NULL;
    while (p != NULL && p->element != theKey)
    {
        //移动p到它的下一个孩子节�??
        res ^= p->element;
        pp = p;
        if (theKey < p->element)
            p = p->leftChild;
        else if (theKey > p->element)
            p = p->rightChild;
    }
    if (p == NULL)
        return 0; //不存�??
    res ^= p->element;
    p = root;

    //因为删除了一个节点，所以要再次查找theKey，来更新因为删除操作而变化的leftSize
    while (p != NULL && p->element != theKey)
    {
        if (theKey < p->element)
        {
            p->leftSize--;
            p = p->leftChild;
        }
        else if (theKey > p->element)
        {
            p = p->rightChild;
        }
    }

    //重新组织树结�??
    //当p有两个孩子节点时的处�??
    if (p->leftChild != NULL && p->rightChild != NULL)
    {
        //两个孩子，转化为空或只有一个孩子，在p的右子树中寻找最小元�??
        BinaryTreeNode<T> *s = p->rightChild, *ps = p; //s的双�??
        while (s->leftChild != NULL)
        {
            //移动到最大的元素
            s->leftSize--;
            ps = s;
            s = s->leftChild;
        }
        //将最大的元素s移动到p，但不是简单的移动
        BinaryTreeNode<T> *q = new BinaryTreeNode<T>(s->element, p->leftChild, p->rightChild, p->leftSize);
        if (pp == NULL)
            root = q;
        else if (p == pp->leftChild)
        {
            pp->leftChild = q;
        }
        else
            pp->rightChild = q;
        if (ps == p)
            pp = q;
        else
            pp = ps;
        delete p;
        p = s;
    }

    //p最多有一个孩子，把孩子指针存放在c
    BinaryTreeNode<T> *c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;
    //删除p
    if (p == root)
        root = c;
    else
    {
        //p是pp的左孩子还是右孩�??
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
    return res;
}

template <class T>
int binarySearchTree<T>::find_rank(int rank)
{
    int res = 0;
    BinaryTreeNode<T> *p = root; //从根节点开始找
    while (p != NULL)
    {
        res ^= p->element;
        if (p->leftSize == rank)
            break;
        if (rank < p->leftSize)
            p = p->leftChild;
        else if (rank > p->leftSize)
        {
            rank -= p->leftSize + 1;
            p = p->rightChild;
        }
    }
    if (p == NULL)
    {
        return 0;
    }
    return res;
}

template <class T>
int binarySearchTree<T>::erase_rank(int rank)
{
    int res = 0;
    //查找名次为rank的节�??
    BinaryTreeNode<T> *p = root, *pp = NULL;
    while (p != NULL && p->leftSize != rank)
    {
        //移动p到它的下一个孩子节�??
        res ^= p->element;
        pp = p;
        if (rank < p->leftSize)
            p = p->leftChild;
        else if (rank > p->leftSize)
        {
            rank -= p->leftSize + 1;
            p = p->rightChild;
        }
    }
    if (p == NULL)
        return 0; //不存�??
    res ^= p->element;
    //找到对应rank的theKey
    int theKey = p->element;
    p = root;
    //因为删除了一个节点，所以要再次查找theKey，来更新因为删除操作而变化的leftSize
    while (p != NULL && p->element != theKey)
    {
        if (theKey < p->element)
        {
            p->leftSize--;
            p = p->leftChild;
        }
        else if (theKey > p->element)
        {
            p = p->rightChild;
        }
    }

    //重新组织树结�??
    //当p有两个孩子节点时的处�??
    if (p->leftChild != NULL && p->rightChild != NULL)
    {
        //两个孩子，转化为空或只有一个孩子，在p的右子树中寻找最小元�??
        BinaryTreeNode<T> *s = p->rightChild, *ps = p; //s的双�??
        while (s->leftChild != NULL)
        {
            //移动到最大的元素
            s->leftSize--;
            ps = s;
            s = s->leftChild;
        }
        //将最大的元素s移动到p，但不是简单的移动
        BinaryTreeNode<T> *q = new BinaryTreeNode<T>(s->element, p->leftChild, p->rightChild, p->leftSize);
        if (pp == NULL)
            root = q;
        else if (p == pp->leftChild)
        {
            pp->leftChild = q;
        }
        else
            pp->rightChild = q;
        if (ps == p)
            pp = q;
        else
            pp = ps;
        delete p;
        p = s;
    }
    //p最多有一个孩子，把孩子指针存放在c
    BinaryTreeNode<T> *c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;
    //删除p
    if (p == root)
        root = c;
    else
    {
        //p是pp的左孩子还是右孩�??
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
    return res;
}

template <class T>
void binarySearchTree<T>::output(BinaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        output(t->leftChild);
        cout << t->element << " ";
        output(t->rightChild);
    }
    else
        return;
}

int main()
{
    int m, a, b;
    binarySearchTree<int> tree;
    cin >> m;
    while (m--)
    {
        cin >> a >> b;
        if (a == 0)
            cout << tree.insert(b) << endl;
        else if (a == 1)
            cout << tree.find(b) << endl;
        else if (a == 2)
        {
            cout << tree.erase(b) << endl;
        }
        else if (a == 3)
            cout << tree.find_rank(b - 1) << endl;
        else if (a == 4)
            cout << tree.erase_rank(b - 1) << endl;
        cout<<"��ǰ�����������"<<endl;
        tree.output(tree.getroot());
        cout << endl;
    }
    system("pause");
    return 0;
}