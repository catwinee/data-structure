#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream iFile;
ofstream oFile;
typedef struct triTuple
{
    int i, j;
    int e; //数据域
    struct triTuple *r, *d; //指针域
} clnode, *clptr;

class CrossList
{
private:
    int m, n, t; //最大行数, 最大列数, 非零元总数
    clptr *rhead, *chead;

public:
    CrossList(); //无参构造函数
    CrossList(CrossList &a, CrossList &b); //通过两个十字链表构造他们的和十字链表
    ~CrossList(); //析构函数
    void assign(); //从字符文件中读取数据为十字链表赋值
    void insert(clptr e); //往十字链表中插入节点
    void remove(int ii, int jj); //删除指定位置节点
    void traverse() const; //遍历链表, 输出到文件中
    void add(CrossList &cl); //将一个十字链表中的所有节点加入到另一个十字链表中
};

int main()
{
    iFile.open("input.txt");
    oFile.open("output.txt");
    CrossList cl1;
    CrossList cl2;
    CrossList cl3(cl1, cl2); //通过两个链表构建他们的和
    cl3.traverse(); //输出结果到文件
    iFile.close();
    oFile.close();
}

CrossList::CrossList()
{
    int mm, nn, tt;
    iFile >> mm >> nn >> tt; //读取数据
    rhead = new clptr[mm + 1]; //分配空间
    chead = new clptr[nn + 1];
    for (int i = 0; i < mm; ++i) //置空指针
        rhead[i] = nullptr;
    for (int i = 0; i < nn; ++i)
        chead[i] = nullptr;
    m = mm, n = nn, t = tt;
    assign(); //进行赋值
}

CrossList::CrossList(CrossList &a, CrossList &b)
{
    m = max(a.m, b.m), n = max(a.n, b.n), t = 0; //新十字链表的行数与列数取两个十字链表的最大值
    rhead = new clptr[m + 1];
    chead = new clptr[n + 1];
    for (int i = 0; i < m; ++i)
        rhead[i] = nullptr;
    for (int i = 0; i < n; ++i)
        chead[i] = nullptr;
    this->add(a);
    this->add(b); //分别将两个链表中的所有节点插入新链表中
}

CrossList::~CrossList()
{
    clptr p, q;
    for (int i = 0; i < m; ++i)
    {
        if (rhead[i])
            p = rhead[i]->r;
        while (p)
        {
            q = p->r; //存储下一个位置的信息
            delete p;
            p = q;
        }
    }
    p = q = nullptr;
    delete[] rhead;
    delete[] chead;
    rhead = chead = nullptr; //记得置空
    t = 0;
}

void CrossList::assign()
{
    int ii, jj, ee, tt = t;
    for (int i = 0; i < tt; ++i)
    {
        iFile >> ii >> jj >> ee;
        clptr e = new clnode({ii, jj, ee, nullptr, nullptr});
        insert(e); //循环插入节点
    }
}

void CrossList::insert(clptr e)
{
    clptr p;
    if (!rhead[e->i] || rhead[e->i]->j > e->j) //如果在开头则直接插入
        e->r = rhead[e->i], rhead[e->i] = e;
    else
    {
        p = rhead[e->i];
        while (p->r && p->r->j < e->j)
            p = p->r;
        if (p->r && p->r->j == e->j) //如果存在相同坐标的项, 则直接相加
        {
            p = p->r;
            p->e += e->e;
            if (!p->e) //如果结果为0则删除该节点并返回
                remove(e->i, e->j);
            --t;
            return;
        }
        else if (p->j == e->j)
        {
            p->e += e->e;
            if (!p->e)
                remove(e->i, e->j);
            --t;
            return;
        }
        else
            e->r = p->r, p->r = e;
    }
    if (!chead[e->j] || chead[e->j]->i > e->i)
        e->d = chead[e->j], chead[e->j] = e;
    else
    {
        p = chead[e->j];
        while (p->d && p->d->i < e->i)
            p = p->d;
        e->d = p->d, p->d = e;
    }
    return;
}

void CrossList::remove(int ii, int jj)
{
    --t; //非零元数目减一
    clptr p = rhead[ii], q;
    if (p->j == jj)
        rhead[ii] = nullptr;
    else
    {
        while (p->r->j < jj)
            p = p->r;
        q = p->r, p->r = q->r;
        delete q;
    }
    p = chead[jj];
    if (p->i == ii)
        chead[jj] == nullptr;
    else
    {
        while (p->d->i < ii)
            p = p->d;
        q = p->d, p->d = q->d;
        delete q;
    }
}

void CrossList::traverse() const //不修改对象
{
    oFile << m << " " << n << " " << t << '\n';
    clptr p;
    for (int i = 0; i < m; ++i)
    {
        if (rhead[i])
        {
            p = rhead[i];
            while (p)
            {
                oFile << '(' << p->i << ", " << p->j << ", " << p->e << ")\n";
                p = p->r;
            }
        }
    }
}

void CrossList::add(CrossList &cl)
{
    t += cl.t; //项数增加
    clptr p, q;
    for (int i = 0; i < cl.m; ++i)
    {
        if (cl.rhead[i])
        {
            p = cl.rhead[i];
            while (p)
            {
                q = p->r;
                p = new clnode({p->i, p->j, p->e, nullptr, nullptr});
                this->insert(p); //逐个插入
                p = q;
            }
        }
    }
}