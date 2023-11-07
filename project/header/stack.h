#ifndef _STACK_H_
#define _STACK_H_

template <class elemT>
class Stack
{
private:
public:
    virtual void Push(const elemT &e) = 0;
    virtual elemT Pop() = 0;
    virtual void Clear() = 0;
    virtual int Len() const = 0;
    // virtual int Size() const = 0;
    virtual bool isEmpty() const = 0;
    // virtual bool isFull() const = 0;
    virtual elemT Top() const = 0;
    virtual void Traverse() const = 0;
};

#endif