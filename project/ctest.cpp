#include "header/linklist.h"
#include "header/linkstack.h"
#include "header/seqlist.h"
#include "header/seqqueue.h"
#include "header/seqstack.h"
#include "header/string.h"

using namespace std;

void test5() // for seqQueue
{
    seqQueue<int> q;
    for (int i = 0; i < 10; ++i)
        q.enQueue(i);
    q.Traverse();
}

void test4() // for linkStack
{
    linkStack<char> s;
    for (int i = 'a'; i <= 'z'; ++i)
        s.Push(i);
    s.Traverse();
    s.Clear();
    s.Traverse();
}

void test3() // for seqStack
{
    seqStack<int> s;
    for (int i = 0; i < 10; ++i)
        s.Push(i);
    s.Traverse();
    seqStack<int> s2(s);
    s2.Traverse();
    for (int i = 0; i < 10; ++i)
        printf("%d: Pop %d\n", i, s.Pop());
    s2.Clear();
    s2.Pop();
}
void test2() // for linkList
{
    linkList<int> a;
    for (int i = 0; i < 10; ++i)
        a.Push_Front(i);
    linkList<int> c(a);
    c.Traverse();
    // for (int i = -1; i < 13; ++i)
    //     printf("%d's idx is: %d\n", i, c.Remove(i));
    c.Inverse();
    c.Traverse();
    c.Delete(0);
    c.Delete(8);
    c.Traverse();
    for (int i = 0; !c.isEmpty(); ++i)
        cout << c.Pop_Back() << endl;
    c.Clear();
}

void test1() // for seqList
{
    seqStack<int> opnd;  //操作数栈
    seqStack<char> optr; //运算符栈
    seqList<int> a(1);
    for (int i = 0; i < 10; ++i)
        a.Push_Back(i);
    seqList<int> b(a);
    a.Inverse();
    // a.Insert(20, -1);
    cout << a.Visit(3) << endl;
    a.Traverse();
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}