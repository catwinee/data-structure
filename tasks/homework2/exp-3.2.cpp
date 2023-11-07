#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int initStackSize = 10000;
typedef struct Stack
{
    char *elem;
    int top;
    int size;
} stk;
void initStk(stk &s)
{
    s.elem = (char *)malloc(initStackSize * sizeof(char));
    if (!s.elem)
    {
        printf("Bad Alloc!\n");
        exit(-1);
    }
    s.top = 0;
    s.size = initStackSize;
}
bool isEmpty(const stk &s)
{
    return s.top == 0;
}
bool isFull(const stk &s)
{
    return s.top == s.size + 1;
}
void push(stk &s, const char &e)
{
    if (isFull(s))
    {
        printf("Overflow!\n");
        exit(-1);
    }
    s.elem[s.top++] = e;
}
char pop(stk &s)
{
    if (isEmpty(s))
    {
        printf("Downflow!\n");
        exit(-1);
    }
    char e = s.elem[--s.top];
    return e;
}
char getPeak(const stk &s)
{
    if (isEmpty(s))
    {
        printf("Downflow!\n");
        exit(-1);
    }
    char e = s.elem[s.top - 1];
    return e;
}
bool compare(char o1, char o2)
{
    int a1, a2;
    switch (o1)
    {
    case '(':
        a1 = 3;
        break;
    case '+':
    case '-':
        a1 = 2;
        break;
    case '*':
    case '/':
        a1 = 1;
    }
    switch (o2)
    {
    case '(':
        a2 = 3;
        break;
    case '+':
    case '-':
        a2 = 2;
        break;
    case '*':
    case '/':
        a2 = 1;
    }
    return a1 <= a2;
}
int main()
{
    printf("请输入中缀表达式:\n");
    stk optr;
    initStk(optr);
    char ch, fml[100], tmp;
    for (int i = 0;;)
    {
        ch = getchar();
        if (ch == ' ' || ch == '\n')
            continue;
        if (ch == '#')
            break;
        fml[i++] = ch;
    }
    int n = strlen(fml);
    for (int i = 0; i < n; ++i)
    {
        ch = fml[i];
        if (isalpha(ch))
            printf("%c", ch);
        else
        {
            if (ch == '(')
                push(optr, ch);
            else if (ch == ')')
            {
                ch = pop(optr);
                while (ch != '(')
                {
                    printf("%c", ch);
                    ch = pop(optr);
                }
            }
            else
            {
                if (isEmpty(optr))
                    push(optr, ch);
                else
                {
                    if (compare(tmp = pop(optr), ch))
                    {
                        printf("%c", tmp);
                        push(optr, ch);
                    }
                    else
                    {
                        push(optr, tmp);
                        push(optr, ch);
                    }
                }
            }
        }
    }
    while (!isEmpty(optr))
        printf("%c", pop(optr));
}