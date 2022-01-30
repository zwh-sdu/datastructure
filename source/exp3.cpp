#include <iostream>
#include <string>
using namespace std;

struct student
{ //定义结构体存放每个学生的信息
    string name;
    long long phone;
    long long classnum;
    long long dorm;
};

class studentlist
{
public:
    ~studentlist() { delete[] s; };
    void init(student *stu);                                                           //初始化类内的s数组
    void insert(string _name, long long _phone, long long _classnum, long long _dorm); //插入一个学生信息
    void delet(string _name);                                                          //删除一个学生
    void edit(string _name, long long op, long long num);                              //修改一个学生信息
    long long search(string _name);                                                    //查找学生姓名
    long long output(long long _classnum);                                             //输出一个班学生宿舍号的异或值
private:
    int tot; //当前一共有多少个学生
    student *s;
};

void studentlist::init(student *stu)
{
    tot = 0;
    s = stu;
}

void studentlist::insert(string _name, long long _phone, long long _classnum, long long _dorm)
{
    s[tot].name = _name;
    s[tot].phone = _phone;
    s[tot].classnum = _classnum;
    s[tot].dorm = _dorm;
    tot++;
}
void studentlist::delet(string _name)
{
    int i;
    for (i = 0; i < tot; i++)
    {
        if (s[i].name == _name)
            break;
    }
    copy(s + i + 1, s + tot, s + i);
    tot--;
}
void studentlist::edit(string _name, long long op, long long num)
{
    for (int i = 0; i < tot; i++)
    {
        if (s[i].name == _name)
        {
            switch (op)
            {
            case 1:
                s[i].phone = num;
                break;
            case 2:
                s[i].classnum = num;
                break;
            case 3:
                s[i].dorm = num;
            }
        }
    }
}
long long studentlist::search(string _name)
{
    for (int i = 0; i < tot; i++)
    {
        if (s[i].name == _name)
            return 1;
    }
    return 0;
}
long long studentlist::output(long long _classnum)
{
    long long res = 0;
    for (int i = 0; i < tot; i++)
    {
        if (s[i].classnum == _classnum)
            res = res ^ s[i].dorm;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    studentlist l;
    student *stu = new student[n];
    l.init(stu);
    string name;
    long long phone, num;
    long long classnum, dorm, op, k;
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        switch (k)
        {
        case 0:
            cin >> name >> phone >> classnum >> dorm;
            l.insert(name, phone, classnum, dorm);
            break;
        case 1:
            cin >> name;
            l.delet(name);
            break;
        case 2:
            cin >> name >> op >> num;
            l.edit(name, op, num);
            break;
        case 3:
            cin >> name;
            cout << l.search(name) << endl;
            break;
        case 4:
            cin >> classnum;
            cout << l.output(classnum) << endl;
            break;
        }
    }
    system("pause");
    return 0;
}