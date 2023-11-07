#include <iostream>
using namespace std;

#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include "list.h"

template <class elemT>
class seqList : public List<elemT>
{
private:
    elemT *elem;
    int size, length;
    void outofrange(int idx) const
    {
        printf("ERROR: Out of Range!\n");
        printf("Details: length=%d, idx=%d\n", length, idx);
        exit(-1);
    }
    void badalloc() const
    {
        printf("ERROR: Bad Alloc!\n");
        exit(-1);
    }
    void expand(int increment = 10)
    {
        elemT *tmp = elem;
        elem = new (nothrow) elemT[size + increment];
        if (!elem)
            badalloc();
        for (int i = 0; i < length; ++i)
            elem[i] = tmp[i];
        delete[] tmp;
        size += increment;
    }

public:
    //构造函数
    seqList(int initSize = 100);
    //复制构造函数
    seqList(const seqList &a);
    //析构函数
    ~seqList();

    //在索引 idx[0..n] 处插入元素 e
    void Insert(int idx, const elemT &e);
    //在表尾推入元素 e
    void Push_Back(const elemT &e);

    //删除索引 idx[0..n - 1] 处的元素, 将后面的元素前移, 返回被删除元素
    elemT Delete(int idx);
    //弹出表尾元素并返回元素值
    elemT Pop_Back();
    //清空但不销毁顺序表
    void Clear()
    {
        length = 0;
    }

    //修改索引为 idx[0..n - 1] 的元素为 e
    void Modify(int idx, const elemT &e);
    //反转顺序表
    void Inverse();

    //求长
    int Len() const
    {
        return length;
    }
    //求容量
    int Size() const
    {
        return size;
    }
    //判空
    bool isEmpty() const
    {
        return length;
    }
    //判满
    bool isFull() const
    {
        return size == length;
    }
    //访问索引为 idx[0..n - 1] 的元素
    elemT Visit(int idx) const
    {
        if (idx < 0 || idx >= length)
            outofrange(idx);
        return elem[idx];
    }
    //自表头起查找元素 e, 返回其索引, 不存在则返回 -1
    int Search(const elemT &e) const;
    //遍历
    void Traverse() const;
};

template <class elemT>
seqList<elemT>::seqList(int initSize)
{
    elem = new (nothrow) elemT[initSize];
    if (!elem)
        badalloc();
    size = initSize;
    length = 0;
};

template <class elemT>
seqList<elemT>::seqList(const seqList &a)
{
    elem = new (nothrow) elemT[a.size];
    if (!elem)
        badalloc();
    size = a.size;
    for (int i = 0; i < a.length; ++i)
        elem[i] = a.elem[i];
    length = a.length;
}

template <class elemT>
seqList<elemT>::~seqList()
{
    delete elem;
    size = length = -1;
}

template <class elemT>
void seqList<elemT>::Insert(int idx, const elemT &e)
{
    if (idx < 0 || idx > length)
        outofrange(idx);
    if (length == size)
        expand();
    for (int i = length; i > idx; --i)
        elem[i] = elem[i - 1];
    elem[idx] = e;
    ++length;
}

template <class elemT>
void seqList<elemT>::Push_Back(const elemT &e)
{
    if (length == size)
        expand();
    elem[length] = e;
    ++length;
}

template <class elemT>
elemT seqList<elemT>::Delete(int idx)
{
    if (idx < 0 || idx >= length)
        outofrange(idx);
    elemT e = elem[idx];
    for (int i = idx; i < length; ++i)
        elem[i] = elem[i + 1];
    --length;
    return e;
}

template <class elemT>
elemT seqList<elemT>::Pop_Back()
{
    if (isEmpty())
        outofrange(0);
    return elem[--length];
}

template <class elemT>
void seqList<elemT>::Modify(int idx, const elemT &e)
{
    if (idx < 0 || idx >= length)
        outofrange(idx);
    elem[idx] = e;
}

template <class elemT>
void seqList<elemT>::Inverse()
{
    for (int i = 0, j = length - 1; i < j; ++i, --j)
    {
        elemT tmp = elem[i];
        elem[i] = elem[j];
        elem[j] = tmp;
    }
}

template <class elemT>
int seqList<elemT>::Search(const elemT &e) const
{
    for (int i = 0; i < length; ++i)
        if (elem[i] == e)
            return i;
    return -1;
}

template <class elemT>
void seqList<elemT>::Traverse() const
{
    printf("Traverse:\n");
    if (isEmpty())
        return (void)printf("Empty!\n");
    for (int i = 0; i < length; ++i)
    {
        cout << setw(5) << elem[i];
        if (i % 5 == 4)
            cout << '\n';
    }
}

#endif