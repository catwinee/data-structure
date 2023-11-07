#ifndef _SEQQ_H_
#define _SEQQ_H_
#include <iostream>
#include <iomanip>
#include "queue.h"

template <class elemT>
class seqQueue : public Queue<elemT>
{
private:
    elemT *elem;
    int front;
    int rear;
    int size;
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
        for (int i = front, cnt = 0; i != rear;)
        {
            elem[cnt++] = tmp[i++];
            if (i == size)
                i = 0;
        }
        size += increment;
    }
    void outofrange() const
    {
        printf("ERROR: Out of range!\n");
        printf("Details: front=%d, rear=%d", front, rear);
        exit(-1);
    }
    void downflow() const
    {
        printf("ERROR: Downflow!\n");
        exit(-1);
    }

public:
    seqQueue();
    seqQueue(const seqQueue &q);
    ~seqQueue();
    void enQueue(const elemT &e);
    elemT deQueue();
    void Clear()
    {
        rear = front = -1;
    }
    int Len() const
    {
        return (rear - front + size) % size;
    }
    int Size() const
    {
        return size - 1;
    }
    bool isEmpty() const
    {
        return front == rear;
    }
    bool isFull() const
    {
        return front == (rear + 1) % size;
    }
    elemT getHead() const
    {
        if (isEmpty())
            downflow();
        return elem[front];
    }
    void Traverse() const
    {
        printf("Traverse:\n");
        if (isEmpty())
            return (void)printf("Empty seqQueue.\n");
        int i = front, cnt = 0;
        for (; i != rear; )
        {
            cout << setw(5) << elem[i++];
            i %= size;
            if (++cnt % 5 == 0)
                printf("\n");
        }
        if (cnt % 5)
            printf("\n");
    }
};

template <class elemT>
seqQueue<elemT>::seqQueue()
{
    size = 100;
    elem = new (nothrow) elemT[size];
    if (!elem)
        badalloc();
    front = rear = 0;
}

template <class elemT>
seqQueue<elemT>::seqQueue(const seqQueue &q)
{
    ;
}

template <class elemT>
seqQueue<elemT>::~seqQueue()
{
    Clear();
}

template <class elemT>
void seqQueue<elemT>::enQueue(const elemT &e)
{
    if (isFull())
        expand();
    elem[rear] = e;
    rear = ++rear % size;
}

template <class elemT>
elemT seqQueue<elemT>::deQueue()
{
    if (isEmpty())
        downflow();
    rear = (rear - 1 + size) % size;
    return elem[rear];
}

#endif