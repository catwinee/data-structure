#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;

#define Stack_init_size 100
#define Stackincrement 10
#define Status int
#define OK 0
#define OVERFLOW -2
#define ERROR -1

ofstream outputFile;
int num[45];

typedef struct
{
    int *top;
    int *base;
    int stacksize;
} sqStack;

Status initialStack(sqStack &s) //初始化链表
{
    s.base = new int[Stack_init_size];
    if (!s.base) //避免内存分配失败
        exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = Stack_init_size;
    return OK;
}
Status push(sqStack &s, int e) //向栈s压入一个元素e
{
    if (s.top - s.base >= s.stacksize) //避免上溢
    {
        s.base = (int *)realloc(s.base, (s.stacksize + Stackincrement) * sizeof(int));
        s.top = s.base + s.stacksize;
        s.stacksize += Stackincrement;
    }
    *s.top++ = e;
    return OK;
}
Status pop(sqStack &s, int &e) //从栈s中弹出一个元素并赋值给e
{
    if (s.top == s.base) //避免下溢
        return ERROR;
    e = *--s.top;
    return OK;
}
Status getTop(sqStack &s, int &e) //取栈顶但不弹出, 赋值给e
{
    if (s.top == s.base) //避免下溢
        return ERROR;
    e = *(s.top - 1);
    return OK;
}

int main()
{
    outputFile.open("b.txt");
    memset(num, -1, sizeof num);
    num[0] = 0, num[1] = 1; //已知量只有f(0)和f(1), 其余暂定为-1
    sqStack s;
    initialStack(s);
    push(s, 39); //推入未知量

    while (s.top != s.base) //当栈不为空
    {
        int tmp;
        getTop(s, tmp);
        if (tmp % 2)
        {
            int f1 = tmp / 2, f2 = tmp - 2;
            if (num[f1] == -1 || num[f2] == -1) //若不能计算则继续推入未知量
                push(s, f1), push(s, f2);
            else //可以计算则弹出并记录
            {
                pop(s, tmp);
                num[tmp] = num[f1] + num[f2];
            }
        } // tmp为奇数
        else
        {
            int f = tmp / 2;
            if (num[f] == -1) //不能计算推入
                push(s, f);
            else //可以计算弹出
            {
                pop(s, tmp);
                num[tmp] = num[f];
            }
        } // tmp为偶数
        if (num[tmp - 1] == -1)
            push(s, tmp - 1);
    } // while
    for (int i = 0; i <= 39; ++i)
    {
        outputFile << setw(6) << num[i];
        if (i % 5 == 4)
            outputFile << '\n';
    } // for
    outputFile.close();
    return 0;
}