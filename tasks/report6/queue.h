#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

template <typename elemT>
class queue
{
private:
    elemT *data;
    int top, base;
    int size;
    void outofrange() const
    {
        printf("Out of Range!\n");
        exit(-1);
    }

public:
    queue(int initsize = 100);
    ~queue();
    void enQueue(elemT e);
    elemT deQueue();
    bool isFull()
    {
        return (top + 1) % size == base;
    }
    bool isEmpty()
    {
        return top == base;
    }
};

template <typename elemT>
queue<elemT>::queue(int initsize)
{
    data = new elemT[initsize];
    top = base = 0;
    size = initsize;
}

template <typename elemT>
queue<elemT>::~queue()
{
    delete[] data;
    top = base = -1;
    size = 0;
}

template <typename elemT>
void queue<elemT>::enQueue(elemT e)
{
    if (isFull())
        outofrange();
    data[top] = e;
    top = (top + 1) % size;
}

template <typename elemT>
elemT queue<elemT>::deQueue()
{
    if (isEmpty())
        outofrange();
    top = (top - 1 + size) % size;
    return data[top];
}

#endif