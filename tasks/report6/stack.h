#ifndef _MY_STACK_H
#define _MY_STACK_H

#include <iostream>
template <typename elemT>
class stack
{
private:
    elemT *base;
    int top;
    int size;
    void outofrange() const
    {
        printf("Out of Range!\n");
        exit(-1);
    }

public:
    stack(int initsize = 100);
    ~stack();
    elemT pop();
    void push(elemT e);
    elemT gettop();
    bool isEmpty() const
    {
        return top == -1;
    }
    bool isFull() const
    {
        return top == size - 1;
    }
};

template <typename elemT>
stack<elemT>::stack(int initsize)
{
    base = new elemT[initsize];
    top = -1;
    size = initsize;
}

template <typename elemT>
stack<elemT>::~stack()
{
    delete[] base;
    base = nullptr;
    top = -1;
    size = -1;
}

template <typename elemT>
void stack<elemT>::push(elemT e)
{
    if (isFull())
        outofrange();
    base[++top] = e;
    return;
}

template <typename elemT>
elemT stack<elemT>::pop()
{
    if (isEmpty())
        outofrange();
    return base[top--];
}

template <typename elemT>
elemT stack<elemT>::gettop()
{
    if (isEmpty())
        outofrange();
    return base[top];
}

#endif