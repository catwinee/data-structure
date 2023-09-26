#include <iostream>
using namespace std;
typedef struct LinkList
{
    int val;
    struct LinkList *next;
    LinkList() : val(0), next(nullptr){};
    LinkList(int x) : val(x), next(nullptr){};
} ListNode, *ListPtr;
ListPtr unique(ListPtr &head);
int main()
{
    ListPtr head = new ListNode(-1), p = head;
    for (int i = 1; i <= 8; ++i)
    {
        int x = i / 2 + i % 2;
        p->next = new ListNode(x);
        p = p->next;
    }
    head = unique(head);
    return 0;
}
ListPtr unique(ListPtr &head)
{
    ListPtr p = head->next, tmp = new ListNode;
    while (p)
    {
        if (!p->next)
            return head;
        if (p->next->val == p->val)
            tmp = p->next, p->next = p->next->next, delete tmp, tmp = nullptr;
        p = p->next;
    }
    return head;
}
