#include <iostream>
using namespace std;
typedef struct LinkList
{
    int val;
    struct LinkList *next;
    LinkList() : val(0), next(nullptr){};
    LinkList(int x) : val(x), next(nullptr){};
} LinkNode, *LinkPtr;
LinkPtr insert(LinkPtr &first, int i, int b);
int main()
{
    LinkPtr first = new LinkNode(1), p = first;
    for (int i = 2; i <= 5; ++i)
    {
        p->next = new LinkNode(i);
        p = p->next;
    }
    first = insert(first, 6, 9);
    return 0;
}
LinkPtr insert(LinkPtr &first, int i, int b)
{
    LinkPtr p = first, tmp = new LinkNode(b);
    if (i == 1)
    {
        tmp->next = first;
        return tmp;
    }
    for (int cnt = 2; cnt < i; ++cnt)
    {
        if (!p)
            exit(-1);
        p = p->next;
    }
    tmp->next = p->next;
    p->next = tmp;
    return first;
}
