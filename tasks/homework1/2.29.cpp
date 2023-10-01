#include <iostream>
using namespace std;
typedef struct
{
    int *elem;
    int length;
    int size;
} SqList;
SqList unionsql(SqList a, SqList b, SqList &c);
void unique(SqList &res, SqList c);
int main()
{
    SqList a, b, c;
    a.elem = new int, a.length = 0, a.size = 50;
    b.elem = new int, b.length = 0, b.size = 50;
    c.elem = new int, c.length = 0, c.size = 50;
    for (int i = 0; i < 20; ++i)
        a.elem[i] = 2 * i, ++a.length;
    for (int i = 0; i < 20; ++i)
        b.elem[i] = 4 * i, ++b.length;
    c = unionsql(a, b, c);
    for (int i = 0; i < c.length; ++i)
        cout << c.elem[i] << '\n';
    return 0;
}
SqList unionsql(SqList a, SqList b, SqList &res)
{
    int pa = 0, pb = 0, cnt = 0;
    while (pa < a.length && pb < b.length)
    {
        while (pb < b.length && a.elem[pa] > b.elem[pb])
            ++pb;
        if (pb == b.length)
            break;
        if (a.elem[pa] == b.elem[pb])
            res.elem[cnt++] = a.elem[pa];
        ++pa;
    }
    res.length = cnt;
    return res;
}
void unique(SqList &a, SqList b)
{
    int pa = 0, pb = 0, cnt = 0;
    while (pa < a.length && pb < b.length)
    {
        while (pb < b.length && a.elem[pa] > b.elem[pb])
            ++pb;
        if (pb == b.length)
            break;
        if (a.elem[pa] == b.elem[pb])
        {
            for (int i = pa; i < a.length; ++i)
                a.elem[i] = a.elem[i + 1];
            --a.length;
        }
        ++pa;
    }
}