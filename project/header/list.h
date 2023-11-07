#ifndef _LIST_H
#define _LIST_H
#include <iostream>
using namespace std;

template <class elemT>
class List
{
private:
public:
    virtual void Insert(int idx, const elemT &e) = 0;
    virtual void Push_Back(const elemT &e) = 0;
    virtual elemT Delete(int idx) = 0;
    virtual elemT Pop_Back() = 0;
    virtual void Clear() = 0;
    virtual void Modify(int idx, const elemT &e) = 0;
    virtual void Inverse() = 0;
    virtual int Len() const = 0;
    // virtual int Size() const = 0; 顺序表特有
    virtual bool isEmpty() const = 0;
    // virtual bool isFull() const = 0; 顺序表特有
    virtual elemT Visit(int idx) const = 0;
    virtual int Search(const elemT &e) const = 0;
    // virtual void Traverse() const = 0;
};

#endif



