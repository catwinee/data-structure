#include <iostream>
#include <string.h>
using namespace std;

const int initStackSize = 10000;
typedef struct Stack
{
    int *elem;
    int top;
    int size;
} stk;
void initStk(stk &s)
{
    s.elem = (int *)malloc(initStackSize * sizeof(int));
    if (!s.elem)
    {
        printf("Bad Alloc!\n");
        exit(-1);
    }
    s.top = -1;
    s.size = initStackSize;
}
bool isEmpty(const stk &s)
{
    return s.top == -1;
}
bool isFull(const stk &s)
{
    return s.top == s.size;
}
void push(stk &s, const int &e)
{
    if (isFull(s))
    {
        printf("Overflow!\n");
        exit(-1);
    }
    s.elem[++s.top] = e;
}
int pop(stk &s)
{
    if (isEmpty(s))
    {
        printf("Downflow!\n");
        exit(-1);
    }
    int e = s.elem[s.top--];
    return e;
}

int f(int n) //递归法
{
    return n ? n * f(n / 2) : 1;
}

int main()
{
    int n;
    cin >> n;
    printf("递归算法结果:\n");
    cout << f(n) << '\n';

    stk s;
    int a[10000];
    initStk(s), push(s, n);
    memset(a, -1, sizeof a);
    a[0] = 1;
    while (!isEmpty(s))
    {
        int tmp = pop(s);
        if (a[tmp] != -1)
            continue;
        push(s, tmp);
        if (a[tmp / 2] == -1)
            push(s, tmp / 2);
        else
            a[tmp] = tmp * a[tmp / 2];
    }
    printf("消除递归结果:\n");
    cout << a[n] << '\n';

    return 0;
}