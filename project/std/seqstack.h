#include <iostream>
using namespace std;

#include "astatus.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef int elemtype;
typedef struct
{
    elemtype *elem;
    int size, top;
} seqStack;

seqStack initStack(seqStack &s)
{
    s.elem = new elemtype[STACK_INIT_SIZE];
    if (!s.elem)
    {
        cerr << "内存分配失败!\n";
        exit(DOWNFLOW);
    }
    s.size = STACK_INIT_SIZE;
    s.top = -1;
    return s;
}
Status destroyStack(seqStack &s)
{
    delete s.elem;
    s.top = -1;
    s.size = 0;
    return OK;
}

bool isFull(seqStack &s)
{
    return s.top == s.size - 1;
}
bool isEmpty(seqStack &s)
{
    return s.top == -1;
}
int lenStack(seqStack &s)
{
    return s.top + 1;
}

Status Push(seqStack &s, elemtype e)
{
    if (isFull(s)) // 栈满
    {
        elemtype *tmp = new elemtype[s.size + STACK_INCREMENT];
        if (!tmp)
        {
            cerr << "内存分配失败!\n";
            exit(DOWNFLOW);
        }
        copy(s.elem, s.elem + (elemtype)s.size, tmp);
        delete[] s.elem;
        s.elem = tmp;
        s.size += STACK_INCREMENT;
    }
    s.elem[++s.top] = e;
    return OK;
}
elemtype Pop(seqStack &s)
{
    if ((isEmpty(s)))
    {
        cerr << "栈发生下溢!\n";
        exit(DOWNFLOW);
    }
    return s.elem[s.top--];
}
elemtype getTop(seqStack &s)
{
    if ((isEmpty(s)))
    {
        cerr << "栈发生下溢!\n";
        exit(DOWNFLOW);
    }
    return s.elem[s.top];
}