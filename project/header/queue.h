#ifndef _QUEUE_H_
#define _QUEUE_H_

template <class elemT>
class Queue
{
private:
public:
    virtual void enQueue(const elemT &e) = 0;
    virtual elemT deQueue() = 0;
    virtual void Clear() = 0;
    virtual int Len() const = 0;
    virtual int Size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual elemT getHead() const = 0;
    virtual void Traverse() const = 0;
};

#endif