#include <iostream>
using namespace std;
typedef struct List
{
    int val;
    List *next;
    List() : val(0), next(nullptr){};
    List(int x) : val(x), next(nullptr){};
    List(int x, List *ptr) : val(x), next(ptr){};
} Listnode, *Listptr;
bool isemptyList(Listptr head)
{
    if (!head->next)
        return 1;
    else
        return 0;
}
void outputList(Listptr head)
{
    head = head->next;
    while (head)
    {
        cout << head->val << '\n';
        head = head->next;
    }
}
void inputList(Listptr &head)
{
    Listptr p = head;
    int n, x;
    cin >> n;
    while (n--)
    {
        cin >> x;
        Listptr tmp = new List(x);
        p->next = tmp, p = p->next;
    }
}
void clearList(Listptr &head)
{
    Listnode *p;
    while (head->next)
    {
        p = head->next;
        head->next = p->next;
        delete p;
    }
}
int main()
{
    Listptr head = new List(-1);
    cout << isemptyList(head) << '\n';
    inputList(head);
    outputList(head);
    cout << isemptyList(head) << '\n';
    clearList(head);
    cout << isemptyList(head) << '\n';
    return 0;
}