#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_
#include "stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <class elemT>
class linkStack : public Stack<elemT>
{
private:
    struct Node
    {
        elemT val;
        struct Node *next;
        Node(Node *p = nullptr) : next(p){};
        Node(const elemT &x, Node *p = nullptr) : val(x), next(p){};
    };
    Node *top;
    void downflow() const
    {
        printf("ERROR: Downflow!\n");
        exit(-1);
    }

public:
    linkStack();
    linkStack(const linkStack &s);
    ~linkStack();
    void Push(const elemT &e)
    {
        Node *p = new Node(e, top);
        top = p;
    }
    elemT Pop();
    void Clear()
    {
        Node *tmp;
        while (top)
        {
            tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    int Len() const
    {
        Node *p = top;
        int cnt = 0;
        while (p)
        {
            ++cnt;
            p = p->next;
        }
        return cnt;
    }
    bool isEmpty() const
    {
        return top == nullptr;
    }
    elemT Top() const
    {
        if (isEmpty())
            downflow();
        return top->val;
    }
    void Traverse() const;
};

template <class elemT>
linkStack<elemT>::linkStack()
{
    top = nullptr;
}

template <class elemT>
linkStack<elemT>::linkStack(const linkStack &s)
{
    if (s.isEmpty())
    {
        printf("Empty stack constructed.\n");
        exit(-1);
    }
    top = new Node(s.top->val);
    Node *p = s.top->next, *pr = top;
    while (p)
        pr->next = new Node(p->val), pr = pr->next, p = p->next;
}

template <class elemT>
linkStack<elemT>::~linkStack()
{
    Clear();
}

template <class elemT>
elemT linkStack<elemT>::Pop()
{
    if (isEmpty())
        downflow();
    elemT e = top->val;
    Node *tmp = top;
    top = tmp->next;
    delete tmp;
    return e;
}

template <class elemT>
void linkStack<elemT>::Traverse() const
{
    if (!top)
        return (void)printf("Emtpy linkStack.\n");
    linkStack<elemT> tmp, tmp2(*this);
    Node *p = tmp2.top;
    while (p)
    {
        tmp.Push(tmp2.Pop());
        p = tmp2.top;
    }
    int cnt = 0;
    Node *pr = tmp.top;
    while (pr)
    {
        cout << setw(5) << pr->val;
        pr = pr->next;
        if (++cnt % 5 == 0)
            printf("\n");
    }
    if (cnt % 5)
        printf("\n");
}

#endif