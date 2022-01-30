#include <iostream>
#define maxx 200000
using namespace std;

struct matrixTerm
{
    int row, col, value;
    matrixTerm &operator=(matrixTerm &x)
    {
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    }
};

class sparseMatrix
{
    friend ostream &operator<<(ostream &out, sparseMatrix &x); //输出矩阵
public:
    sparseMatrix(int row, int col);              //构造函数
    ~sparseMatrix() { delete[] terms; }          //析构函数
    sparseMatrix &operator=(sparseMatrix &x);    //重载=操作符
    void init(int row, int col);                 //初始化/重置矩阵
    void multiply(sparseMatrix &x);              //乘法函数
    void add(sparseMatrix &x);                   //加法函数
    void transpose();                            //转置函数
    void insert(int index, const matrixTerm &x); //插入函数
    void pushback(int x, int y, int z);          //插入函数
    void output();

private:
    int rows, cols, tot;
    matrixTerm *terms;
};

//构造函数
sparseMatrix::sparseMatrix(int row, int col)
{
    terms = new matrixTerm[maxx];
    rows = row;
    cols = col;
    tot = 0;
}

//重载=操作符
sparseMatrix &sparseMatrix::operator=(sparseMatrix &x)
{
    rows = x.rows;
    cols = x.cols;
    tot = x.tot;
    for (int i = 0; i < tot; i++)
    {
        terms[i] = x.terms[i];
    }
    return *this;
}

//重载<<输出
ostream &operator<<(ostream &out, sparseMatrix &x)
{
    cout << x.rows << " " << x.cols << endl;
    for (int i = 1; i < x.rows + 1; i++)
    {
        for (int j = 1; j < x.cols + 1; j++)
        {
            bool f = true;
            for (int k = 0; k < x.tot; k++)
            {
                if (x.terms[k].row == i && x.terms[k].col == j)
                {
                    cout << x.terms[k].value << " ";
                    f = false;
                }
            }
            if (f)
                cout << 0 << " ";
        }
        cout << endl;
    }
    return out;
}

void sparseMatrix::output()
{
    int cnt=0;
    cout << rows << " " << cols << endl;
    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < cols + 1; j++)
        {
            if (cnt < tot && terms[cnt].row == i && terms[cnt].col == j)
            { //如果此时该位置存在元素 输出即可
                cout << terms[cnt].value << ' ';
                cnt++;
            }
            else
                cout << 0 << ' ';
        }
        cout << endl;
    }
}

//初始化/重置矩阵
void sparseMatrix::init(int row, int col)
{
    rows = row;
    cols = col;
    tot = 0;
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= col; j++)
        {
            int temp;
            cin >> temp;
            if (temp != 0)
            {
                terms[tot].row = i;
                terms[tot].col = j;
                terms[tot].value = temp;
                tot++;
            }
        }
    }
}

//矩阵乘法函数
void sparseMatrix::multiply(sparseMatrix &x)
{
    if (cols != x.rows)
    { //维度不匹配，矩阵无法相乘
        *this = x;
        cout << -1 << endl;
        return;
    }
    sparseMatrix res(rows, x.cols); //结果矩阵
    int numrow[maxx];               //numrow[i]表示x矩阵第i行中有多少个非零的数
    int prerow[maxx];               //prerow[i]表示x矩阵前i-1行已经一共有多少个非零的数了
    int lineans[maxx];              //暂存一行的结果
    for (int i = 1; i <= x.rows; i++)
    {
        numrow[i] = 0; //初始化为0
    }
    for (int i = 0; i < x.tot; i++)
    {
        if (x.terms[i].value != 0)
        {
            numrow[x.terms[i].row]++; //计算这一行有几个非零数
        }
    }
    prerow[1] = 0;
    for (int i = 2; i <= x.rows; i++)
    {
        prerow[i] = prerow[i - 1] + numrow[i - 1]; //计算prerow数组
    }
    int a = 0;
    for (int i = 1; i <= rows && a < tot; i++)
    {
        for (int j = 1; j <= x.cols; j++)
        {
            lineans[j] = 0;
        }
        while (a < tot && terms[a].row == i)
        {
            int col_temp = terms[a].col; //被乘矩阵的每一列
            if (numrow[col_temp] != 0)   //如果乘矩阵的对应行中有非零的数
            {
                for (int b = prerow[col_temp]; b < prerow[col_temp] + numrow[col_temp]; b++)
                {
                    lineans[x.terms[b].col] += terms[a].value * x.terms[b].value;
                }
            }
            a++;
        }
        for (int j = 1; j <= x.cols; j++)
        {
            if (lineans[j] != 0)
            {
                res.terms[res.tot].value = lineans[j];
                res.terms[res.tot].row = i;
                res.terms[res.tot].col = j;
                res.tot++;
            }
        }
    }
    *this = res;
}

