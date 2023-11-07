#include <iostream>
using namespace std;

const int InitSize = 10;
typedef int elemT;

typedef struct
{
    elemT *elem;
    int topl, topr;
    int size;
} twS;

void inistack(twS &s) //初始化
{
    s.elem = (elemT *)malloc(InitSize * sizeof(elemT));
    if (!s.elem) //内存分配失败
    {
        printf("Bad alloc!\n");
        exit(-1);
    }
    s.size = InitSize;
    s.topl = 0, s.topr = s.size;
}

void resize(twS &s, int increment = 1) //扩容, 默认扩容10个元素
{
    elemT *tmp = s.elem;
    int size0 = s.topl, size1 = s.size - s.topr;
    s.elem = (elemT *)malloc((InitSize + increment) * sizeof(elemT));
    for (int i = 0; i != s.topl; ++i)
        s.elem[i] = tmp[i];
    for (int i = s.size; i != s.topr; --i)
        s.elem[i + increment] = tmp[i];
    s.size = InitSize + increment;
    s.topr = s.size - size1;
}

void push(twS &s, int i, const elemT &x)
{
    if (s.topr == s.topl) //如果发生上溢则扩容
        resize(s);
    if (i)
        s.elem[s.topr--] = x;
    else
        s.elem[s.topl++] = x;
}

void pop(twS &s, int i, elemT &x)
{
    if (i && s.topr == s.size || !i && !s.topl) //发生下溢报错
    {
        printf("Out of Range!\n");
        exit(-1);
    }
    if (i)
        x = s.elem[++s.topr];
    else
        x = s.elem[--s.topl];
}

void Traverse(twS s)
{
    printf("stack0:\n");
    for (int i = 0; i != s.topl; ++i)
        printf("%5d", s.elem[i]);
    printf("\nstack1:\n");
    for (int i = s.size; i != s.topr; --i)
        printf("%5d", s.elem[i]);
}

int tmp;
int main()
{
    twS s;
    inistack(s);
    for (int i = 0; i < 10; ++i)
    {
        push(s, i % 2, i);
    }
    // for (int i = 0; i < 10; ++i)
    // {
    //     pop(s, i % 2, tmp);
    // }
    Traverse(s);
    return 0;
}