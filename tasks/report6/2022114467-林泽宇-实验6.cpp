#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include "stack.h"
#include "queue.h"
using namespace std;

typedef char elemT;
typedef struct BtNode
{
    elemT data;
    struct BtNode *lc, *rc;
} BtNode, *btptr;

void initBt(btptr &root) //初始化二叉树
{
    root->data = '\0';
    root->lc = root->rc = nullptr;
}

void assignBiTree(btptr &root, const string str) //通过前序str给二叉树赋值
{
    static int idx = 0;
    if (idx >= str.size())
        return;
    char ch = str[idx];
    if (ch == '#')
    {
        ++idx;
        root = new BtNode{0, nullptr, nullptr};
        root->data = '@';
        return;
    }
    else if (ch == '\n' || ch == ' ')
        return;
    else
    {
        root = new BtNode{0, nullptr, nullptr};
        root->data = ch, ++idx;
    }
    assignBiTree(root->lc, str);
    assignBiTree(root->rc, str);
}

void preOrderTraverse(btptr &root) //前序遍历
{
    if (!root || root->data == '@')
        return;
    printf("%c", root->data);
    preOrderTraverse(root->lc);
    preOrderTraverse(root->rc);
}

void inOrderTraverse(btptr &root) //中序遍历
{
    if (!root || root->data == '@')
        return;
    inOrderTraverse(root->lc);
    printf("%c", root->data);
    inOrderTraverse(root->rc);
}

void postOrderTraverse(btptr &root) //后序遍历
{
    if (!root || root->data == '@')
        return;
    postOrderTraverse(root->lc);
    postOrderTraverse(root->rc);
    printf("%c", root->data);
}

void layerOrderTraverse(btptr &root) //层序遍历
{
    if (!root)
        return;
    queue<btptr> q;
    q.enQueue(root);
    while (!q.isEmpty())
    {
        char e = q.deQueue()->data;
        if (e != '@')
            printf("%c", e);
        if (root->lc)
            layerOrderTraverse(root->lc);
        if (root->rc)
            layerOrderTraverse(root->rc);
    }
}

char *formSeq(btptr &root, int pos, char seq[]) //返回完全二叉树顺序存储数组地址
{
    if (!root)
        return nullptr;
    queue<btptr> q;
    q.enQueue(root);
    while (!q.isEmpty())
    {
        char e = q.deQueue()->data;
        seq[pos - 1] = e;
        if (root->lc)
            formSeq(root->lc, 2 * pos, seq);
        if (root->rc)
            formSeq(root->rc, 2 * pos + 1, seq);
    }
    return seq;
}

int getEndFromSeq(char seq[]) // 通过完全二叉树顺序存储字符数组获得最后一个非空元素的位置
{
    int layer = 1, length = 1, idx = 0, pos = 0;
    while (1)
    {
        bool flag = 1;
        for (int i = 0; i < length; ++i)
            if (seq[idx++] != '@')
            {
                pos = idx;
                flag = 0;
            }
        if (flag)
            return pos;
        ++layer;
        idx = length;
        length = pow(2, layer) - 1;
    }
}

int main()
{
    string str;
    printf("请输入先序递归遍历字符序列:\n");
    cin >> str;
    btptr root = new BtNode{0, nullptr, nullptr};
    initBt(root);
    assignBiTree(root, str);

    printf("\nPreorder:\n");
    preOrderTraverse(root);
    printf("\nInorder:\n");
    inOrderTraverse(root);
    printf("\nPostorder:\n");
    postOrderTraverse(root);
    printf("\nLayerorder:\n");
    layerOrderTraverse(root);

    printf("\nSeqTraverse:\n");
    char seq[1000];
    memset(seq, '@', sizeof(seq));
    formSeq(root, 1, seq);

    int end = getEndFromSeq(seq);
    for (int i = 0; i < end; ++i)
        printf("%c", seq[i]);

    return 0;
}