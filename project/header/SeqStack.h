#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_
#include "stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <class elemT>
class seqStack : public Stack<elemT>
{
private:
    elemT *elem;
    int top;
    int size;
    void downflow() const
    {
        printf("ERROR: Downflow!\n");
        printf("Details: size=%d", top);
        exit(-1);
    }
    void badalloc() const
    {
        printf("ERROR: Bad alloc!\n");
        exit(-1);
    }
    void expand(int increment = 10)
    {
        elemT *tmp = elem;
        elem = new (nothrow) elemT[size + increment];
        if (!elem)
            badalloc();
        for (int i = 0; i <= top; ++i)
            elem[i] = tmp[i];
        delete[] tmp;
        tmp = nullptr;
    }
public:
    seqStack(int initSize = 100);
    seqStack(const seqStack &s);
    ~seqStack();
    void Push(const elemT &e);
    elemT Pop();
    void Clear()
    {
        top = -1;
    }
    int Len() const
    {
        return top + 1;
    }
    int Size() const
    {
        return size;
    }
    bool isEmpty() const
    {
        return top == -1;
    }
    bool isFull() const
    {
        return top == size - 1;
    }
    elemT Top() const;
    void Traverse() const
    {
        printf("Traverse:\n");
        if (isEmpty())
            return (void)printf("Empty!\n");
        for (int i = 0; i <= top; ++i)
        {
            cout << setw(5) << elem[i];
            if (i % 5 == 4)
                cout << '\n';
        }
    }
};

template <class elemT>
seqStack<elemT>::seqStack(int initSize)
{
    elem = new (nothrow) elemT[initSize];
    if (!elem)
        badalloc();
    top = -1;
    size = initSize;
}
template <class elemT>
seqStack<elemT>::seqStack(const seqStack &s)
{
    elem = new (nothrow) elemT[s.size];
    if (!elem)
        badalloc();
    for (int i = 0; i <= s.top; ++i)
        elem[i] = s.elem[i];
    size = s.size;
    top = s.top;
}
template <class elemT>
seqStack<elemT>::~seqStack()
{
    delete[] elem;
    elem = nullptr;
    size = -1;
    top = -2;
}

template <class elemT>
void seqStack<elemT>::Push(const elemT &e)
{
    if (isFull())
        expand();
    elem[++top] = e;
}

template <class elemT>
elemT seqStack<elemT>::Pop()
{
    if (isEmpty())
        downflow();
    return elem[top--];
}

template <class elemT>
elemT seqStack<elemT>::Top() const
{
    if (isEmpty())
        downflow();
    return elem[top];
}

#endif