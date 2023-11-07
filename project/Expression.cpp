#include <iostream>
#include <cctype>
#include "header/seqstack.h"
using namespace std;
const int MAX_LENGTH = 100;
string formula;
seqStack<int> opnd;  //操作数栈
seqStack<char> optr; //运算符栈
void test();
int main()
{
    /*
    输入修约:
    有三种输入类型:
        1.操作数
        2.运算符('+', '-', '*', '/')加, 减, 乘, 整除
        3.界限符('(', ')', '#')左右括号, 终止符
    输入只有一行, 忽视各操作数与运算符间的空格
    */
    getline(cin, formula);
    formula += '#';
    int n = formula.size();
    for (int i = 0; i < n; ++i)
    {
        if (formula[i] == ' ')
            continue;
        if (isdigit(formula[i]))
        {
            int tmp = formula[i] - '0';
            while (isdigit(formula[++i]))
                tmp *= 10, tmp += formula[i] - '0';
            opnd.Push(tmp), --i;
        }
        else if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '(' || formula[i] == ')' || formula[i] == '#')
            optr.Push(formula[i]);
    }
    test();
    return 0;
}
void test()
{
    while (!opnd.isEmpty())
        cout << opnd.Pop() << endl;
    while (!optr.isEmpty())
        cout << optr.Pop() << endl;
}