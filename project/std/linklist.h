#include "astatus.h"
#include <iostream>
//该链表带头指针
typedef int elemtype;

typedef struct ListNode
{
    elemtype val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr){};
} ListNode, *ListPtr;

Status initList(ListPtr &head)
{
    head = new ListNode(-1);
    head->next = nullptr;
    return OK;
}
Status clearList(ListPtr &head)
{
    ListPtr p;
    while (head->next)
    {
        p = head->next;
        head->next = p->next;
        delete p;
    }
    return OK;
}
Status append(ListPtr &head, elemtype e)
{
    ListPtr p = head;
    while (p->next)
        p = p->next;
    p->next = new ListNode(e);
    return OK;
}
Status insert(ListPtr &head, int pos, elemtype e)
{
    if (pos < 1)
    {
        puts("插入位置不合法!");
        return ERROR;
    }
    ListPtr p = head;
    --pos;
    while (p->next && pos)
    {
        p = p->next;
        --pos;
    }
    ListPtr tmp = new ListNode(e);
    if (!p->next)
        p->next = tmp;
    else
    {
        tmp->next = p->next;
        p->next = tmp;
    }
    return OK;
}
void printList(ListPtr &head)
{
    if (!head->next)
        puts("链表为空!");
    ListPtr p = head->next;
    while (p)
    {
        cout << p->val << ' ';
        p = p->next;
    }
    return;
}