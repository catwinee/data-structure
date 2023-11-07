#include <iostream>
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

void f(int n)
{
    int tmp = n / 10;
    if (tmp)
        f(tmp);
    printf("%5d", n % 10);
}
int main()
{
    int n;
    cin >> n;
    printf("递归算法结果:\n");
    f(n);

    stk s;
    initStk(s);
    int tmp = n;
    while (tmp)
    {
        push(s, tmp % 10);
        tmp /= 10;
    }
    printf("\n消除递归结果:\n");
    while (!isEmpty(s))
        printf("%5d", pop(s));
    return 0;
}
