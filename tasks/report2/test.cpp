#include <iostream>
#include <iomanip>
using namespace std;
typedef struct
{
    int n, r1, r2;
} ElemTp; //入栈元素类型
// r1, r2分别存储fib(n-1)和fib(n-2)的返回值
// r1, r2同时也兼作标志变量
// r1, r2初值为-1表示返回值尚未求得, 需进行入栈操作
//以下为用堆栈实现的非递归算法
int fib(int n)
{
    ElemTp *s = new ElemTp[n]; //建栈,递归深度不会超n
    int top = -1;              //置空栈
    ElemTp a = {n, -1, -1};    //-1表示函数返回值未求得
    s[++top] = a;              //(n, -1, -1)压栈
    int r;                     //临时变量r用于计算fib(n-1)+fib(n-2)等
    while (1)
        if (s[top].r1 != -1 && s[top].r2 != -1) //栈顶r1, r2均已求得
        {
            r = s[top].r1 + s[top].r2; //计算fib(n-1)+fib(n-2)
            --top;
            if (top == -1)
                break; //退栈, 栈空退出循环
            if (s[top].r1 == -1)
                s[top].r1 = r;
            else
                s[top].r2 = r;
        }
        else if (s[top].n <= 1)
        {
            s[top].r1 = 1;
            s[top].r2 = 0;
        }
        //栈顶为(x, 1, 0), 即x≤1时, 可以开始返回算函数值
        else
        {
            a.n = s[top].n - 1;
            a.r1 = a.r2 = -1; //生成(n-1, -1, -1)
            if (s[top].r1 != -1)
                a.n--;    //生成(n-2, -1, -1)
            s[++top] = a; //入栈
        }
    delete[] s; //退出while循环后删除栈
    return r;   //返回fib(n)
}
int main()
{
    int i;
    for (i = 0; i < 20; i++) //输出Fibanacci数列前20项值
    {
        cout << setw(12) << fib(i); //输出每项域宽12列
        if (i % 5 == 4)
            cout << endl; //每输出5项换行
    }
    return 0;
}