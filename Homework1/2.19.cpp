#include <iostream>
using namespace std;
typedef struct LinkList
{
    int val;
    struct LinkList *next;
    LinkList() : val(0), next(nullptr){};
    LinkList(int x) : val(x), next(nullptr){};
} LinkNode, *LinkPtr;
typedef struct
{
    int *elem;
    int length;
    int size;
} SqList;
LinkPtr trim(LinkPtr &head, int mink, int maxk);
SqList trim(SqList &a, int mink, int maxk);
int main()
{
    LinkPtr head = new LinkNode(-1), p = head;
    for (int i = 1; i <= 8; ++i)
    {
        p->next = new LinkNode(i);
        p = p->next;
    }
    SqList a;
    a.elem = new int;
    a.length = 0, a.size = 50;
    for (int i = 0; i < 8; ++i)
        a.elem[i] = i + 1, ++a.length;
    int mink = 2, maxk = 7;
    head = trim(head, mink, maxk);
    a = trim(a, mink, maxk);
    return 0;
}
LinkPtr trim(LinkPtr &head, int mink, int maxk)
{
    LinkPtr p = head->next, tmp;
    while (p && p->val <= mink)
        tmp = p, p = p->next;
    delete head;
    head = p;
    while (p && p->val < maxk - 1)
        tmp = p, p = p->next;
    delete p->next;
    p->next = nullptr;
    return head;
}
SqList trim(SqList &a, int mink, int maxk)
{
    int i;
    for (i = 0; i < a.length; ++i)
        if (a.elem[i] > mink)
            break;
    a.elem = a.elem + i;
    a.length -= i;
    for (i = 0; i < a.length; ++i)
        if (a.elem[i] > maxk)
        {
            --i;
            break;
        }
    a.length = i;
    return a;
}