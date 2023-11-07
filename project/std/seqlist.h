#include "astatus.h"

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef int elemtype;

typedef struct
{
    elemtype *elem;
    int size, length;
} seqList;
seqList initList(seqList &a)
{
    a.elem = new elemtype[LIST_INIT_SIZE];
    if (!a.elem)
    {
        printf("内存分配失败!\n");
        exit(OVERFLOW);
    }
    a.size = LIST_INIT_SIZE;
    a.length = 0;
    return a;
}
Status destroyList(seqList &a)
{
    delete [] a.elem;
    a.elem = nullptr;
    a.size = 0;
    a.length = 0;
    return OK;
}

bool isEmpty(seqList a)
{
    return a.length == 0;
}
bool isFull(seqList a)
{
    return a.size == a.length;
}

Status insert(seqList &a, int pos, elemtype e)
{
    --pos;
    if (a.length >= a.size)
    {
        elemtype *tmp = a.elem;
        a.elem = new int[a.size + LIST_INCREMENT];
        if (!a.elem)
        {
            printf("内存分配失败!\n");
            exit(OVERFLOW);
        }
        memcpy(a.elem, tmp, sizeof tmp);
        delete[] tmp;
        a.size += LIST_INCREMENT;
    }
    if (pos < 0 || pos > a.length) 
    {
        printf("插入位置为%d, 表长为%d, 不合法!\n", pos + 1, a.length);
        exit(ERROR);
    }
    for (int i = a.length; i > pos; --i)
        a.elem[i] = a.elem[i - 1];
    a.elem[pos] = e;
    ++a.length;
    return OK;
}
Status remove(seqList &a, int pos)
{
    --pos;
    if (pos < 0 || pos >= a.length)
    {
        printf("删除位置为%d, 表长为%d, 不合法!\n", pos + 1, a.length);
        exit(ERROR);
    }
    for (int i = pos; i <= a.length; ++i)
        a.elem[i] = a.elem[i + 1];
    --a.length;
    return OK;
}