#include <iostream>
using namespace std;
typedef struct
{
    int *elem;
    int length;
    int size;
} SqList;
int DeleteK(SqList &a, int i, int k);
int main()
{
    SqList a;
    a.elem = new int, a.length = 8, a.size = 50;
    if (!a.elem)
        exit(-2);
    a.elem[0] = 1, a.elem[1] = 2, a.elem[2] = 3, a.elem[3] = 4, a.elem[4] = 5, a.elem[5] = 6, a.elem[6] = 7, a.elem[7] = 8;
    DeleteK(a, 2, 3);
    return 0;
}
int DeleteK(SqList &a, int i, int k)
{
    //本过程从顺序存储结构的线性表a中删除第i个元素起的k个元素
    if (i <= 0 || i >= a.length || k < 0 || k > a.length - i)
        return -1; //参数不合法
    else
    {
        for (int j = i - 1; j < a.length - k - 1; ++j)
            a.elem[j] = a.elem[j + k];
        a.length -= k;
        return 0;
    } // DeleteK
}