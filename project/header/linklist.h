#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <iostream>
#include <iomanip>
using namespace std;
#include "list.h"

template <class elemT>
class linkList : public List<elemT>
{
private:
    struct Node
    {
        elemT val;
        struct Node *next;
        Node(Node *p = nullptr) : next(p){};
        Node(const elemT x, Node *p = nullptr) : val(x), next(p){};
    };
    Node *head;
    Node *tail;
    int length;

    void outofrange(const int &idx) const
    {
        printf("ERROR: Out of Range!\n");
        printf("Details: length=%d, idx=%d\n", length, idx);
        exit(-1);
    }
    void downflow() const
    {
        printf("ERROR: Downflow!\n");
        exit(-1);
    }

public:
    linkList();
    linkList(const linkList &a);
    linkList(const linkList &a, const linkList &b);
    ~linkList();
    void Insert(int idx, const elemT &e);
    void Push_Back(const elemT &e);
    void Push_Front(const elemT &e);
    elemT Delete(int idx);
    void Clear();
    elemT Pop_Back();
    elemT Pop_Front();
    int Remove(const elemT &e);
    void Modify(int idx, const elemT &e);
    void Inverse();
    int Len() const
    {
        return length;
    }
    bool isEmpty() const
    {
        return head == tail;
    }
    elemT Visit(int idx) const;
    int Search(const elemT &e) const;
    void Traverse() const;
};

template <class elemT>
linkList<elemT>::linkList()
{
    head = tail = new Node();
    length = 0;
}

template <class elemT>
linkList<elemT>::linkList(const linkList &a)
{
    head = tail = new Node();
    length = 0;
    Node *p = a.head->next;
    while (p)
    {
        Push_Back(p->val);
        p = p->next;
    }
    tail->next = nullptr;
}

template <class elemT>
linkList<elemT>::~linkList()
{
    Clear();
    delete head;
}

template <class elemT>
void linkList<elemT>::Insert(int idx, const elemT &e)
{
    if (idx < 0 || idx > length)
        outofrange(idx);
    if (idx == length)
        return Push_Back(e);
    else if (!idx)
        return Push_Front(e);
    Node *p = head;
    Node *tmp = new Node(e);
    while (idx--)
        p = p->next;
    tmp->next = p->next;
    p->next = tmp;
    ++length;
}

template <class elemT>
void linkList<elemT>::Push_Back(const elemT &e)
{
    tail->next = new Node(e);
    tail = tail->next;
    ++length;
}

template <class elemT>
void linkList<elemT>::Push_Front(const elemT &e)
{
    if (isEmpty())
        return Push_Back(e);
    head->next = new Node(e, head->next);
    ++length;
}

template <class elemT>
elemT linkList<elemT>::Delete(int idx)
{
    if (idx < 0 || idx >= length)
        outofrange(idx);
    if (idx == length - 1)
        return Pop_Back();
    else if (!idx)
        return Pop_Front();
    Node *p = head, *tmp;
    elemT e;
    while (idx--)
        p = p->next;
    tmp = p->next;
    e = tmp->val;
    p->next = tmp->next;
    delete tmp;
    --length;
    return e;
}

template <class elemT>
void linkList<elemT>::Clear()
{
    Node *p = head->next;
    while (p)
    {
        head->next = p->next;
        delete p;
        p = head->next;
    }
    tail = head;
    length = 0;
}

template <class elemT>
elemT linkList<elemT>::Pop_Back()
{
    if (isEmpty())
        downflow();
    int idx = --length;
    Node *p = head;
    elemT e;
    while (idx--)
        p = p->next;
    tail = p;
    p = p->next;
    e = p->val;
    delete p;
    tail->next = nullptr;
    return e;
}

template <class elemT>
elemT linkList<elemT>::Pop_Front()
{
    if (isEmpty())
        downflow();
    if (length == 1)
        return Pop_Back();
    Node *p = head->next;
    elemT e;
    head->next = p->next;
    e = p->val;
    delete p;
    --length;
    return e;
}

template <class elemT>
int linkList<elemT>::Remove(const elemT &e)
{
    int tmp = Search(e);
    if (tmp == -1)
        return -1;
    else
    {
        Delete(tmp);
        return tmp;
    }
}

template <class elemT>
void linkList<elemT>::Modify(int idx, const elemT &e)
{
    if (idx < 0 || idx >= length)
        outofrange(idx);
    Node *p = head;
    while (idx--)
        p = p->next;
    p->next->val = e;
}

template <class elemT>
void linkList<elemT>::Inverse()
{
    Node *p = head->next;
    int tmp = length;
    if (!tmp)
        return;
    while (p)
    {
        Push_Front(p->val);
        p = p->next;
    }
    while (tmp--)
        Pop_Back();
}

template <class elemT>
elemT linkList<elemT>::Visit(int idx) const
{
    if (idx < 0 || idx >= length)
        outofrange(idx);
    Node *p = head->next;
    while (idx--)
        p = p->next;
    return p->val;
}

template <class elemT>
int linkList<elemT>::Search(const elemT &e) const
{
    Node *p = head->next;
    int cnt = 0;
    while (p && p->val != e)
        p = p->next, ++cnt;
    if (p)
        return cnt;
    else
        return -1;
}

template <class elemT>
void linkList<elemT>::Traverse() const
{
    printf("Traverse: \n");
    Node *p = head->next;
    if (!p)
        return (void)printf("Empty!\n");
    int cnt = 0;
    while (p)
    {
        cout << setw(5) << p->val;
        p = p->next;
        if (++cnt % 5 == 0)
            printf("\n");
    }
    if (cnt % 5)
        printf("\n");
}

#endif