#include <iostream>
using namespace std;

template <class T>
class arrayStack
{
public:
    arrayStack(int initialCapacity = 100);        //构造函数
    ~arrayStack() { delete[] stack; };            //析构函数
    bool empty() const { return stackTop == -1; } //判断stack是否为空
    int size() const { return stackTop + 1; }     //获得stack大小
    T &top() { return stack[stackTop]; }          //获得栈顶元素
    void pop() { stack[stackTop--].~T(); }        //弹出栈顶元素
    void push(const T &x);                        //压栈
    
private:
    int stackTop;    //当前栈顶
    int arrayLength; //栈容量
    T *stack;        //栈数组
};

template <class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <class T>
void arrayStack<T>::push(const T &x)
{
    if (stackTop == arrayLength - 1) //stack满了，需要开一个更大的空间
    {
        T *big = new T[2 * arrayLength];
        copy(stack, stack + arrayLength, big);
        delete[] stack;
        stack = big;
        arrayLength *= 2;
    }
    stack[++stackTop] = x;
}

double calculate(string a)
{
    arrayStack<double> num; //数字栈
    arrayStack<char> op;    //操作栈
    double number;
    for (int i = 0; i < a.size(); i++)
    {
        //如果是数字的话直接进栈
        if (a[i] >= '0' && a[i] <= '9')
        {
            number = a[i] - '0';
            while (a[i + 1] >= '0' && a[i + 1] <= '9') //判断是几位数字，并转换成整型存储
            {
                number = 10 * number + (a[i + 1] - '0');
                i++;
            }
            num.push(number); //数字进栈
        }
        else if (a[i] == '+' || a[i] == '-') //如果是加减的话，因为加减的优先级最低，因此只要遇到加减号，无论操作符栈中的什么运算符都要运算
        {
            while (!op.empty() && (op.top() == '+' || op.top() == '-' || op.top() == '*' || op.top() == '/'))
            {
                if (op.top() == '+')
                {
                    number = num.top();
                    num.pop();
                    number += num.top();
                    num.pop();
                }
                else if (op.top() == '-')
                {
                    number = -num.top();
                    num.pop();
                    number += num.top();
                    num.pop();
                }
                else if (op.top() == '*')
                {
                    number = num.top();
                    num.pop();
                    number *= num.top();
                    num.pop();
                }
                else if (op.top() == '/')
                {
                    double temp = num.top();
                    num.pop();
                    number = num.top() / temp;
                    num.pop();
                }
                num.push(number);
                op.pop();
            }
            //将当前操作符进栈
            op.push(a[i]);
        }
        //当前运算符是'('时，直接压入操作符栈
        else if (a[i] == '(')
        {
            op.push(a[i]);
        }
        //当前操作符是')'时，一直清除栈中的运算符号直至左括号
        else if (a[i] == ')')
        {
            while (op.top() != '(')
            {
                if (op.top() == '+')
                {
                    number = num.top();
                    num.pop();
                    number += num.top();
                    num.pop();
                }
                else if (op.top() == '-')
                {
                    number = -num.top();
                    num.pop();
                    number += num.top();
                    num.pop();
                }
                else if (op.top() == '*')
                {
                    number = num.top();
                    num.pop();
                    number *= num.top();
                    num.pop();
                }
                else if (op.top() == '/')
                {
                    double temp = num.top();
                    num.pop();
                    number = num.top() / temp;
                    num.pop();
                }
                num.push(number);
                op.pop();
            }
            //将遇到的左括号弹出去
            op.pop();
        }
        //当前运算符是乘除时，因为优先级高于加减，因此要判断最上面的是否是乘除，如果是乘除就运算，否则就直接进栈
        else if (a[i] == '*' || a[i] == '/')
        {
            while (!op.empty() && (op.top() == '*' || op.top() == '/'))
            {
                if (op.top() == '*')
                {
                    number = num.top();
                    num.pop();
                    number *= num.top();
                    num.pop();
                }
                else if (op.top() == '/')
                {
                    double temp = num.top();
                    num.pop();
                    number = num.top() / temp;
                    num.pop();
                }
                //将当前的结果入栈，并将运算符栈顶弹出
                num.push(number);
                op.pop();
            }
            //将当前的运算符压入栈
            op.push(a[i]);
        }
    }
    //遍历结束后，当栈中不是空的时候就继续运算，直到栈中空为止
    while (!op.empty())
    {
        if (op.top() == '+')
        {
            number = num.top();
            num.pop();
            number += num.top();
            num.pop();
        }
        else if (op.top() == '-')
        {
            number = -num.top();
            num.pop();
            number += num.top();
            num.pop();
        }
        else if (op.top() == '*')
        {
            number = num.top();
            num.pop();
            number *= num.top();
            num.pop();
        }
        else if (op.top() == '/')
        {
            double temp = num.top();
            num.pop();
            number = num.top() / temp;
            num.pop();
        }
        num.push(number);
        op.pop();
    }
    //返回最终结果
    number = num.top();
    return number;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        // for (int i = 1; i < s.size() - 1; i++)
        // {
        //     if (s[i] == '(' && ((s[i - 1] >= '0' && s[i - 1] <= '9') || s[i - 1] == ')'))
        //     {
        //         s.insert(i, "*");
        //     }
        //     if (s[i] == ')' && ((s[i + 1] >= '0' && s[i + 1] <= '9') || s[i + 1] == '('))
        //     {
        //         s.insert(i + 1, "*");
        //     }
        // }
        // cout<<s<<endl;
        printf("%.2f\n",calculate(s));
    }
    system("pause");
    return 0;
}

// 1+6/17+214+9/1+209+9+7/(95)-16-08-7-92+6-(0-5-28-7-95*(6-5526-2-7-5+67+69-100+30+2/1-6/6+5))
// 0-4-1/6*(1-(6/7)-4+6+2+61)-17+2-82+0-(4+6-61+(3-86/4-6-5)*6/4/8+7-14/95)-0/6+1-0-2+7-2+64-36+2/8+6+162