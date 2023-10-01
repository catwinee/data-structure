#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
ifstream inputFile;
ofstream outputFile;
typedef struct Polynomial //多项式结构体
{
    double ecof;             //双精度浮点型存储系数
    long long int expo;      //整型存储指数
    struct Polynomial *next; //指针域
} PolynTerm, *PolynPtr;
void createPolyn(PolynPtr &head) //新建空多项式
{
    head = new PolynTerm;
}
void formatPolyn(PolynPtr &head) //格式化多项式(合并同次项并按照指数降序排列)
{
    PolynPtr ohead = new Polynomial;
    ohead->next = head->next; //存储未排序数据
    head->next = nullptr;     //置空原多项式, 方便插入
    PolynPtr p = head, pr = ohead->next;
    while (pr) //当仍有数据未插入
    {
        PolynPtr tmp = new PolynTerm;
        tmp->ecof = pr->ecof;
        tmp->expo = pr->expo;
        while (p) //寻找插入位置
        {
            if (!p->next) //表尾处直接插入
            {
                tmp->next = nullptr;
                p->next = tmp;
                break;
            }
            if (p->next->expo == pr->expo) //若指数相同则合并
            {
                p->next->ecof += pr->ecof;
                --head->ecof;       //合并后项数减一
                if (!p->next->ecof) //如果合并后系数为0则删除
                {
                    p->next = p->next->next;
                    --head->ecof; //项数再减一
                }
                break;
            }
            if (p->next->expo < pr->expo) // 满足条件插入
            {
                tmp->next = p->next;
                p->next = tmp;
                break;
            }
            p = p->next;
        }
        p = head, pr = pr->next;
    }
    for (int i = 0; i < head->ecof; ++i) //记得标记表尾
        p = p->next;
    p->next = nullptr;
}
PolynPtr inputPolyn(PolynPtr &head) //通过输入创建一个多项式
{
    head->ecof = 0;
    while (head->ecof <= 0) //项数为0则重新输入
    {
        inputFile >> head->ecof;
        if (!head->ecof)
            outputFile << "项数必须为正数!\n", outputFile.flush();
    }
    PolynPtr p = head; // p指针作为哨兵
    for (int i = 0; i < head->ecof; ++i)
    {
        PolynPtr tmp = new PolynTerm;
        outputFile.flush();
        inputFile >> tmp->ecof >> tmp->expo;
        if (tmp->ecof) //系数不能为0
            p->next = tmp, p = p->next;
        else
        {
            outputFile << "该项系数为0, 请重新输入!\n";
            outputFile.flush();
            --i;
        }
    }
    p->next = nullptr;
    formatPolyn(head);
    return head;
}
void outputPolyn(PolynPtr p) //输出多项式
{
    outputFile << "该多项式有" << p->ecof << "项" << endl;
    p = p->next;
    if (!p)
    {
        outputFile << "该多项式为空\n";
        outputFile.flush();
        return;
    }
    if (p->ecof < 0) //数据和符号分开输出
        outputFile << "-";
    while (p) //已经保证系数不为0
    {
        if (p->expo == 0) //指数为0, 只输出系数
        {
            outputFile << abs(p->ecof);
            // printf("%.2lf", abs(p->ecof)); //只输出绝对值
            p = p->next;
            if (p) //处理下一项符号
                if (p->ecof > 0)
                    outputFile << " + ";
                else if (p->ecof < 0)
                    outputFile << " -";
            continue; //只输出系数
        }
        if (abs(p->ecof) != 1) //除非系数为正负1, 否则输出系数
            outputFile << abs(p->ecof);
        // printf("%.2lf", abs(p->ecof));
        if (p->expo == 1) //输出变量
            outputFile << "x";
        else if (p->expo > 0)
            outputFile << "x^" << p->expo;
        else
            outputFile << "x^(" << p->expo << ')';
        p = p->next;
        if (p) //处理下一项符号
            if (p->ecof > 0)
                outputFile << " + ";
            else if (p->ecof < 0)
                outputFile << " - ";
    }
    outputFile << '\n';
}
PolynPtr addPolyn(PolynPtr pah, PolynPtr pbh) //多项式加法
{
    PolynPtr pa = pah->next, pb = pbh->next;
    PolynPtr res = new PolynTerm, p = res;
    res->ecof = pah->ecof + pbh->ecof; //项数相加
    while (pa)                         //先把A表所有项导入
    {
        PolynPtr tmp = new PolynTerm;
        tmp->ecof = pa->ecof;
        tmp->expo = pa->expo;
        p->next = tmp;
        p = p->next, pa = pa->next;
    }
    while (pb) //再导入B表
    {
        PolynPtr tmp = new PolynTerm;
        tmp->ecof = pb->ecof;
        tmp->expo = pb->expo;
        p->next = tmp;
        p = p->next, pb = pb->next;
    }
    p->next = nullptr;
    formatPolyn(res); //最后格式化多项式
    return res;
}
PolynPtr multiplyPolyn(PolynPtr pah, PolynPtr pbh) // 多项式乘法
{
    PolynPtr pa = pah->next, pb = pbh->next;
    PolynPtr res = new PolynTerm, p = res;
    res->ecof = pah->ecof * pbh->ecof; //项数相乘
    while (pa)
    {
        while (pb) //逐项相乘
        {
            PolynPtr tmp = new PolynTerm;
            tmp->ecof = pa->ecof * pb->ecof; //系数相乘
            tmp->expo = pa->expo + pb->expo; //指数相加
            p->next = tmp;
            p = p->next;
            pb = pb->next;
        }
        pa = pa->next;
        pb = pbh->next;
    }
    p->next = nullptr;
    formatPolyn(res); //格式化多项式
    return res;
}
int main()
{
    //设置输入输出文件, 控制精度
    inputFile.open("input.txt");
    outputFile.open("output.txt");
    outputFile << fixed << setprecision(2);
    ios_base::sync_with_stdio(0);
    inputFile.tie(0), outputFile.tie(0);

    //先建表
    PolynPtr polyn_A, polyn_B, polyn_C, polyn_D;
    createPolyn(polyn_A), createPolyn(polyn_B), createPolyn(polyn_C), createPolyn(polyn_D);
    inputPolyn(polyn_A);
    inputPolyn(polyn_B);

    outputFile << "多项式A为: \n";
    outputFile.flush();
    outputPolyn(polyn_A);
    outputFile << "多项式B为: \n";
    outputFile.flush();
    outputPolyn(polyn_B);

    polyn_C = addPolyn(polyn_A, polyn_B);
    outputFile << "两个多项式相加的结果为: \n";
    outputFile.flush();
    outputPolyn(polyn_C);

    polyn_D = multiplyPolyn(polyn_A, polyn_B);
    outputFile << "两个多项式相乘的结果为: \n";
    outputFile.flush();
    outputPolyn(polyn_D);

    outputFile.close();
    return 0;
}