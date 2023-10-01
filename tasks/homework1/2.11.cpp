#include <iostream>
using namespace std;
int a[5] = {1, 2, 4, 5, 6};
typedef struct
{
    int *elem;
    int length;
    int size;
} SqList;
void insert(SqList &a, int x);
void extend(SqList &a);
int main()
{
    int n = 5;
    SqList a;
    a.elem = new int, a.length = 8, a.size = 50;
    if (!a.elem)
        exit(-2);
    a.elem[0] = 1, a.elem[1] = 2, a.elem[2] = 3, a.elem[3] = 4, a.elem[4] = 5, a.elem[5] = 6, a.elem[6] = 7, a.elem[7] = 9;
    insert(a, 8);
    return 0;
}
void insert(SqList &a, int x)
{
    if (a.length + 1 < a.size)//容量不足则扩容
        extend(a);
    for (int i = 0; i < a.length; ++i) //遍历
    {
        if (a.elem[i] > x) //寻找插入点
        {
            for (int j = a.length - 1; j >= i; --j)
                a.elem[j + 1] = a.elem[j];
            a.elem[i] = x;
            break;
        }
    }
    return;
}