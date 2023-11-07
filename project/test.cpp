#include "std/linkList.h"
#include "std/linkstack.h"
#include "std/seqlist.h"
#include "std/seqqueue.h"
#include "std/seqstack.h"
#include "std/string.h"

int main()
{
    seqList l;
    seqStack a;
    ListPtr s;
    initList(s);
    for (int i = 0; i < 6; ++i)
        append(s, i);
    printList(s);

    cout << endl;
    insert(s, 5, 9);
    insert(s, 1, 9);
    insert(s, 0, 9);
    printList(s);

    clearList(s);
    printList(s);
    return 0;
}