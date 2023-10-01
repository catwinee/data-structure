#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
using namespace std;

#define Stack_init_size 100
#define Stackincrement 10
#define Status int
#define OK 0
#define OVERFLOW -2
#define ERROR -1

ofstream outputFile;
int num[45];

typedef struct
{
    int *top;
    int *base;
    int stacksize;
} sqStack;

Status initialStack(sqStack &s)
{
    s.base = new int[Stack_init_size];
    if (!s.base)
        exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = Stack_init_size;
    return OK;
}
Status push(sqStack &s, int e)
{
    if (s.top - s.base >= s.stacksize) //避免上溢
    {
        s.base = (int *)realloc(s.base, (s.stacksize + Stackincrement) * sizeof(int));
        s.top = s.base + s.stacksize;
        s.stacksize += Stackincrement;
    }
    *s.top++ = e;
    return OK;
}
Status pop(sqStack &s, int &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *--s.top;
    return OK;
}
Status getTop(sqStack &s, int &e)
{
    if (s.top == s.base)
        return ERROR;
    e = *(s.top - 1);
    return OK;
}

int main()
{
    outputFile.open("b.txt");
    memset(num, -1, sizeof num);
    num[0] = 0, num[1] = 1;
    sqStack s;
    initialStack(s);
    push(s, 39);

    while (s.top != s.base)
    {
        int tmp;
        getTop(s, tmp);
        if (tmp % 2)
        {
            int f1 = tmp / 2, f2 = tmp - 2;
            if (num[f1] == -1|| num[f2] == -1)
                push(s, f1), push(s, f2);
            else
            {
                pop(s, tmp);
                num[tmp] = num[f1] + num[f2];
            }
        }
        else
        {
            int f = tmp / 2;
            if (num[f] == -1)
                push(s, f);
            else
            {
                pop(s, tmp);
                num[tmp] = num[f];
            }
        }
        if (num[tmp - 1] == -1)
            push(s, tmp - 1);
    }

    for (int i = 0; i <= 39; ++i)
    {
        outputFile << setw(6) << num[i];
        if (i % 8 == 7)
            outputFile << '\n';
    }
    outputFile.close();
    return 0;
}