#include <iostream>
using namespace std;

class Queue
{
public:
    Queue(int initialCapacity = 10);
    ~Queue() { delete[] queue; }
    void push(int x);
    void pop();
    void init(int l);
    void output();
    void solve();
    int size();
    int getfront();

private:
    int front;  //队首前一个位置
    int back;   //队尾
    int length; //队列长度
    int *queue; //队列指针
};

Queue::Queue(int initialCapacity)
{
    length = initialCapacity;
    queue = new int[length];
    front = 0;
    back = 0;
}

void Queue::push(int x)
{
    //如果需要，则增加数组长度
    if ((back + 1) % length == front) //加倍数组长度
    {
        //分配新的数组空间
        int *newqueue = new int[2 * length];
        //把原数组复制到新数组
        int start = (front + 1) % length;
        if (start < 2)
        {
            //没有形成环
            copy(queue + start, queue + start + length - 1, newqueue);
        }
        else
        {
            //队列形成环
            copy(queue + start, queue + length, newqueue);
            copy(queue, queue + back + 1, newqueue + length - start);
        }
        //这是新的队列的首和尾的元素位置
        front = 2 * length - 1;
        back = length - 2;
        length *= 2;
        delete[] queue;
        queue = newqueue;
    }
    back = (back + 1) % length;
    queue[back] = x;
}

void Queue::pop()
{
    //从队首弹出一个元素
    front = (front + 1) % length;
    ~queue[front];
}

void Queue::init(int n)
{
    for (int i = 1; i <= n; i++)
        push(i);
}

void Queue::output()
{
    for (int i = (front + 1) % length; i < (front + 1) % length + size(); i++)
    {
        cout << queue[i];
    }
    cout << endl;
}

int Queue::size()
{
    //获得当前数组的元素个数
    return (back - front + length) % length;
}

int Queue::getfront()
{
    //获得队首元素
    return queue[(front + 1) % length];
}

void Queue::solve()
{
    while (size() >= 2)
    {
        pop();
        int temp = getfront();
        pop();
        push(temp);
    }
    output();
}

int main()
{
    int n;
    cin >> n;
    Queue q;
    q.init(n);
    q.solve();
    //system("pause");
    return 0;
}