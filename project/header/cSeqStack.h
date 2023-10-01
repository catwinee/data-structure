#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define DOWNFLOW -3
typedef int Status;

#define STACK_INIT_SIZE 100
#define INCREMENT 10

template <class ElemT>
class seqStack
{
private:
    ElemT *elem;
    int size, top;
public:
    seqStack()
    {
        this->elem = new ElemT[STACK_INIT_SIZE];
        if (!this->elem)
        {
            cerr << "内存分配失败!\n";
            exit(DOWNFLOW);
        }
        this->size = STACK_INIT_SIZE;
        this->top = -1;
    }
    seqStack(seqStack &s)
    {
        this->elem = new ElemT[s.size];
        if (!this->elem)
        {
            cerr << "内存分配失败!\n";
            exit(DOWNFLOW);
        }
        this->size = s.size;
        this->top = s.top;
        for (int i = 0; i <= s.top; ++i)
            this->elem[i] = s.elem[i];
    }
    Status destroyStack()
    {
        delete this->elem;
        this->top = -1;
        this->size = 0;
        return OK;
    }
    bool isFull()
    {
        return this->top == this->size - 1;
    }
    bool isEmpty()
    {
        return this->top == -1;
    }
    int lenStack()
    {
        return this->top + 1;
    }
    Status Push(ElemT e)
    {
        if (this->isFull()) // 栈满
        {
            ElemT *tmp = new ElemT[this->size + INCREMENT];
            if (!tmp)
            {
                cerr << "内存分配失败!\n";
                exit(DOWNFLOW);
            }
            copy(this->elem, this->elem + (ElemT)this->size, tmp);
            delete[] this->elem;
            this->elem = tmp;
            this->size += INCREMENT;
        }
        this->elem[++this->top] = e;
        return OK;
    }
    ElemT Pop()
    {
        if ((this->isEmpty()))
        {
            cerr << "栈发生下溢!\n";
            exit(DOWNFLOW);
        }
        return this->elem[this->top--];
    }
    ElemT getTop()
    {
        if ((this->isEmpty()))
        {
            cerr << "栈发生下溢!\n";
            exit(DOWNFLOW);
        }
        return this->elem[this->top];
    }
};