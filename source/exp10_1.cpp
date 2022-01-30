#include <iostream>
using namespace std;

template <class T>
class minHeap
{
public:
    minHeap(int initialCapacity = 10);
    ~minHeap() { delete[] heap; }
    const T &top() { return heap[1]; }
    void push(const T &);
    void pop();
    void initialize(T *theHeap, int theSize);

private:
    T *heap;         //一个类型为T的一维数组
    int arrayLength; //数组heap的容量
    int heapSize;    //堆的元素个数
};

template <class T>
minHeap<T>::minHeap(int initialCapacity)
{
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template <class T>
void minHeap<T>::push(const T &theElement) //把元素theElement加入堆
{
    //必要时增加数组长度
    if (heapSize == arrayLength - 1) //数组长度加倍
    {
        T *temp = new T[2 * arrayLength];
        copy(heap, heap + arrayLength, temp);
        delete[] heap;
        heap = temp;
        arrayLength *= 2;
    }
    //为元素theElement寻找插入位置
    //currentNode从叶子节点向上移动
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement)
    {
        //不能把元素theElement插入在heap[currentNode]
        heap[currentNode] = heap[currentNode / 2]; //把元素向下移动
        currentNode /= 2;                          //currentNode移向双亲
    }
    heap[currentNode] = theElement;
}

template <class T>
void minHeap<T>::pop() //删除最大元素
{
    //删除最大元素
    heap[1].~T();
    //删除最后一个元素，然后重新建堆
    T lastElement = heap[heapSize--];
    //从根开始，为最后一个元素寻找位置
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        //heap[child]应该是currentNode的更大的孩子
        if (child < heapSize && heap[child] > heap[child + 1])
            child++;
        //可以把lastElement放在heap[currentNode]吗？
        if (lastElement <= heap[child])
            break; //可以
        //不可以
        heap[currentNode] = heap[child]; //把孩子child向上移动
        currentNode = child;             //向下移动一层寻找位置
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template <class T>
void minHeap<T>::initialize(T *theHeap, int theSize) //在数组theHeap[1:theSize]中建小根堆
{
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    arrayLength = theSize + 1;
    //堆化
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        //为元素rootElement寻找位置
        int child = 2 * root; //孩子child的双亲是元素rootElement的位置
        while (child <= heapSize)
        {
            //heap[child]应该是兄弟中的较小者
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            //可以把元素rootElement放在heap[child/2]吗
            if (rootElement <= heap[child])
                break; //可以
            //不可以
            heap[child / 2] = heap[child]; //把孩子向上移
            child *= 2;                    //移到下一层
        }
        heap[child / 2] = rootElement;
    }
}

int main()
{
    int n, m, t;
    cin >> n;
    minHeap<int> minheap(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> t;
        minheap.push(t);
    }
    cout << minheap.top() << endl;
    cin >> m;
    while (m--)
    {
        int op, num;
        cin >> op;
        if (op == 1) //插入操作
        {
            cin >> num;
            minheap.push(num);
            cout << minheap.top() << endl;
        }
        else if (op == 2) //删除操作
        {
            minheap.pop();
            cout << minheap.top() << endl;
        }
        else if (op == 3) //排序操作
        {
            cin >> n;
            minHeap<int> minheap_t(n);
            for (int i = 1; i <= n; i++)
            {
                cin >> t;
                minheap_t.push(t);
            }
            while (n--)
            {
                cout << minheap_t.top() << " ";
                minheap_t.pop();
            }
            cout << endl;
        }
    }
    //system("pause");
    return 0;
}