//矩阵加法函数
void sparseMatrix::add(sparseMatrix &x)
{
    sparseMatrix res(rows, cols); //结果矩阵
    if (rows != x.rows || cols != x.cols)
    {
        *this = x;
        cout << -1 << endl;
        return;
    }
    int restot = 0;   //结果系数矩阵中有多少个数
    int a = 0, b = 0; //a,b分别遍历被加数和加数,下面类似于双指针算法
    while (a != tot && b != x.tot)
    {
        int aa = terms[a].row * cols + terms[a].col;
        int bb = x.terms[b].row * cols + x.terms[b].col;
        //看看a和b的位置谁靠前
        if (aa < bb)
        {
            res.insert(restot++, terms[a]); //如果a<b说明这个位置上b是0，结果直接是a
            a++;
        }
        else if (aa > bb)
        {
            res.insert(restot++, x.terms[b]); //如果a>b说明这个位置上a是0，结果直接是b
            b++;
        }
        else if (aa == bb)
        {
            if (terms[a].value + x.terms[b].value != 0)
            {
                matrixTerm temp;
                temp.row = terms[a].row;
                temp.col = terms[a].col;
                temp.value = terms[a].value + x.terms[b].value;
                res.insert(restot++, temp);
            }
            a++;
            b++;
        }
    }
    for (; a < tot; a++)
    {
        res.insert(restot++, terms[a]);
    }
    for (; b < x.tot; b++)
    {
        res.insert(restot++, x.terms[b]);
    }
    *this = res;
}

void sparseMatrix::insert(int pos, const matrixTerm &x)
{

    copy(terms + pos, terms + tot, terms + pos + 1); //先把要插入位置后面元素向后挪一位
    //copy_backward(terms + pos, terms + tot, terms + tot + 1);
    terms[pos].row = x.row;
    terms[pos].col = x.col;
    terms[pos].value = x.value;
    tot++;
}

void sparseMatrix::transpose()
{
    sparseMatrix res(cols, rows);
    //设置转置矩阵特征
    res.tot = tot;
    res.rows = cols;
    res.cols = rows;
    //初始化以实现转置
    int *colSize = new int[cols + 1];
    int *rowNext = new int[cols + 1];
    //寻找*this中每一列的项的数目
    for (int i = 1; i <= cols; i++)
    {
        colSize[i] = 0;
    }
    for (int i = 0; i < tot; i++)
    {
        colSize[terms[i].col]++;
    }
    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++)
    {
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];
    }
    for (int i = 0; i < tot; i++)
    {
        int j = rowNext[terms[i].col]++;
        res.terms[j].row = terms[i].col;
        res.terms[j].col = terms[i].row;
        res.terms[j].value = terms[i].value;
    }
    *this = res;
}

//插入函数
void sparseMatrix::pushback(int x, int y, int z)
{
    matrixTerm temp;
    temp.row = x;
    temp.col = y;
    temp.value = z;
    terms[tot] = temp;
    tot++;
}

int main()
{
    ios::sync_with_stdio(false);
    int w;
    cin >> w;
    int row, col, op, t, x, y, z;
    sparseMatrix a(0, 0);
    while (w--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> row >> col;
            a.init(row, col);
        }
        else if (op == 2)
        {
            cin >> row >> col;
            cin >> t;
            sparseMatrix b(row, col);
            for (int i = 0; i < t; i++)
            {
                cin >> x >> y >> z;
                b.pushback(x, y, z);
            }
            a.multiply(b);
        }
        else if (op == 3)
        {
            cin >> row >> col;
            cin >> t;
            sparseMatrix b(row, col);
            for (int i = 0; i < t; i++)
            {
                cin >> x >> y >> z;
                b.pushback(x, y, z);
            }
            a.add(b);
        }
        else if (op == 4)
        {
            //cout << a;
            a.output();
        }
        else if (op == 5)
        {
            a.transpose();
        }
    }
    //system("pause");
    return 0;
}

// //样例输入
// 7
// 1
// 5 5
// 2 1 0 0 0
// 0 0 -1 0 0
// 0 0 0 0 0
// 0 0 -1 0 0
// 0 0 0 0 0
// 3
// 5 5
// 4
// 2 2 5
// 3 5 8
// 4 4 2
// 5 3 4
// 4
// 2
// 5 5
// 3
// 1 1 8
// 2 4 4
// 3 5 2
// 4
// 5
// 4
// //样例输出
// 5 5
// 2 1 0 0 0
// 0 5 -1 0 0
// 0 0 0 0 8
// 0 0 -1 2 0
// 0 0 4 0 0
// 5 5
// 16 0 0 4 0
// 0 0 0 20 -2
// 0 0 0 0 0
// 0 0 0 0 -2
// 0 0 0 0 8
// 5 5
// 16 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 4 20 0 0 0
// 0 -2 0 -2 8