#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define Stack_init_size 100
#define Stackincrement 10
#define Status int
#define OK 0
#define OVERFLOW -2
#define ERROR -1
ofstream outputFile;
typedef struct
{
    int n;
    int e, o;
} node;
typedef struct
{
    node *top;
    node *base;
    int stacksize;
} Stack;
Status initialStack(Stack &s)
{
    s.base = new node;
    if (!s.base)
        exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = Stack_init_size;
    return OK;
}
Status push(Stack &s, node e)
{
    if (s.top - s.base >= s.stacksize) //避免上溢
    {
        s.base =
            (node *)realloc(s.base, (s.stacksize +
                                     Stackincrement) *
                                        sizeof(node));
        s.top = s.base + s.stacksize;
        s.stacksize += Stackincrement;
    }
    *s.top++ = e;
    return OK;
}
Status pop(Stack &s, node e)
{
    if (s.top == s.base)
        return ERROR;
    e = *--s.top;
    return OK;
}
Status getTop(Stack &s, node e)
{
    if (s.top == s.base)
        return ERROR;
    e = *(s.top - 1);
    return OK;
}
int f(int n)
{
    if (!n)
        return 0;
    else if (n == 1)
        return 1;
    Stack s;
    initialStack(s);
    for (int i = n; i > 1; --i)
        push(s, {i, -1});
    push(s, {1, 1}), push(s, {0, 0});
}
int main()
{
    outputFile.open("b.txt");
    for (int i = 0; i <= 39; ++i)
    {
        outputFile << f(i);
    }
    outputFile.close();
    return 0;
}