#include <iostream>
using namespace std;
typedef struct LinkList
{
    int val;
    struct LinkList *next;
    LinkList() : val(0), next(nullptr){};
    LinkList(int x) : val(x), next(nullptr){};
} ListNode, *ListPtr;
ListPtr reverse(ListPtr &head);
int main()
{
    ListPtr head = new ListNode(-1), p = head;
    for (int i = 1; i <= 3; ++i)
    {
        p->next = new ListNode(i);
        p = p->next;
    }
    head = reverse(head);
    return 0;
}
ListPtr reverse(ListPtr &head)
{
    ListPtr p = head->next, pr;
    bool f = 1;
    while (p)
    {
        ListPtr tmp = new ListNode(p->val);
        tmp->next = head->next;
        head->next = tmp;
        if (f)
        {
            f = 0, pr = tmp;
        }
        p = p->next;
    }
    pr->next = nullptr;
    return head;
}